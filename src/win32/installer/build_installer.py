# -*- coding: utf-8 -*-
# Copyright 2010-2021, Google Inc.
# All rights reserved.
#
# Redistribution and use in source and binary forms, with or without
# modification, are permitted provided that the following conditions are
# met:
#
#     * Redistributions of source code must retain the above copyright
# notice, this list of conditions and the following disclaimer.
#     * Redistributions in binary form must reproduce the above
# copyright notice, this list of conditions and the following disclaimer
# in the documentation and/or other materials provided with the
# distribution.
#     * Neither the name of Google Inc. nor the names of its
# contributors may be used to endorse or promote products derived from
# this software without specific prior written permission.
#
# THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
# "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
# LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
# A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT
# OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
# SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
# LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
# DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
# THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
# (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
# OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.

"""Runs wix.exe to build the installer."""

import argparse
import dataclasses
import os
import pathlib
import platform
import subprocess

from build_tools import mozc_version
from build_tools import vs_util


@dataclasses.dataclass
class ForwarderInfo:
  """Third party archive file to be used to build Mozc binaries.

  Attributes:
  """
  arch: str
  branding: str
  version: MozcVersion

  def get_version_string(self, separator='.') -> str:
    components = [
      '@MAJOR@',
      '@MINOR@',
      '@BUILD@',
      '@REVISION@'
    ]
    return self.version.GetVersionInFormat(separator.join(components))

  @property
  def forwarder_dll_name(self) -> str:
    if self.arch == 'arm64x':
      return {
        'Mozc': 'mozc_tip_forwarder_arm64x.dll',
        'GoogleJapaneseInput': 'GoogleIMEJaTIPForwarderArm64X.dll',
      }[self.branding]
    elif self.arch == 'x64':
      return {
        'Mozc': 'mozc_tip_forwarder_x64.dll',
        'GoogleJapaneseInput': 'GoogleIMEJaTIPForwarderX64.dll',
      }[self.branding]
    else:
      raise ValueError(f'unrecognized arch: {self.arch}')

  @property
  def arm64_impl_dll_name(self) -> str:
    return {
      'Mozc': 'mozc_tip_arm64.dll',
      'GoogleJapaneseInput': 'GoogleIMEJaTIP_arm64.dll',
    }[self.branding]

  @property
  def x64_impl_dll_name(self) -> str:
    return {
      'Mozc': 'mozc_tip_x64.dll',
      'GoogleJapaneseInput': 'GoogleIMEJaTIP_x64.dll',
    }[self.branding]

  @property
  def file_description(self) -> str:
    return {
      'Mozc': 'Mozc TIP Module Forwarder',
      'GoogleJapaneseInput': 'Google 日本語入力 TIP モジュール フォワーダー',
    }[self.branding]

  @property
  def product_name(self) -> str:
    return {
      'Mozc': 'Mozc',
      'GoogleJapaneseInput': 'Google 日本語入力',
    }[self.branding]

  @staticmethod
  def _get_def_file_content(filename:str) -> str:
    stem = str(pathlib.Path(filename).stem)
    return '\n'.join([
      'EXPORTS',
      f'    DllGetClassObject = {stem}.DllGetClassObject',
      f'    DllCanUnloadNow   = {stem}.DllCanUnloadNow',
    ])

  def get_def_file_content_for_x64(self) -> str:
    return self._get_def_file_content(self.x64_impl_dll_name)

  def get_def_file_content_for_arm64(self) -> str:
    return self._get_def_file_content(self.arm64_impl_dll_name)

  def get_rc_file_content(self) -> str:
    comma_separated_versoin = self.get_version_string(',')
    dot_separated_versoin = self.get_version_string('.')
    file_description = self.file_description

    original_file_name = None
    original_file_name = self.forwarder_dll_name
    internal_name = str(pathlib.Path(original_file_name).stem)
    product_name = self.product_name
    copyright = 'Google LLC'

    return '\n'.join([
      '#include "winres.h"',
      'LANGUAGE LANG_JAPANESE, SUBLANG_DEFAULT',
      '',
      'VS_VERSION_INFO VERSIONINFO',
      f'FILEVERSION {comma_separated_versoin}',
      f'PRODUCTVERSION {comma_separated_versoin}',
      'FILEFLAGSMASK VS_FF_DEBUG | VS_FF_PRERELEASE | VS_FF_PATCHED | VS_FF_INFOINFERRED',
      'FILEFLAGS 0x0L',
      'FILEOS VOS__WINDOWS32',
      'FILETYPE VFT_DLL',
      'FILESUBTYPE VFT2_UNKNOWN',
      'BEGIN',
      '    BLOCK "StringFileInfo"',
      '    BEGIN',
      '        BLOCK "041104b0"',
      '        BEGIN',
      f'            VALUE "CompanyName", "{copyright}"',
      f'            VALUE "FileDescription", "{file_description}"',
      f'            VALUE "FileVersion", "{dot_separated_versoin}"',
      f'            VALUE "InternalName", "{internal_name}"',
      f'            VALUE "LegalCopyright", "{copyright}"',
      f'            VALUE "OriginalFilename", "{original_file_name}"',
      f'            VALUE "ProductName", "{product_name}"',
      f'            VALUE "ProductVersion", "{dot_separated_versoin}"',
      '        END',
      '    END',
      '    BLOCK "VarFileInfo"',
      '    BEGIN',
      '        VALUE "Translation", 0x411, 1200',
      '    END',
      'END',
      '',
    ])


