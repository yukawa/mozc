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

"""
A macro to generate import libraries for Win32 DLLs such as input.dll and
msctf.dll, whose import libraries are not included in the Windows SDK.
"""

load(
    "//:build_defs.bzl",
    "MOZC_TAGS",
    "mozc_cc_binary",
    "mozc_cc_library",
)
load("@rules_cc//cc:defs.bzl", "cc_import")

def mozc_cc_win32_library(
        name,
        srcs = [],
        hdrs = [],
        win_def_file = None,
        visibility = None,
        **kwargs):
    """A rule to build an DLL import library for Win32 system DLLs"""
    # A DLL name, which actually will not be used in production.
    # e.g. "input_dll_fake.dll" vs "C:\Windows\System32\input.dll"
    # The actual DLL name should be specified in the LIBRARY section of
    # win_def_file.
    # https://learn.microsoft.com/en-us/cpp/build/reference/library
    cc_binary_target_name = name + "_fake.dll"
    filegroup_target_name = name + "_lib"
    cc_import_taget_name = name + "_import"

    mozc_cc_binary(
        name = cc_binary_target_name,
        srcs = srcs,
        deps = [],
        win_def_file = win_def_file,
        linkshared = 1,
        tags = MOZC_TAGS.WIN_ONLY,
        target_compatible_with = ["@platforms//os:windows"],
        **kwargs
    )

    native.filegroup(
        name = filegroup_target_name,
        srcs = [":" + cc_binary_target_name],
        output_group = "interface_library",
        tags = MOZC_TAGS.WIN_ONLY,
        target_compatible_with = ["@platforms//os:windows"],
    )

    cc_import(
        name = cc_import_taget_name,
        interface_library = ":" + filegroup_target_name,
        shared_library = ":" + cc_binary_target_name,
        tags = MOZC_TAGS.WIN_ONLY,
        target_compatible_with = ["@platforms//os:windows"],
    )

    mozc_cc_library(
        name = name,
        hdrs = hdrs,
        visibility = visibility,
        deps = [":" + cc_import_taget_name],
        tags = MOZC_TAGS.WIN_ONLY,
        target_compatible_with = ["@platforms//os:windows"],
    )
