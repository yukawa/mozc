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

#ifndef MOZC_BASE_STRINGS_SAFE_GLOBAL_STRING_H_
#define MOZC_BASE_STRINGS_SAFE_GLOBAL_STRING_H_

#include <array>
#include <atomic>
#include <type_traits>
#include <string>
#include <string_view>

namespace mozc {

template <size_t fixed_array_size, typename CharT = char>
requires std::same_as<CharT, char> || std::same_as<CharT, wchar_t>
class SafeGlobalString {
 public:
  using StringT = std::basic_string<CharT>;
  using StringViewT = std::basic_string_view<CharT>;

  // A data initializer that is guaranteed to return the same value no matter
  // How many times it is called.
  using IdempotentInitializer = StringT(*)();

  SafeGlobalString() = delete;
  ~SafeGlobalString() = default;

  consteval SafeGlobalString(IdempotentInitializer idempotent_initializer)
      : idempotent_initializer_(idempotent_initializer) {
    static_assert(
        std::is_trivially_destructible_v<decltype(*this)>,
        "Must be trivially destructible.");
  }

  StringViewT Get() {
    // Fast path: check if already initialized.
    if (initialized_.load(std::memory_order::seq_cst)) [[likely]] {
      if (leaking_fallback_buffer_ == nullptr) [[likely]] {
        return StringViewT(value_.data(), size_);
      } else {
        return StringViewT(leaking_fallback_buffer_, size_);
      }
    }

    // Slow path: Executing `idempotent_initializer_` multiple times is
    // acceptable, compared to introducing the risk of potential dead lock when
    // trying to ensure only-once semantics.
    //
    // Win32 Loader lock is a good example. Consider this method is called from
    // DllMain and some worker thread at the same time and
    // `idempotent_initializer_` internally calls `LoadLibrary` Win32 API.
    // In this scenario, `idempotent_initializer_` can complete only when called
    // from DllMain, which already acquires Win32 Loader Lock.
    // https://learn.microsoft.com/en-us/windows/win32/dlls/dynamic-link-library-best-practices#deadlocks-caused-by-lock-order-inversion
    const StringT value = idempotent_initializer_();
    const size_t size = value.size();

    StringViewT result;
    if (size <= std::size(value_)) [[likely]] {
      // OK to race with other thread, as long as the same result is written.
      for (size_t i = 0; i < size; ++i) {
        value_[i] = value[i];
      }
      result = StringViewT(value_.data(), size);
    } else {
      CharT* buffer = new CharT[size];
      for (size_t i = 0; i < size; ++i) {
        buffer[i] = value[i];
      }
      result = StringViewT(buffer, size);
      // Accept to leak the memory.
      leaking_fallback_buffer_ = buffer;
    }
    size_ = size;
    initialized_.store(true, std::memory_order::seq_cst);
    return result;
  }

 private:
  std::atomic<bool> initialized_ = {};
  size_t size_ = 0;
  CharT* leaking_fallback_buffer_ = nullptr;
  std::array<CharT, fixed_array_size> value_ = {};
  const IdempotentInitializer idempotent_initializer_;
};

}  // namespace mozc

#endif  // MOZC_BASE_STRINGS_SAFE_GLOBAL_STRING_H_
