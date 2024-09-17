// Copyright 2010-2021, Google Inc.
// All rights reserved.
//
// Redistribution and use in source and binary forms, with or without
// modification, are permitted provided that the following conditions are
// met:
//
//     * Redistributions of source code must retain the above copyright
// notice, this list of conditions and the following disclaimer.
//     * Redistributions in binary form must reproduce the above
// copyright notice, this list of conditions and the following disclaimer
// in the documentation and/or other materials provided with the
// distribution.
//     * Neither the name of Google Inc. nor the names of its
// contributors may be used to endorse or promote products derived from
// this software without specific prior written permission.
//
// THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
// "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
// LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
// A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT
// OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
// SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
// LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
// DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
// THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
// (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
// OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.

#include <string>

#include "absl/flags/flag.h"
#include "absl/log/log.h"
#include "absl/strings/str_cat.h"
#include "absl/strings/str_format.h"
#include "absl/strings/string_view.h"
#include "base/file_stream.h"
#include "base/version.h"
#include "base/file_util.h"
#include "base/init_mozc.h"
#include "base/protobuf/text_format.h"
#include "protocol/win32_resource.pb.h"
#include <iostream>

ABSL_FLAG(std::string, proto_file, "", "input *.textproto file");
ABSL_FLAG(std::string, output_file, "", "output *.rc file");

namespace {

void load() {
  mozc::Win32Resource resource;

  const auto textproto_path = absl::GetFlag(FLAGS_proto_file);
  absl::StatusOr<std::string> data = mozc::FileUtil::GetContents(textproto_path);
  mozc::protobuf::TextFormat::ParseFromString(data.value(), &resource);

  const auto version_str_comma = absl::StrFormat(
        "%d,%d,%d,%d",
        mozc::Version::GetMozcVersionMajor(),
        mozc::Version::GetMozcVersionMinor(),
        mozc::Version::GetMozcVersionBuildNumber(),
        mozc::Version::GetMozcVersionRevision());
  const auto version_str_dot = absl::StrFormat(
        "%d.%d.%d.%d",
        mozc::Version::GetMozcVersionMajor(),
        mozc::Version::GetMozcVersionMinor(),
        mozc::Version::GetMozcVersionBuildNumber(),
        mozc::Version::GetMozcVersionRevision());

  const auto &version_strings = resource.version_info().version_strings(0);

  std::string content = R"(
1 VERSIONINFO
FILEVERSION )" + version_str_comma + R"(
PRODUCTVERSION )" + version_str_comma + R"(
FILEOS 0x4
FILETYPE 0x1
{
    BLOCK "StringFileInfo"
    {
        BLOCK "041104b0"
        {
            VALUE "CompanyName", ")" + version_strings.company_name(0).value() + R"("
            VALUE "FileDescription", ")" + version_strings.file_description(0).value() + R"("
            VALUE "FileVersion", ")" + version_str_dot + R"("
            VALUE "InternalName", "mozc_broker"
            VALUE "LegalCopyright", "Copyright 2024 Google LLC. All Rights Reserved."
            VALUE "OriginalFilename", "mozc_broker.exe"
            VALUE "ProductName", "Mozc"
            VALUE "ProductVersion", ")" + version_str_dot + R"("
        }
    }

    BLOCK "VarFileInfo"
    {
        VALUE "Translation", 0x0411 0x04B0
    }
})";

  mozc::FileUtil::SetContents(absl::GetFlag(FLAGS_output_file), content);
}

}  // namespace


int main(int argc, char *argv[]) {
  mozc::InitMozc(argv[0], &argc, &argv);

  load();

  return 0;
}
