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

#include "base/singleton.h"

#include <array>

#include "absl/base/const_init.h"
#include "absl/base/thread_annotations.h"
#include "absl/log/log.h"
#include "absl/synchronization/mutex.h"

namespace mozc {
namespace internal {
namespace {

constinit absl::Mutex mu(absl::kConstInit);
constinit std::array<void (*)(void), 256> finalizers
    ABSL_GUARDED_BY(mu) = {};
constinit int size ABSL_GUARDED_BY(mu) = 0;

}  // namespace

void AddSingletonFinalizer(void (*finalizer)()) ABSL_LOCKS_EXCLUDED(mu) {
  absl::MutexLock lock(&mu);
  if (size >= finalizers.size()) {
    LOG(FATAL) << "Too many singletons";
  }
  finalizers[size++] = finalizer;
}

}  // namespace internal

void FinalizeSingletons() ABSL_LOCKS_EXCLUDED(internal::mu) {
  absl::MutexLock lock(&internal::mu);
  for (auto func : internal::finalizers) {
    func();
  }
  internal::size = 0;
}

}  // namespace mozc
