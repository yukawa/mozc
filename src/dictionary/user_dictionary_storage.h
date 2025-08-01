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

// UserDicStorageInterface provides interface for accessing data
// storage of the user dictionary. Subclasses determine how to save
// dictionary data on a disk.

// The following are not responsibility of UserDicStorageInterface
// and supposed to be performed by its client.
//
// (1) Validation of input values.
//   Subclasses that implement the interface of
//   UserDicStorageInterface are supposed to perform only minimal
//   validation of input value, for example a subclass that saves
//   dictionary data in a tab-separated text file usually doesn't
//   accept input with a tab or new line character and should check
//   input for them. However, UserDicStorageInterface and its
//   subclasses don't care about any more complicated
//   application-level validity of data like an acceptable POS set,
//   character encoding and so on. The class takes input value as it
//   is.
//
// (2) Duplicate entry elimination.
//   UserDicStorageInterface treats an entry in it with a unique
//   integer key. This means it doesn't take into account any actual
//   attribute of the entry when distinguishing it from another. If
//   any kind of duplicate elimination is necessary, it should be done
//   before the value is passed to the class.
//
// (3) Importing a dictionary file of Mozc or third party IMEs.
//   UserDicStorageInterface provides CreateDictionary() and
//   AddEntry(). Clients of the class can import an external
//   dictionary file using the two member functions.

#ifndef MOZC_DICTIONARY_USER_DICTIONARY_STORAGE_H_
#define MOZC_DICTIONARY_USER_DICTIONARY_STORAGE_H_

#include <cstddef>
#include <cstdint>
#include <memory>
#include <string>

#include "absl/status/status.h"
#include "absl/status/statusor.h"
#include "absl/strings/string_view.h"
#include "protocol/user_dictionary_storage.pb.h"

namespace mozc {

class ProcessMutex;

class UserDictionaryStorage {
 public:
  using UserDictionary = user_dictionary::UserDictionary;
  using UserDictionaryEntry = user_dictionary::UserDictionary::Entry;

  // Extended error code stored in absl::Status. We use the absl's canonical
  // error code (absl::StatusCode) for general resource management. Extended
  // Error code is mainly used for the dictionary management. When
  // absl::IsUnknown(status) is true, we can access the extended error code
  // via status.raw_code(). Otherwise, canonical error code is used.
  enum ExtendedErrorCode : int {
    OK = 0,  // default (absl::StatusCode::kOk)
    // Reasonably big offset not to overwerap with canonical error code.
    INVALID_DICTIONARY_ID = 100,
    INVALID_CHARACTERS_IN_DICTIONARY_NAME,
    EMPTY_DICTIONARY_NAME,
    DUPLICATED_DICTIONARY_NAME,
    TOO_LONG_DICTIONARY_NAME,
    TOO_MANY_DICTIONARIES,
    TOO_MANY_ENTRIES,
    ERROR_TYPE_SIZE
  };

  explicit UserDictionaryStorage(std::string filename);
  virtual ~UserDictionaryStorage();

  // return the filename of user dictionary
  absl::string_view filename() const;

  // Return true if data tied with this object already
  // exists. Otherwise, it means that the space for the data is used
  // for the first time.
  absl::Status Exists() const;

  // Loads a user dictionary from the file.
  // NOTE: If the file is not existent, nothing is updated.
  //       Therefore if the file is deleted after first load(),
  //       second load() does nothing so the content loaded by first load()
  //       is kept as is.
  absl::Status Load();

  // Serialize user dictionary to local file.
  // Need to call Lock() the dictionary before calling Save().
  absl::Status Save() const;

  // Lock the dictionary so that other processes/threads cannot
  // execute mutable operations on this dictionary.
  bool Lock();

  // release the lock
  bool UnLock();

  // Export a dictionary to a file in TSV format.
  absl::Status ExportDictionary(uint64_t dic_id,
                                absl::string_view filename) const;

  // Create a new dictionary with a specified name. Returns the id of
  // the new instance. The returned status may return ExtendedErrorCode
  // when the StatusCode is Unknown.
  absl::StatusOr<uint64_t> CreateDictionary(absl::string_view dic_name);

  // Delete a dictionary.
  absl::Status DeleteDictionary(uint64_t dic_id);

  // Rename a dictionary.
  absl::Status RenameDictionary(uint64_t dic_id, absl::string_view dic_name);

  // return the index of "dic_id"
  // return -1 if no dictionary is found.
  int GetUserDictionaryIndex(uint64_t dic_id) const;

  // return mutable UserDictionary corresponding to dic_id
  UserDictionary *GetUserDictionary(uint64_t dic_id);

  // returns the dictionary id associated with the "dic_name".
  absl::StatusOr<uint64_t> GetUserDictionaryId(
      absl::string_view dic_name) const;

  // maximum number of dictionaries this storage can hold
  static size_t max_dictionary_size();

  // maximum number of entries one dictionary can hold
  static size_t max_entry_size();

  user_dictionary::UserDictionaryStorage &GetProto() { return proto_; }

  const user_dictionary::UserDictionaryStorage &GetProto() const {
    return proto_;
  }

  size_t dictionaries_size() const { return proto_.dictionaries_size(); }

  const user_dictionary::UserDictionary &dictionaries(size_t i) const {
    return proto_.dictionaries(i);
  }

 private:
  // Return true if this object can accept the given dictionary name.
  // This changes the internal state. The returned status may return
  // ExtendedErrorCode when the StatusCode is Unknown.
  absl::Status IsValidDictionaryName(absl::string_view name) const;

  // Load the data from filename actually.
  absl::Status LoadInternal();

  user_dictionary::UserDictionaryStorage proto_;
  const std::string filename_;
  std::unique_ptr<ProcessMutex> process_mutex_;
};

}  // namespace mozc

#endif  // MOZC_DICTIONARY_USER_DICTIONARY_STORAGE_H_