def exec_command(
    args: list[str],
    cwd: Union[str, pathlib.Path],
    env=os.environ: dict[str, str],
) -> None:
  """Runs the given command then returns the output.

  Args:
    args: The command to be executed.
    cwd: The current working directory.
    env: Environment variables.

  Raises:
    ChildProcessError: When the given command cannot be executed.
  """
  process = subprocess.Popen(
      args,
      stdout=subprocess.PIPE,
      stderr=subprocess.PIPE,
      shell=False,
      text=True,
      encoding='utf-8',
      cwd=cwd,
      env=env)
  stdout, stderr = process.communicate()
  exitcode = process.wait()

  if exitcode != 0:
    command = ' '.join(args)
    msgs = ['Failed to execute command:', '', command, '', f'cwd={cwd}']
    if stdout:
      msgs += ['-----stdout-----', stdout]
    if stderr:
      msgs += ['-----stderr-----', stderr]
    raise ChildProcessError('\n'.join(msgs))


def normalize_win_arch(arch: str) -> str:
  """Normalize the architecture name for Windows build environment.

  Args:
    arch: a string representation of a CPU architecture to be normalized.

  Returns:
    String representation of a CPU architecture (e.g. 'x64' and 'arm64')
  """
  normalized = arch.lower()
  if normalized == 'amd64':
    return 'x64'
  return normalized


