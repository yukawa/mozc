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

"""Repository rule for Linux libraries configured by `pkg-config`.

Note, this rule supports only necessary functionaries of pkg-config for Mozc.
Generated `BUILD.bazel` is available at `bazel-src/external/<repository_name>`.

## Example of usage
```:WORKSPACE.bazel
pkg_config_repository(
  name = "ibus",
  packages = ["glib-2.0", "gobject-2.0", "ibus-1.0"],
)
```

```:BUILD.bazel
cc_library(
    name = "ibus_client",
    deps = [
        "@ibus//:ibus",
        ...
    ],
    ...
)
```
"""

BUILD_TEMPLATE = """
package(
    default_visibility = ["//visibility:public"],
)

cc_library(
    name = "{name}",
    hdrs = glob([
        {hdrs}
    ]),
    copts = [
        {copts}
    ],
    includes = [
        {includes}
    ],
    linkopts = [
        {linkopts}
    ],
)
"""

EXPORTS_FILES_TEMPLATE = """
exports_files(glob(["libexec/*"], allow_empty=True))
"""

def _itemize_pkg_config_result(result):
    """Get the list of items in pkg-config result with removing duplicate items.

    Args:
      result: the returned object from repo_ctx.execute.
    Returns:
      list: a string list that is constructed by splitting the result with
            space. An empty list if the command failed.
    """
    if result.return_code != 0:
        return []

    # Dedup with keeping the original order.
    items = []
    for item in result.stdout.strip().split(" "):
        if item and (item not in items):
            items.append(item)
    return items

def _make_strlist(list):
    return "\"" + "\",\n        \"".join(list) + "\""

def _symlinks(repo_ctx, paths):
    for path in paths:
        if repo_ctx.path(path).exists:
            continue
        repo_ctx.symlink("/" + path, path)

def _pkg_config_repository_impl(repo_ctx):
    # Do nothing for macOS and Windows.
    for os in ["mac", "win"]:
        if repo_ctx.os.name.lower().startswith(os):
            repo_ctx.file("BUILD.bazel", "")
            return

    pkg_config = repo_ctx.which("pkg-config")
    if not pkg_config:
        fail("pkg-config is not found")

    packages = repo_ctx.attr.packages

    missing_package_found = False
    for pkg in packages:
        if repo_ctx.execute([pkg_config, "--exists", pkg]).return_code != 0:
            print("Missing package: " + pkg)  # buildifier: disable=print
            missing_package_found = True

    if missing_package_found:
        repo_ctx.file("BUILD.bazel", "")
        return

    includes = _itemize_pkg_config_result(
        repo_ctx.execute([pkg_config, "--cflags-only-I"] + packages),
    )

    # If includes is empty, pkg-config will be re-executed with
    # the --keep-system-cflags option added. Typically, -I/usr/include is
    # returned, enabling bazel to recognize packages as valid even when
    # pkg-config does not output cflags with standard options.
    if not includes:
        includes = _itemize_pkg_config_result(repo_ctx.execute(
            [pkg_config, "--cflags-only-I", "--keep-system-cflags"] + packages,
        ))
    includes = [item[len("-I/"):] for item in includes]
    _symlinks(repo_ctx, includes)
    data = {
        # In bzlmod, repo_ctx.attr.name has a prefix like "_main~_repo_rules~ibus".
        # Note also that Bazel 8.0+ uses "+" instead of "~".
        # https://github.com/bazelbuild/bazel/issues/23127
        "name": repo_ctx.attr.name.replace("~", "+").split("+")[-1],
        "hdrs": _make_strlist([item + "/**" for item in includes]),
        "copts": _make_strlist(_itemize_pkg_config_result(
            repo_ctx.execute([pkg_config, "--cflags-only-other"] + packages),
        )),
        "includes": _make_strlist(includes),
        "linkopts": _make_strlist(_itemize_pkg_config_result(
            repo_ctx.execute([pkg_config, "--libs-only-l"] + packages),
        )),
    }
    build_file_data = BUILD_TEMPLATE.format(**data)

    libexecdir = _itemize_pkg_config_result(
        repo_ctx.execute([pkg_config, "--variable=libexecdir"] + packages),
    )
    if len(libexecdir) == 1:
        repo_ctx.symlink(libexecdir[0], "libexec")
        build_file_data += EXPORTS_FILES_TEMPLATE

    repo_ctx.file("BUILD.bazel", build_file_data)

pkg_config_repository = repository_rule(
    implementation = _pkg_config_repository_impl,
    configure = True,
    local = True,
    attrs = {
        "packages": attr.string_list(),
    },
)
