import argparse
import os
import pathlib
import subprocess

from build_tools import vs_util
from build_tools import mozc_version

ABS_SCRIPT_PATH = pathlib.Path(__file__).absolute()
# src/win32/installer/build_installer.py -> src/
ABS_MOZC_SRC_DIR = ABS_SCRIPT_PATH.parents[2]
ABS_DOCUMENT_DIR = pathlib.Path(ABS_MOZC_SRC_DIR).joinpath('installer')
ABS_QT_DIR = pathlib.Path(ABS_MOZC_SRC_DIR).joinpath('third_paty').joinpath('qt')
TIMEOUT = 600


def exec_command(args: list[str], cwd: os.PathLike) -> None:
  """Runs the given command then returns the output.

  Args:
    args: The command to be executed.

  Raises:
    ChildProcessError: When the given command cannot be executed.
  """
  commands = ' '.join(args)
  process = subprocess.Popen(
    args,
    stdout=subprocess.PIPE,
    stderr=subprocess.PIPE,
    shell=False,
    text=True,
    encoding="utf-8",
    cwd=cwd)
  stdout, stderr = process.communicate()
  exitcode = process.wait()

  if exitcode != 0:
    command = ' '.join(args)
    msgs = [f'Failed to execute command:', '', f'{command}', '', f'cwd={cwd}']
    if len(stdout) > 0:
      msgs += ['-----stdout-----', stdout]
    if len(stderr) > 0:
      msgs += ['-----stderr-----', stderr]
    raise ChildProcessError('\n'.join(msgs))


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
  mozc_tip32 = pathlib.Path(args.mozc_tip32).resolve()
  mozc_tip64 = pathlib.Path(args.mozc_tip64).resolve()
  mozc_broker = pathlib.Path(args.mozc_broker).resolve()
  mozc_server = pathlib.Path(args.mozc_server).resolve()
  mozc_cache_service = pathlib.Path(args.mozc_cache_service).resolve()
  mozc_renderer = pathlib.Path(args.mozc_renderer).resolve()
  mozc_tool = pathlib.Path(args.mozc_tool).resolve()
  custom_action = pathlib.Path(args.custom_action).resolve()
  commands = [
    'dotnet', 'tool', 'run', 'wix',
    'build',
    '-nologo',
    '-arch', 'x64',
    '-define', f'MozcVersion={version.GetVersionString()}',
    '-define', 'UpgradeCode=DD94B570-B5E2-4100-9D42-61930C611D8A',
    '-define', 'OmahaGuid=',
    '-define', 'OmahaClientKey=',
    '-define', 'OmahaClientStateKey=',
    '-define', 'OmahaChannelType=dev',
    '-define', 'VSConfigurationName=Release',
    '-define', f'ReleaseRedistCrt32Dir={redist_x86}',
    '-define', f'ReleaseRedistCrt64Dir={redist_x64}',
    '-define', f'AddRemoveProgramIconPath={icon_path}',
    '-define', f'MozcTIP32Path={mozc_tip32}',
    '-define', f'MozcTIP64Path={mozc_tip64}',
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
  parser.add_argument('--mozc_tip32', type=str)
  parser.add_argument('--mozc_tip64', type=str)
  parser.add_argument('--custom_action', type=str)
  parser.add_argument('--icon_path', type=str)
  parser.add_argument('--credit_file', type=str)
  parser.add_argument('--qt_core_dll', type=str)
  parser.add_argument('--wxs_path', type=str)

  args = parser.parse_args()

  run_wix4(args)


if __name__ == '__main__':
  main()
