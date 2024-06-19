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

"""Repository rule for Qt for Windows."""

BUILD_TEMPLATE = """
package(
    default_visibility = ["//visibility:public"],
)

cc_library(
    name = "qt_win",
    hdrs = glob([
        "include"
    ]),
    includes = [
        "include",
        "include/QtCore",
        "include/QtGui",
        "include/QtWidgets",
    ],
#    linkopts = select({
#        "//tools/compilation_mode:dbg": [
#            "Qt6Cored.lib",
#            "Qt6Guid.lib",
#            "Qt6Widgetsd.lib",
#        ],
#        "//conditions:default": [
#            "Qt6Core.lib",
#            "Qt6Gui.lib",
#            "Qt6Widgets.lib",
#        ],
#    }),
    linkopts = [
        "Qt6Core.lib",
        "Qt6Gui.lib",
        "Qt6Widgets.lib",
    ],
)

exports_files([
    "bin/moc.exe",
    "bin/uic.exe",
    "bin/rcc.exe",
])
"""

def _qt_win_repository_impl(repo_ctx):
    is_win = repo_ctx.os.name.lower().startswith("win")
    if not is_win:
        repo_ctx.file("BUILD.bazel", "")
        return

    qt_path = repo_ctx.path("C:/Users/micro/source/repos/mozc/src/third_party/qt")
    repo_ctx.symlink(qt_path.get_child("bin"), "bin")
    repo_ctx.symlink(qt_path.get_child("include"), "include")
    repo_ctx.symlink(qt_path.get_child("lib"), "lib")
    repo_ctx.symlink(qt_path.get_child("plugins"), "plugins")

    repo_ctx.file("BUILD.bazel", BUILD_TEMPLATE)

qt_win_repository = repository_rule(
    implementation = _qt_win_repository_impl,
    configure = True,
    local = True,
)
