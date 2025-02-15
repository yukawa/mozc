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
from collections.abc import Iterator
import dataclasses
import functools
import os
import pathlib
import platform
import shutil
import subprocess
import sys
import tarfile
import tempfile
import time
from typing import Any, Union
from vs_util import get_vs_env_vars


ABS_SCRIPT_PATH = pathlib.Path(__file__).absolute()


def is_windows() -> bool:
  """Returns true if the platform is Windows."""
  return os.name == 'nt'


def parse_args() -> argparse.Namespace:
  """Parse command line options."""
  parser = argparse.ArgumentParser()
  parser.add_argument('--dryrun', action='store_true', default=False)
  return parser.parse_args()


def get_def_file_content(filename:str) -> str:
  return '\n'.join([
    'EXPORTS',
    f'    DllGetClassObject = {filename}.DllGetClassObject',
    f'    DllCanUnloadNow   = {filename}.DllCanUnloadNow',
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
  host_arch = normalize_win_arch(platform.uname().machine)

  target_arch = 'arm64'
  arch = host_arch if host_arch == target_arch else f'{host_arch}_{target_arch}'
  env = get_vs_env_vars(arch)

  with tempfile.TemporaryDirectory() as work_dir:
    empty_cc = pathlib.Path(work_dir).joinpath('empty.cc')
    empty_cc.touch()

    cl = shutil.which('cl.exe', path=env['PATH'])
    link = shutil.which('link.exe', path=env['PATH'])

    exec_command([cl, '/nologo', '/c', '/Foempty_arm64.obj', 'empty.cc'], cwd=work_dir, env=env, dryrun=args.dryrun)
    exec_command([cl, '/nologo', '/c', '/arm64EC', '/Foempty_x64.obj', 'empty.cc'], cwd=work_dir, env=env, dryrun=args.dryrun)

    mozc_x64_def = pathlib.Path(work_dir).joinpath('mozc_x64.def')
    mozc_x64_def.write_text(get_def_file_content('mozc_x64'))

    mozc_arm64_def = pathlib.Path(work_dir).joinpath('mozc_arm64.def')
    mozc_arm64_def.write_text(get_def_file_content('mozc_arm64'))

    exec_command([link, '/lib', '/machine:x64', '/ignore:4104', '/def:mozc_x64.def', '/out:mozc_x64.lib'], cwd=work_dir, env=env, dryrun=args.dryrun)
    exec_command([link, '/lib', '/machine:arm64', '/ignore:4104', '/def:mozc_arm64.def', '/out:mozc_arm64.lib'], cwd=work_dir, env=env, dryrun=args.dryrun)

    exec_command([
        link, '/dll', '/noentry', '/machine:arm64x', '/ignore:4104',
        '/defArm64Native:mozc_arm64.def', '/def:mozc_x64.def', 'empty_arm64.obj', 
        'empty_x64.obj', '/out:mozc_tip_shim_arm64.dll', 'mozc_arm64.lib',
        'mozc_x64.lib'], cwd=work_dir, env=env, dryrun=args.dryrun)

    src = pathlib.Path(work_dir).joinpath('mozc_tip_shim_arm64.dll')
    dest = pathlib.Path('D:\\').joinpath('mozc_tip_shim_arm64.dll')
    # shutil.copy2(src=src, dst=dest)


def main():
  args = parse_args()

  if is_windows():
    build_on_windows(args)


if __name__ == '__main__':
  main()
