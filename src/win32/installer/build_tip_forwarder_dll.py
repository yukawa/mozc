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

"""Generates an ARM64X forwarder DLL.

"""


import argparse
import dataclasses
import os
import pathlib
import platform
import shutil
import subprocess
import tempfile
from typing import Union

from build_tools import mozc_version
from build_tools import vs_util


def is_windows() -> bool:
  """Returns true if the platform is Windows."""
  return os.name == 'nt'


def parse_args() -> argparse.Namespace:
  """Parse command line options."""
  parser = argparse.ArgumentParser()
  parser.add_argument('--dryrun', action='store_true', default=False)

  parser.add_argument(
      '--version_file',
      dest='version_file',
      help='the path to version.txt',
  )
  parser.add_argument(
      '--branding',
      dest='branding',
      default='Mozc',
      choices=['Mozc', 'GoogleJapaneseInput'],
      help='branding',
  )
  parser.add_argument(
      '--output',
      dest='output',
      help='the path of the generated forwarder DLL file',
  )
  parser.add_argument(
      '--host',
      dest='host',
      help='the architecture of the host environment',
  )

  return parser.parse_args()


@dataclasses.dataclass
class ForwarderInfo:
  """Third party archive file to be used to build Mozc binaries.

  Attributes:
  """
  branding: str
  version: mozc_version.MozcVersion

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
    return {
      'Mozc': 'mozc_tip64x.dll',
      'GoogleJapaneseInput': 'GoogleIMEJaTIP64X.dll',
    }[self.branding]

  @property
  def arm64_impl_dll_name(self) -> str:
    return {
      'Mozc': 'mozc_tip64arm.dll',
      'GoogleJapaneseInput': 'GoogleIMEJaTIP64Arm.dll',
    }[self.branding]

  @property
  def x64_impl_dll_name(self) -> str:
    return {
      'Mozc': 'mozc_tip64.dll',
      'GoogleJapaneseInput': 'GoogleIMEJaTIP64.dll',
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
    command: list[str],
    cwd: Union[str, pathlib.Path],
    env: dict[str, str],
    dryrun: bool = False,
) -> None:
  """Run the specified command.

  Args:
    command: Command to run.
    cwd: Directory to execute the command.
    env: Environment variables.
    dryrun: True to execute the specified command as a dry run.

  Raises:
    CalledProcessError: When the process failed.
  """
  if dryrun:
    print(
        f"dryrun: subprocess.run('{command}', shell=False, check=True,"
        f' cwd={cwd}, env={env})'
    )
  else:
    subprocess.run(command, shell=False, check=True, cwd=cwd, env=env)


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


def build_on_windows(args: argparse.Namespace) -> None:
  """Build ARM64X DLL.

  Args:
    args: build options to be used to customize behaviors.

  Raises:
    FileNotFoundError: when any required file is not found.
  """
  host_arch = args.host
  if host_arch is None:
    host_arch = normalize_win_arch(platform.uname().machine)

  version = mozc_version.MozcVersion(args.version_file)
  info = ForwarderInfo(branding=args.branding, version=version)

  target_arch = 'arm64'
  arch = host_arch if host_arch == target_arch else f'{host_arch}_{target_arch}'
  env = vs_util.get_vs_env_vars(arch)

  dest = pathlib.Path(args.output)
  if dest.exists():
    if args.dryrun:
      print(f'dryrun: unlinking {str(dest)}')
    else:
      dest.unlink()

  with tempfile.TemporaryDirectory() as work_dir:
    empty_cc = pathlib.Path(work_dir).joinpath('empty.cc')
    empty_cc.touch()

    cl = shutil.which('cl.exe', path=env['PATH'])
    link = shutil.which('link.exe', path=env['PATH'])
    rc = shutil.which('rc.exe', path=env['PATH'])

    exec_command([cl, '/nologo', '/c', '/Foempty_arm64.obj', 'empty.cc'], cwd=work_dir, env=env, dryrun=args.dryrun)
    exec_command([cl, '/nologo', '/c', '/arm64EC', '/Foempty_x64.obj', 'empty.cc'], cwd=work_dir, env=env, dryrun=args.dryrun)

    mozc_x64_def = pathlib.Path(work_dir).joinpath('mozc_x64.def')
    mozc_x64_def.write_text(info.get_def_file_content_for_x64(), encoding='utf-8', newline='\r\n')

    exec_command([link, '/lib', '/nologo', '/machine:arm64EC', '/ignore:4104', '/def:mozc_x64.def', '/out:mozc_x64.lib'], cwd=work_dir, env=env, dryrun=args.dryrun)
    mozc_arm64_def = pathlib.Path(work_dir).joinpath('mozc_arm64.def')
    mozc_arm64_def.write_text(info.get_def_file_content_for_arm64(), encoding='utf-8', newline='\r\n')
    exec_command([link, '/lib', '/nologo', '/machine:arm64', '/ignore:4104', '/def:mozc_arm64.def', '/out:mozc_arm64.lib'], cwd=work_dir, env=env, dryrun=args.dryrun)

    rc_file = pathlib.Path(work_dir).joinpath('mozc_tip_shim.rc')
    rc_file.write_text(info.get_rc_file_content(), encoding='utf-8', newline='\r\n')

    exec_command([
        rc, '/nologo', '/r', '/8', str(rc_file)], cwd=work_dir, env=env, dryrun=args.dryrun)

    forwarder_filename = pathlib.Path(info.forwarder_dll_name).name
    exec_command([
        link, '/dll', '/nologo', '/noentry', '/machine:arm64x', '/emitpogophaseinfo',
        '/largeaddressaware', '/dynamicbase', '/highentropyva', '/ignore:4104',
        '/defArm64Native:mozc_arm64.def', '/def:mozc_x64.def', f'/out:{forwarder_filename}',
        'empty_arm64.obj', 'empty_x64.obj', 'mozc_arm64.lib', 'mozc_x64.lib',
        'mozc_tip_shim.res'], cwd=work_dir, env=env, dryrun=args.dryrun)

    src = pathlib.Path(work_dir).joinpath(forwarder_filename)
    if args.dryrun:
      print(f'dryrun: Copying {src} to {dest}')
    else:
      shutil.copy2(src=src, dst=dest)


def main():
  args = parse_args()

  if is_windows():
    build_on_windows(args)


if __name__ == '__main__':
  main()
