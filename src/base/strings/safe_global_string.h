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

#include "base/strings/zstring_view.h"

namespace mozc {

// A utility class to deal with global strings with the following capabilities:
// 1. It allows the library users to lazily initialize the string by calling
//    `GetOrInit()` only after it becomes ready, e.g. only after dependent
//    modules are fully loaded.
// 2. It is thread-safe, meaning that multiple threads can call `GetOrInit()`
//    concurrently without causing data race, with an assumption that the
//    `idempotent_initializer` is idempotent (i.e., it always returns the same
//    value when called multiple times) and thread-safe.
// 3. It guarantees that the string is null-terminated.
// 4. It is trivially destructible, which means it can be used in static
//    storage duration objects without causing destructor order issues, with a
//    caveat that it may leak memory if the string is larger than the fixed
//    array size provided by the template parameter.
template <size_t fixed_array_size, typename CharT = char>
requires std::same_as<CharT, char> || std::same_as<CharT, wchar_t>
class SafeGlobalString {
 public:
  using StringT = std::basic_string<CharT>;
  using StringViewT = std::basic_string_view<CharT>;
  using ZStringViewT = ::mozc::basic_zstring_view<StringViewT>;

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

  ZStringViewT GetOrInit() {
    // Fast path: check if already initialized.
    if (initialized_.load(std::memory_order::acquire)) [[likely]] {
      if (leaking_fallback_buffer_ == nullptr) [[likely]] {
        return ZStringViewT(value_.data(), size_without_null_);
      } else {
        return ZStringViewT(leaking_fallback_buffer_, size_without_null_);
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
    const CharT* value_ptr = value.c_str();
    const size_t size_without_null = value.size();
    const size_t size_with_null = size_without_null + 1;

    const CharT* result_ptr = nullptr;
    if (size_with_null <= std::size(value_)) [[likely]] {
      // OK to race with other thread, as long as the same result is written.
      for (size_t i = 0; i < size_with_null; ++i) {
        value_[i] = value_ptr[i];
      }
      result_ptr = value_.data();
    } else {
      CharT* buffer = new CharT[size_with_null];
      for (size_t i = 0; i < size_with_null; ++i) {
        buffer[i] = value_ptr[i];
      }
      // Accept to leak the memory.
      leaking_fallback_buffer_ = buffer;
      result_ptr = buffer;
    }
    size_without_null_ = size_without_null;
    initialized_.store(true, std::memory_order::release);
    return ZStringViewT(result_ptr, size_without_null_);
  }

 private:
  std::atomic<bool> initialized_ = {};
  size_t size_without_null_ = 0;
  CharT* leaking_fallback_buffer_ = nullptr;
  std::array<CharT, fixed_array_size> value_ = {};
  const IdempotentInitializer idempotent_initializer_;
};

}  // namespace mozc

#endif  // MOZC_BASE_STRINGS_SAFE_GLOBAL_STRING_H_
