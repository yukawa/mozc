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

"""A helper script to use Visual Studio."""

import ctypes
import json
import os
import pathlib
import platform
import subprocess
import sys
from typing import Optional, Union


def _get_win_machine_arch_with_api() -> Optional[str]:
    """Get the machine architecture on Windows with `IsWow64Process2` API.

    This function uses the `IsWow64Process2` Win32 API to determine the host
    CPU architecture. Note that the API is available starting from
    Windows 10 version 1709 (build 16299).

    Returns:
        str: The host architecture, e.g., 'X86', 'AMD64', 'ARM64', or None if
        the architecture cannot be determined or if the platform is not
        Windows.
    """
    kernel32 = ctypes.windll.kernel32
    IsWow64Process2 = kernel32.IsWow64Process2
    if not IsWow64Process2:
        # IsWow64Process2 is available starting from Windows 10 version 1709
        return None

    process_machine = ctypes.c_ushort()
    native_machine = ctypes.c_ushort()
    result = IsWow64Process2(
        ctypes.c_void_p(kernel32.GetCurrentProcess()),
        ctypes.byref(process_machine),
        ctypes.byref(native_machine)
    )

    if not result:
        raise None

    # Use native_machine for host architecture
    return {
        0x014c: 'X86',
        0x8664: 'AMD64',
        0xAA64: 'ARM64',
    }.get(native_machine.value, None)


def get_win_machine_arch() -> Optional[str]:
    """Get the machine architecture on Windows in a reliable way.

    On CPython 3.11.* or prior, `platform.uname().machine` can return an empty
    string when used in Bazel's sandboxed action environment, where
    `PROCESSOR_ARCHITECTURE` and `PROCESSOR_ARCHITEW6432` environment variables
    are not set by default unless explicitly specified with `--action_env`
    command line option. As you can see below, the `machine` field of
    `platform.uname()` is just a wrapper around the `PROCESSOR_ARCHITECTURE`
    environment variable in these versions of CPython:

      https://github.com/python/cpython/blob/3.9/Lib/platform.py#L729-L739

    To work around the above limitation, this function first uses the
    `IsWow64Process2` Win32 API to determine the system's CPU architecture, then
    falls back to `platform.uname().machine` only if the API call fails
    including the case when the API is not available (e.g., on Windows 10
    version 1703 or earlier).

    Note that on CPython 3.12.0 and later `platform.uname().machine` seems to
    work even in Bazel's sandboxed action environment, as it now tries to query
    the system's CPU architecture with WMI then falling back to
    `PROCESSOR_ARCHITECTURE` environment variable only when the WMI query fails.

      https://github.com/python/cpython/commit/de33df27aaf930be6a34027c530a651f0b4c91f5

    Returns:
        str: The host architecture, e.g., 'X86', 'AMD64', 'ARM64', or None if
        the architecture cannot be determined or if the platform is not
        Windows.
    """
    if os.name != 'nt':
        # This function is intended to be used only on Windows.
        return None

    return _get_win_machine_arch_with_api() or platform.uname().machine


def normalize_win_arch(arch: Optional[str]) -> Optional[str]:
  """Normalize the architecture name for Windows build environment.

  Args:
    arch: a string representation of a CPU architecture to be normalized.

  Returns:
    String representation of a CPU architecture (e.g. 'x64' and 'arm64').
    Returns None if the input is None or empty.
  """
  if not arch:
    return None
  normalized = arch.lower()
  if normalized == 'amd64':
    return 'x64'
  return normalized