def generate_forwarder(
    info: ForwarderInfo,
    out: pathlib.Path,
):
  host_arch = normalize_win_arch(platform.uname().machine)
  target_arch = 'arm64' if info.arch == 'arm64x' else 'x64'
  arch = host_arch if host_arch == target_arch else f'{host_arch}_{target_arch}'
  env = get_vs_env_vars(arch)

  with tempfile.TemporaryDirectory() as work_dir:
    empty_cc = pathlib.Path(work_dir).joinpath('empty.cc')
    empty_cc.touch()

    cl = shutil.which('cl.exe', path=env['PATH'])
    link = shutil.which('link.exe', path=env['PATH'])
    rc = shutil.which('rc.exe', path=env['PATH'])

    if info.arch == 'arm64x':
      exec_command([cl, '/nologo', '/c', '/Foempty_arm64.obj', 'empty.cc'], cwd=work_dir, env=env, dryrun=args.dryrun)
      exec_command([cl, '/nologo', '/c', '/arm64EC', '/Foempty_x64.obj', 'empty.cc'], cwd=work_dir, env=env, dryrun=args.dryrun)
    else:
      exec_command([cl, '/nologo', '/c', '/Foempty_x64.obj', 'empty.cc'], cwd=work_dir, env=env, dryrun=args.dryrun)

    mozc_x64_def = pathlib.Path(work_dir).joinpath('mozc_x64.def')
    mozc_x64_def.write_text(info.get_def_file_content_for_x64(), encoding='utf-8')
    exec_command([link, '/lib', '/nologo', '/machine:x64', '/ignore:4104', '/def:mozc_x64.def', '/out:mozc_x64.lib'], cwd=work_dir, env=env, dryrun=args.dryrun)

    if info.arch == 'arm64x':
      mozc_arm64_def = pathlib.Path(work_dir).joinpath('mozc_arm64.def')
      mozc_arm64_def.write_text(info.get_def_file_content_for_arm64(), encoding='utf-8')
      exec_command([link, '/lib', '/nologo', '/machine:arm64', '/ignore:4104', '/def:mozc_arm64.def', '/out:mozc_arm64.lib'], cwd=work_dir, env=env, dryrun=args.dryrun)

    rc_file = pathlib.Path(work_dir).joinpath('mozc_tip_shim.rc')
    rc_file.write_text(info.get_rc_file_content(), encoding='utf-8')

    exec_command([
        rc, '/nologo', '/r', '/8', str(rc_file)], cwd=work_dir, env=env, dryrun=args.dryrun)

    forwarder_filename = pathlib.Path(info.forwarder_dll_name).name
    if info.arch == 'arm64x':
      exec_command([
          link, '/dll', '/nologo', '/noentry', '/machine:arm64x', '/ignore:4104',
          '/defArm64Native:mozc_arm64.def', '/def:mozc_x64.def', f'/out:{forwarder_filename}',
          'empty_arm64.obj', 'empty_x64.obj', 'mozc_arm64.lib', 'mozc_x64.lib',
          'mozc_tip_shim.res'], cwd=work_dir, env=env, dryrun=args.dryrun)
    else:
      exec_command([
          link, '/dll', '/nologo', '/noentry', '/machine:x64', '/ignore:4104',
          '/def:mozc_x64.def', f'/out:{forwarder_filename}', 'empty_x64.obj',
          'mozc_x64.lib', 'mozc_tip_shim.res'],
          cwd=work_dir, env=env, dryrun=args.dryrun)

    src = pathlib.Path(work_dir).joinpath(forwarder_filename)
    if args.dryrun:
      print(f'dryrun: Copying {src} to {out}')
    else:
      shutil.copy2(src=src, dst=out)


