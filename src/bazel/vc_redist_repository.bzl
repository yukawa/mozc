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

"""Repository rule for Visual C++ redistribution files."""

_VC_REDIT_BUILD = """
package(
    default_visibility = ["//visibility:public"],
)

exports_files([
    "x64/Microsoft.VC143.CRT/msvcp140.dll",
    "x64/Microsoft.VC143.CRT/msvcp140_1.dll",
    "x64/Microsoft.VC143.CRT/msvcp140_2.dll",
    "x64/Microsoft.VC143.CRT/vcruntime140.dll",
    "x64/Microsoft.VC143.CRT/vcruntime140_1.dll",
])
"""

def _get_path_env_var(repo_ctx, name):
    """Returns a path from an environment variable with removing quotes."""

    value = repo_ctx.getenv(name)
    if value == None:
        return None

    if value[0] == "\"" and len(value) > 1 and value[-1] != "\"":
        value = value[1:-1]
    if "/" in value:
        value = value.replace("/", "\\")
    if value[-1] == "\\":
        value = value.rstrip("\\")
    return value


def _get_vc_tools_regist_dir(repo_ctx):
    is_windows = repo_ctx.os.name.lower().startswith("win")
    if not is_windows:
        return None

    program_files_x86 = _get_path_env_var(repo_ctx, "ProgramFiles(x86)")
    vswhere_path = program_files_x86 + r"\Microsoft Visual Studio\Installer\vswhere.exe"
    if not repo_ctx.path(vswhere_path).exists:
        return None

    cmd = [
        vswhere_path,
        '-products',
        'Microsoft.VisualStudio.Product.Enterprise',
        'Microsoft.VisualStudio.Product.Professional',
        'Microsoft.VisualStudio.Product.Community',
        'Microsoft.VisualStudio.Product.BuildTools',
        '-requires',
        'Microsoft.VisualStudio.Component.VC.Redist.14.Latest',
        '-find',
        'VC/Auxiliary/Build/vcvarsall.bat',
        '-utf8',
    ]
    result = repo_ctx.execute(cmd)
    if result.stderr:
        return None
    vcvarsall_path = result.stdout.split("\n")[0]
    if not repo_ctx.path(vcvarsall_path).exists:
        return None

    cmd_path = _get_path_env_var(repo_ctx, "ComSpec")
    if not repo_ctx.path(cmd_path).exists:
        return None

    result = repo_ctx.execute([
        cmd_path,
        "(\"" + vcvarsall_path + "\" x64>nul)&&set",
    ])
    if result.stderr:
        return None
    for line in result.stdout.split("\n"):
        line = line.strip()
        if not line.upper().startswith("VCTOOLSREDISTDIR="):
            continue
        redist_dir = line[17:]
        break
    if redist_dir[-1] == "\\":
        redist_dir = redist_dir.rstrip("\\")
    return redist_dir


def _vc_redistribution_repository_impl(repo_ctx):
    redist_dir = _get_vc_tools_regist_dir(repo_ctx)
    if not redist_dir:
        repo_ctx.file("BUILD.bazel", "", executable = False)
        return

    repo_ctx.symlink(redist_dir.get_child("x86"), "x86")
    repo_ctx.symlink(redist_dir.get_child("x64"), "x64")
    repo_ctx.file("BUILD.bazel", _VC_REDIT_BUILD, executable = False)


vc_redist_repository = repository_rule(
    implementation = _vc_redistribution_repository_impl,
    configure = True,
    local = True,
    environ = ["ComSpec", "ProgramFiles(x86)"],
)
