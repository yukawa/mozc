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

#include "win32/base/tsf_registrar.h"

#include <atlbase.h>
#include <ktmw32.h>
#include <msctf.h>
#include <objbase.h>
#include <wil/com.h>
#include <wil/resource.h>
#include <windows.h>

#undef StrCat  // b/328804050

#include <string>
#include <string_view>

#include "absl/log/log.h"
#include "base/const.h"
#include "base/strings/zstring_view.h"
#include "base/system_util.h"
#include "base/win32/com.h"
#include "base/win32/wide_char.h"
#include "win32/base/display_name_resource.h"
#include "win32/base/tsf_profile.h"

namespace mozc {
namespace win32 {
namespace {

// The categories this text service is registered under.
// This needs to be const as the included constants are defined as const.
const GUID kCategories[] = {
    GUID_TFCAT_DISPLAYATTRIBUTEPROVIDER,     // It supports inline input.
    GUID_TFCAT_TIPCAP_COMLESS,               // It's a COM-Less module.
    GUID_TFCAT_TIPCAP_INPUTMODECOMPARTMENT,  // It supports input mode.
    GUID_TFCAT_TIPCAP_UIELEMENTENABLED,      // It supports UI less mode.
    GUID_TFCAT_TIP_KEYBOARD,                 // It's a keyboard input method.
    GUID_TFCAT_TIPCAP_IMMERSIVESUPPORT,      // It supports Metro mode.
    GUID_TFCAT_TIPCAP_SYSTRAYSUPPORT,        // It supports Win8 systray.
};

struct ComRegistryEntry {
  const zwstring_view guid_str;
  const zwstring_view dll_path;
  const zwstring_view description;
  const zwstring_view threading_model;
  const bool for_64bit;
};

struct RegistoryOpenOptions final {
  const REGSAM regsam = 0;
  const DWORD options = REG_OPTION_NON_VOLATILE;
  const HANDLE transaction_handle = nullptr;
};

class ScopedRegistry final {
 public:
  ScopedRegistry() = default;
  ~ScopedRegistry() { Close(); }

  // To simplify, make this class not-copyable and not-movable
  ScopedRegistry(const ScopedRegistry&) = delete;
  ScopedRegistry& operator=(const ScopedRegistry&) = delete;

  HKEY hkey() const {
    return key_handle_;
  }

  bool OpenIfExist(HKEY parent, const wchar_t* key,
                   const RegistoryOpenOptions& options) {
    HKEY hkey = nullptr;
    const LRESULT result =
        ::RegOpenKeyTransactedW(parent, key, options.options, options.regsam,
                                &hkey, options.transaction_handle, nullptr);
    if (result != ERROR_SUCCESS) {
      return false;
    }
    Assign(hkey);
    return true;
  }

  bool OpenOrCreate(HKEY parent, const wchar_t* key,
                    const RegistoryOpenOptions& options) {
    HKEY hkey = nullptr;
    const LRESULT result = ::RegCreateKeyTransactedW(
        parent, key, 0, nullptr, options.options, options.regsam, nullptr,
        &hkey, nullptr, options.transaction_handle, nullptr);
    if (result != ERROR_SUCCESS) {
      return false;
    }
    Assign(hkey);
    return true;
  }

  bool ExpectValue(const wchar_t* value_name,
                   zwstring_view expected_value) const {
    if (!IsValid()) {
      return false;
    }
    DWORD type = 0;
    DWORD str_bytes_with_null = 0;
    LSTATUS status =
        ::RegGetValueW(key_handle_, nullptr, value_name, RRF_RT_REG_SZ,
                                    &type, nullptr, &str_bytes_with_null);
    if (status != ERROR_SUCCESS) {
      return false;
    }
    if (type != REG_SZ) {
      return false;
    }
    std::wstring result;
    if (str_bytes_with_null <= 2) {
      return expected_value.empty();
    }
    result.resize((str_bytes_with_null / sizeof(wchar_t)) - 1);
    status = ::RegGetValueW(key_handle_, nullptr, value_name, RRF_RT_REG_SZ,
                            &type, result.data(), &str_bytes_with_null);
    if (status != ERROR_SUCCESS) {
      return false;
    }
    if (type != REG_SZ) {
      return false;
    }
    return result == expected_value;
  }

  bool SetValue(const wchar_t* value_name, zwstring_view value) const {
    if (!IsValid()) {
      return false;
    }
    if (ExpectValue(value_name, value)) {
      return true;
    }
    const DWORD str_bytes_with_null =
        static_cast<DWORD>((value.size() + 1) * sizeof(wchar_t));
    const LSTATUS status = ::RegSetValueEx(
        key_handle_, value_name, 0, REG_SZ,
        reinterpret_cast<const BYTE*>(value.c_str()), str_bytes_with_null);
    return status == ERROR_SUCCESS;
  }

  bool EnsureSubkeyAbsent(const wchar_t* subkey) {
    if (!IsValid()) {
      return false;
    }
    const LSTATUS status = ::RegDeleteTreeW(key_handle_, subkey);
    return status == ERROR_SUCCESS || status == ERROR_NOT_FOUND;
  }