def run_wix4(args) -> None:
  """Run 'dotnet tool run wix build ...'.

  Args:
    args: args
  """
  vs_env_vars = vs_util.get_vs_env_vars('x64')
  redist_root = pathlib.Path(vs_env_vars['VCTOOLSREDISTDIR']).resolve()
  redist_x86 = redist_root.joinpath('x86').joinpath('Microsoft.VC143.CRT')
  redist_x64 = redist_root.joinpath('x64').joinpath('Microsoft.VC143.CRT')
  version_file = pathlib.Path(args.version_file).resolve()
  version = mozc_version.MozcVersion(version_file)
  credit_file = pathlib.Path(args.credit_file).resolve()
  document_dir = credit_file.parent
  qt_dir = pathlib.Path(args.qt_core_dll).parent.parent.resolve()
  icon_path = pathlib.Path(args.icon_path).resolve()
  mozc_tip_x86 = pathlib.Path(args.mozc_tip_x86).resolve()
  mozc_tip_x64 = pathlib.Path(args.mozc_tip_x64).resolve()
  mozc_tip_x64_pdb = mozc_tip_x64.with_suffix('.pdb')
  if args.mozc_tip_x64_pdb:
    mozc_tip_x64_pdb = pathlib.Path(args.mozc_tip_x64_pdb).resolve()
  mozc_broker = pathlib.Path(args.mozc_broker).resolve()
  mozc_server = pathlib.Path(args.mozc_server).resolve()
  mozc_cache_service = pathlib.Path(args.mozc_cache_service).resolve()
  mozc_renderer = pathlib.Path(args.mozc_renderer).resolve()
  mozc_tool = pathlib.Path(args.mozc_tool).resolve()
  custom_action = pathlib.Path(args.custom_action).resolve()
  wix_path = pathlib.Path(args.wix_path).resolve()

  branding = args.branding
  upgrade_code = ''
  omaha_guid = ''
  omaha_client_key = ''
  omaha_clientstate_key = ''
  if branding == 'GoogleJapaneseInput':
    upgrade_code = 'C1A818AF-6EC9-49EF-ADCF-35A40475D156'
    omaha_guid = 'DDCCD2A9-025E-4142-BCEB-F467B88CF830'
    omaha_client_key = 'Software\\Google\\Update\\Clients\\' + omaha_guid
    omaha_clientstate_key = (
        'Software\\Google\\Update\\ClientState\\' + omaha_guid
    )
  elif branding == 'Mozc':
    upgrade_code = 'DD94B570-B5E2-4100-9D42-61930C611D8A'

  omaha_channel_type = 'dev' if version.IsDevChannel() else 'stable'
  vs_configuration_name = 'Debug' if args.debug_build else 'Release'

  with tempfile.TemporaryDirectory() as work_dir:
    tip_forwarder_x64 = pathlib.Path(work_dir).joinpath('tip_forwarder_x64.dll')
    tip_forwarder_x64_info = ForwarderInfo(arch='x64', branding=branding, version=version)
    generate_forwarder(tip_forwarder_x64_info, out=tip_forwarder_x64)

    # tip_forwarder_arm64 = pathlib.Path(work_dir).joinpath('tip_forwarder_arm64.dll')
    # tip_forwarder_arm64_info = ForwarderInfo(arch='arm64', branding=branding, version=version)
    # generate_forwarder(tip_forwarder_arm64_info, out=tip_forwarder_arm64)

    commands = [
        f'{wix_path}',
        'build',
        '-nologo',
        '-arch', 'x64',
        '-define', f'MozcVersion={version.GetVersionString()}',
        '-define', f'UpgradeCode={upgrade_code}',
        '-define', f'OmahaGuid={omaha_guid}',
        '-define', f'OmahaClientKey={omaha_client_key}',
        '-define', f'OmahaClientStateKey={omaha_clientstate_key}',
        '-define', f'OmahaChannelType={omaha_channel_type}',
        '-define', f'VSConfigurationName={vs_configuration_name}',
        '-define', f'ReleaseRedistCrt32Dir={redist_x86}',
        '-define', f'ReleaseRedistCrt64Dir={redist_x64}',
        '-define', f'AddRemoveProgramIconPath={icon_path}',
        '-define', f'MozcTIPx86Path={mozc_tip_x86}',
        '-define', f'MozcTIPx64Path={mozc_tip_x64}',
        '-define', f'MozcTIPx64PdbPath={mozc_tip_x64_pdb}',
        '-define', f'MozcTIPForwarderX64={tip_forwarder_x64.resolve()}',
        '-define', f'MozcBroker64Path={mozc_broker}',
        '-define', f'MozcServer64Path={mozc_server}',
        '-define', f'MozcCacheService64Path={mozc_cache_service}',
        '-define', f'MozcRenderer64Path={mozc_renderer}',
        '-define', f'MozcToolPath={mozc_tool}',
        '-define', f'CustomActions64Path={custom_action}',
        '-define', f'DocumentsDir={document_dir}',
        '-define', f'QtDir={qt_dir}',
        '-define', 'QtVer=6',
        '-out', args.output,
        '-src', args.wxs_path,
    ]
    exec_command(commands, cwd=os.getcwd())


def main():
  parser = argparse.ArgumentParser()
  parser.add_argument('--output', type=str)
  parser.add_argument('--version_file', type=str)
  parser.add_argument('--mozc_tool', type=str)
  parser.add_argument('--mozc_renderer', type=str)
  parser.add_argument('--mozc_server', type=str)
  parser.add_argument('--mozc_broker', type=str)
  parser.add_argument('--mozc_cache_service', type=str)
  parser.add_argument('--mozc_tip_x86', type=str)
  parser.add_argument('--mozc_tip_x64', type=str)
  parser.add_argument('--mozc_tip_x64_pdb', type=str)
  parser.add_argument('--custom_action', type=str)
  parser.add_argument('--icon_path', type=str)
  parser.add_argument('--credit_file', type=str)
  parser.add_argument('--qt_core_dll', type=str)
  parser.add_argument('--wxs_path', type=str)
  parser.add_argument('--wix_path', type=str)
  parser.add_argument('--branding', type=str)
  parser.add_argument(
      '--debug_build', dest='debug_build', default=False, action='store_true'
  )

  args = parser.parse_args()

  run_wix4(args)


if __name__ == '__main__':
  main()
