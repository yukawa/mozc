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

#ifndef MOZC_PREDICTION_PREDICTOR_INTERFACE_H_
#define MOZC_PREDICTION_PREDICTOR_INTERFACE_H_

#include <cstdint>
#include <vector>

#include "absl/strings/string_view.h"
#include "absl/types/span.h"
#include "prediction/result.h"
#include "request/conversion_request.h"

namespace mozc::prediction {

class PredictorInterface {
 public:
  virtual ~PredictorInterface() = default;

  // Returns suggestions.
  // You may need to change the behavior according to the
  // Segments::request_type flag
  // SUGGESTION: automatic suggestions
  // PREDICTION: invoked only when user pushes "tab" key.
  // less aggressive than SUGGESTION mode.
  virtual std::vector<Result> Predict(
      const ConversionRequest &request) const = 0;

  // Finish the conversion. Stores the history for penalization.
  // results[0] stores the committed result.
  // We can revert the Finish operation with the revert_id and Revert method.
  virtual void Finish(const ConversionRequest &request,
                      absl::Span<const Result> results, uint32_t revert_id) {}

  // Reverts the last Finish operation.
  virtual void Revert(uint32_t revert_id) {}

  // Clears all history data of UserHistoryPredictor.
  virtual bool ClearAllHistory() { return true; }

  // Clears unused history data of UserHistoryPredictor.
  virtual bool ClearUnusedHistory() { return true; }

  // Clears a specific history data of UserHistoryPredictor.
  virtual bool ClearHistoryEntry(const absl::string_view key,
                                 const absl::string_view value) {
    return true;
  }

  // Syncs user history to local disk.
  virtual bool Sync() { return true; }

  // Reloads user history data from local disk.
  virtual bool Reload() { return true; }

  // Waits for syncer thread to complete.
  virtual bool Wait() { return true; }

  virtual absl::string_view GetPredictorName() const = 0;
};

}  // namespace mozc::prediction

#endif  // MOZC_PREDICTION_PREDICTOR_INTERFACE_H_