  void Close() {
    if (key_handle_ != nullptr) {
      ::RegCloseKey(key_handle_);
      key_handle_ = nullptr;
    }
  }

  bool IsValid() const {
    return key_handle_ != nullptr;
  }

 private:
  void Assign(HKEY new_hkey) {
    Close();
    key_handle_ = new_hkey;
  }

  HKEY key_handle_ = nullptr;
};

bool EnsureComRegistryExist(const ComRegistryEntry& entry) {
  constexpr DWORD kTimeout = 5000;  // 5 sec.
  wil::unique_hfile transaction_handle(::CreateTransaction(
      nullptr, 0, TRANSACTION_DO_NOT_PROMOTE, 0, 0, kTimeout, nullptr));

  const REGSAM wow64_flag = entry.for_64bit ? KEY_WOW64_64KEY : KEY_WOW64_32KEY;
  const RegistoryOpenOptions options{
      .regsam = KEY_READ | KEY_WRITE | KEY_SET_VALUE | KEY_CREATE_SUB_KEY |
                KEY_ENUMERATE_SUB_KEYS | wow64_flag,
      .options = REG_OPTION_NON_VOLATILE,
      .transaction_handle = transaction_handle.get(),
  };
  ScopedRegistry clsid_key;
  if (!clsid_key.OpenIfExist(HKEY_CLASSES_ROOT, L"CLSID", options)) {
    // CLSID key does not exist.
    return false;
  }

  ScopedRegistry class_key;
  if (!class_key.OpenOrCreate(clsid_key.hkey(), entry.guid_str.c_str(),
                              options)) {
    return false;
  }
  if (!class_key.SetValue(nullptr, entry.description)) {
    return false;
  }

  ScopedRegistry in_proc_server32_key;
  if (!in_proc_server32_key.OpenOrCreate(class_key.hkey(), L"InProcServer32",
                                         options)) {
    return false;
  }
  if (!in_proc_server32_key.SetValue(nullptr, entry.dll_path)) {
    return false;
  }
  if (!in_proc_server32_key.SetValue(L"ThreadingModel",
                                     entry.threading_model)) {
    return false;
  }
  return true;
}

bool EnsureComRegistryNotExist(zwstring_view guid_str, bool for_64bit) {
  constexpr DWORD kTimeout = 5000;  // 5 sec.
  wil::unique_hfile transaction_handle(::CreateTransaction(
      nullptr, 0, TRANSACTION_DO_NOT_PROMOTE, 0, 0, kTimeout, nullptr));

  const REGSAM wow64_flag = for_64bit ? KEY_WOW64_64KEY : KEY_WOW64_32KEY;
  const RegistoryOpenOptions options{
      .regsam = KEY_READ | KEY_WRITE | KEY_SET_VALUE | KEY_CREATE_SUB_KEY |
                KEY_ENUMERATE_SUB_KEYS | wow64_flag,
      .options = REG_OPTION_NON_VOLATILE,
      .transaction_handle = transaction_handle.get(),
  };
  ScopedRegistry clsid_key;
  if (!clsid_key.OpenIfExist(HKEY_CLASSES_ROOT, L"CLSID", options)) {
    // CLSID key does not exist.
    return false;
  }

  return clsid_key.EnsureSubkeyAbsent(guid_str.c_str());
}

std::wstring GetMozcComponentPath(const absl::string_view filename) {
  return mozc::win32::Utf8ToWide(
      absl::StrCat(mozc::SystemUtil::GetServerDirectory(), "\\", filename));
}

}  // namespace

HRESULT TsfRegistrar::Register64bitCOMServer() {
  // TODO: Use ARM64X when being installed into ARM64 env.
  // See https://github.com/google/mozc/issues/1130
  const std::wstring &tip64_path = GetMozcComponentPath(mozc::kMozcTIP64);
  if (!EnsureComRegistryExist(ComRegistryEntry{
      .guid_str = TsfProfile::GetTextServiceGuidStr(),
      .dll_path = tip64_path,
      .description = Utf8ToWide(mozc::kProductNameInEnglish),
      .threading_model = L"Apartment",
      .for_64bit = true})) {
    return E_FAIL;
  }

  return S_OK;
}

void TsfRegistrar::Unregister64bitCOMServer() {
  EnsureComRegistryNotExist(TsfProfile::GetTextServiceGuidStr(), true);
}

// Register this COM server to the profile store for input processors.
// After completing this operation, Windows can treat this module as a
// text-input service.
// To see the list of registers input processors:
//  1. Open the "Control Panel";
//  2. Select "Date, Time, Language and Regional Options";
//  3. Select "Language and Regional Options";
//  4. Click the "Languages" tab;
//  5. Click "Details" in the "Text services and input languages" frame, and;
//  6. All installed prossors are enumerated in the "Installed services"
//     frame.
HRESULT TsfRegistrar::RegisterProfiles() {
  const std::wstring &icon_path = GetMozcComponentPath(mozc::kMozcTIP32);

  // Retrieve the profile store for input processors.
  // If you might want to create the manager object w/o calling the pair of
  // CoInitialize/CoUninitialize, there is a helper function to retrieve the
  // object.
  // http://msdn.microsoft.com/en-us/library/ms629059.aspx
  auto profiles = ComCreateInstance<ITfInputProcessorProfiles>(
      CLSID_TF_InputProcessorProfiles);
  if (!profiles) {
    return E_FAIL;
  }

  // Register this COM server as an input processor, and add this module as an
  // input processor for the language |kTextServiceLanguage|.
  HRESULT result = profiles->Register(TsfProfile::GetTextServiceGuid());
  if (SUCCEEDED(result)) {
    // We use English name here as culture-invariant description.
    // Localized name is specified later by SetLanguageProfileDisplayName.
    std::wstring description = Utf8ToWide(mozc::kProductNameInEnglish);

    result = profiles->AddLanguageProfile(
        TsfProfile::GetTextServiceGuid(), TsfProfile::GetLangId(),
        TsfProfile::GetProfileGuid(), description.c_str(), description.size(),
        icon_path.data(), icon_path.length(), TsfProfile::GetIconIndex());

    auto profiles_ex = ComQuery<ITfInputProcessorProfilesEx>(profiles);
    if (profiles_ex) {
      // Unfortunately, the document of SetLanguageProfileDisplayName is very
      // poor but we can guess that the mechanism of MUI is similar to that of
      // IMM32. IMM32 uses registry value "Layout Text" and
      // "Layout Display Name", where the content of "Layout Display Name" is
      // used by SHLoadIndirectString to display appropriate string based on
      // the current UI language.
      // This mechanism is called "Registry String Redirection".
      //   http://msdn.microsoft.com/en-us/library/dd374120.aspx
      // You can find similar string based on "Registry String Redirection"
      // used by the TSF:
      //   HKLM\SOFTWARE\Microsoft\CTF\TIP\<TextService CLSID>\LanguageProfile
      //       \<LangID>\<Profile GUID>\Display Description
      // Therefore, it is considered that arguments "pchFile" and "pchFile" of
      // the SetLanguageProfileDisplayName is resource file name and string
      // resource id, respectively.

      // You should use a new resource ID when you need to update the MUI text
      // because SetLanguageProfileDisplayName does not support version
      // modifiers.  See b/2994558 and the following article for details.
      // http://msdn.microsoft.com/en-us/library/bb759919.aspx
      HRESULT set_display_name_result =
          profiles_ex->SetLanguageProfileDisplayName(
              TsfProfile::GetTextServiceGuid(), TsfProfile::GetLangId(),
              TsfProfile::GetProfileGuid(), icon_path.data(),
              icon_path.length(), TsfProfile::GetDescriptionTextIndex());
      if (FAILED(set_display_name_result)) {
        LOG(ERROR) << "SetLanguageProfileDisplayName failed."
                   << " hr = " << set_display_name_result;
      }
    }
  }

  return result;
}

// Unregister this COM server from the text-service framework.
void TsfRegistrar::UnregisterProfiles() {
  // If you might want to create the manager object w/o calling the pair of
  // CoInitialize/CoUninitialize, there is a helper function to retrieve the
  // object.
  // http://msdn.microsoft.com/en-us/library/ms629059.aspx
  auto profiles = ComCreateInstance<ITfInputProcessorProfiles>(
      CLSID_TF_InputProcessorProfiles);
  if (profiles) {
    (void)profiles->Unregister(TsfProfile::GetTextServiceGuid());
  }
}

// Retrieves the category manager for text input processors, and
// registers this module as a keyboard and a display attribute provider.
HRESULT TsfRegistrar::RegisterCategories() {
  // If you might want to create the manager object w/o calling the pair of
  // CoInitialize/CoUninitialize, there is a helper function to retrieve the
  // object.
  // http://msdn.microsoft.com/en-us/library/aa383439.aspx
  auto category = ComCreateInstance<ITfCategoryMgr>(CLSID_TF_CategoryMgr);
  if (!category) {
    return E_FAIL;
  }
  HRESULT result = S_OK;
  if (category) {
    for (int i = 0; i < std::size(kCategories); ++i) {
      result = category->RegisterCategory(TsfProfile::GetTextServiceGuid(),
                                          kCategories[i],
                                          TsfProfile::GetTextServiceGuid());
    }
  }

  return result;
}

// Retrieves the category manager for text input processors, and
// unregisters this keyboard module.
void TsfRegistrar::UnregisterCategories() {
  // If you might want to create the manager object w/o calling the pair of
  // CoInitialize/CoUninitialize, there is a helper function to retrieve the
  // object.
  // http://msdn.microsoft.com/en-us/library/aa383439.aspx
  auto category_mgr = ComCreateInstance<ITfCategoryMgr>(CLSID_TF_CategoryMgr);
  if (category_mgr) {
    for (const auto &category : kCategories) {
      category_mgr->UnregisterCategory(TsfProfile::GetTextServiceGuid(),
                                       category,
                                       TsfProfile::GetTextServiceGuid());
    }
  }
}

}  // namespace win32
}  // namespace mozc
