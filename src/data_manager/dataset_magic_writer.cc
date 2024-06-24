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

// Tool to pack multiple files into one file.
//
// Usage
// $ ./path/to/artifacts/dataset_writer_main
//   --magic=\xNN\xNN\xNN
//   --output=/path/to/output
//   [arg1, [arg2, ...]]
//
// Here, each argument has the following form:
//
// name:alignment:/path/to/infile
//
// where alignment must be a power of 2 greater than or equal to 8 (i.e., 8, 16,
// 32, 64, ...). Each packed file can be retrieved by DataSetReader through its
// name.

#include <ios>
#include <string>
#include <vector>

#include "absl/flags/flag.h"
#include "absl/log/check.h"
#include "absl/status/status.h"
#include "absl/strings/escaping.h"
#include "absl/strings/match.h"
#include "absl/strings/str_split.h"
#include "absl/strings/string_view.h"
#include "base/file_stream.h"
#include "base/file_util.h"
#include "base/init_mozc.h"
#include "base/vlog.h"

ABSL_FLAG(std::string, name, "", "The name of the data set");
ABSL_FLAG(std::string, magic, "", "Hex-encoded magic number to be embedded");
ABSL_FLAG(std::string, output, "", "Output file");

int main(int argc, char **argv) {
  mozc::InitMozc(argv[0], &argc, &argv);

  std::string magic;
  CHECK(absl::CUnescape(absl::GetFlag(FLAGS_magic), &magic))
      << "magic number is not a proper hex-escaped string: "
      << absl::GetFlag(FLAGS_magic);

  CHECK(!absl::GetFlag(FLAGS_output).empty()) << "--output is required";
  CHECK(!absl::GetFlag(FLAGS_name).empty()) << "--name is required";

  // Here we directly write to the specified stream, so if it fails for
  // an input, the output contains a partial result.  To avoid such partial file
  // creation, write to a temporary file then rename it.
  const std::string tmpfile = absl::GetFlag(FLAGS_output) + ".tmp";
  {
    mozc::OutputFileStream output(tmpfile, std::ios_base::out);

    const std::string macro_name =
        "MOZC_DATASET_MAGIC_" + absl::GetFlag(FLAGS_name);

    output
        << "#ifdef " + macro_name << "\n"
        << "#error \"kMagicNumber was already included or defined elsewhere\"\n"
        << "#else\n"
        << "#define " + macro_name << "\n"
        << "constexpr char kMagicNumber[] = \""
        << absl::GetFlag(FLAGS_magic) << "\";\n"
        << "#endif " + macro_name << "  // " << macro_name << std::endl;
    output.close();
  }
  absl::Status s =
      mozc::FileUtil::AtomicRename(tmpfile, absl::GetFlag(FLAGS_output));
  CHECK_OK(s) << ": Atomic rename failed. from: " << tmpfile
              << " to: " << absl::GetFlag(FLAGS_output);

  return 0;
}