def get_vcvarsall(
    arch: str, path_hint: Union[str, None] = None
) -> pathlib.Path:
  """Returns the path of 'vcvarsall.bat'.

  Args:
    arch: host/target architecture
    path_hint: optional path to vcvarsall.bat

  Returns:
    The path of 'vcvarsall.bat'.

  Raises:
    FileNotFoundError: When 'vcvarsall.bat' cannot be found.
    ChildProcessError: When 'vcvarsall.bat' cannot be executed.
  """
  if path_hint is not None:
    path = pathlib.Path(path_hint).resolve()
    if path.exists():
      return path
    raise FileNotFoundError(
        f'Could not find vcvarsall.bat. path_hint={path_hint}'
    )

  program_files_x86 = os.environ.get('ProgramFiles(x86)')
  if not program_files_x86:
    program_files_x86 = r'C:\Program Files (x86)'

  vswhere_path = pathlib.Path(program_files_x86).joinpath(
      'Microsoft Visual Studio', 'Installer', 'vswhere.exe'
  )
  if not vswhere_path.exists():
    raise FileNotFoundError(
        'Could not find vswhere.exe.'
        'Consider using --vcvarsall_path option e.g.\n'
        r' --vcvarsall_path=C:\VS\VC\Auxiliary\Build\vcvarsall.bat'
    )

  cmd = [
      str(vswhere_path),
      '-products',
      'Microsoft.VisualStudio.Product.Enterprise',
      'Microsoft.VisualStudio.Product.Professional',
      'Microsoft.VisualStudio.Product.Community',
      'Microsoft.VisualStudio.Product.BuildTools',
      '-find',
      'VC/Auxiliary/Build/vcvarsall.bat',
      '-utf8',
  ]
  cmd += [
      '-requires',
      'Microsoft.VisualStudio.Component.VC.Redist.14.Latest',
  ]
  if arch.endswith('arm64'):
    cmd += ['Microsoft.VisualStudio.Component.VC.Tools.ARM64']

  process = subprocess.Popen(
      cmd,
      stdout=subprocess.PIPE,
      stderr=subprocess.PIPE,
      shell=False,
      text=True,
      encoding='utf-8',
  )
  stdout, stderr = process.communicate()
  exitcode = process.wait()
  if exitcode != 0:
    msgs = ['Failed to execute vswhere.exe']
    if stdout:
      msgs += ['-----stdout-----', stdout]
    if stderr:
      msgs += ['-----stderr-----', stderr]
    raise ChildProcessError('\n'.join(msgs))

  lines = stdout.splitlines()
  if len(lines) > 0:
    vcvarsall = pathlib.Path(lines[0])
    if vcvarsall.exists():
      return vcvarsall

  msg = 'Could not find vcvarsall.bat.'
  if arch.endswith('arm64'):
    msg += (
        ' Make sure Microsoft.VisualStudio.Component.VC.Tools.ARM64 is'
        ' installed.'
    )
  else:
    msg += (
        ' Consider using --vcvarsall_path option e.g.\n'
        r' --vcvarsall_path=C:\VS\VC\Auxiliary\Build\vcvarsall.bat'
    )
  raise FileNotFoundError(msg)


def get_vs_env_vars(
    target_arch: str,
    vcvarsall_path_hint: Union[str, None] = None,
) -> dict[str, str]:
  """Returns environment variables for the specified Visual Studio C++ tool.

  Oftentimes commandline build process for Windows requires to us to set up
  environment variables (especially 'PATH') first by executing an appropriate
  Visual C++ batch file ('vcvarsall.bat').  As a result, commands to be passed
  to methods like subprocess.run() can easily become complicated and difficult
  to maintain.

  With get_vs_env_vars() you can easily decouple environment variable handling
  from the actual command execution as follows.

    cwd = ...
    env = get_vs_env_vars('x86')
    subprocess.run(command_fullpath, shell=False, check=True, cwd=cwd, env=env)

  or

    cwd = ...
    env = get_vs_env_vars('x64')
    subprocess.run(command, shell=True, check=True, cwd=cwd, env=env)

  Args:
    target_arch: The architecture to be used, e.g. 'x64', 'x86', 'arm64'
    vcvarsall_path_hint: optional path to vcvarsall.bat

  Returns:
    A dict of environment variable.

  Raises:
    ChildProcessError: When 'vcvarsall.bat' cannot be executed.
    EnvironmentError: When the host architecture cannot be determined.
    FileNotFoundError: When 'vcvarsall.bat' cannot be found.
    ValueError: When the target architecture is invalid.
  """
  target_arch = normalize_win_arch(target_arch)
  if target_arch not in ('x86', 'x64', 'arm64'):
    raise ValueError(
        f'Invalid target architecture: {target_arch}. '
        'Supported architectures are: x86, x64, arm64.'
    )

  host_arch = normalize_win_arch(get_win_machine_arch())
  if host_arch not in ('x86', 'x64', 'arm64'):
    raise EnvironmentError(
        'Failed to determine the host architecture. '
        'Make sure you are running this script on a Windows machine.'
    )

  arch = host_arch if host_arch == target_arch else f'{host_arch}_{target_arch}'
  vcvarsall = get_vcvarsall(arch, vcvarsall_path_hint)

  pycmd = (
      r'import json;'
      r'import os;'
      r'print(json.dumps(dict(os.environ), ensure_ascii=True))'
  )
  cmd = f'("{vcvarsall}" {arch}>nul)&&("{sys.executable}" -c "{pycmd}")'
  process = subprocess.Popen(cmd, stdout=subprocess.PIPE, shell=True)
  stdout, _ = process.communicate()
  exitcode = process.wait()
  if exitcode != 0:
    raise ChildProcessError(f'Failed to execute {vcvarsall}')
  return json.loads(stdout.decode('ascii'))
