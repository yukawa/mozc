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

#ifndef MOZC_PREDICTION_PREDICTOR_H_
#define MOZC_PREDICTION_PREDICTOR_H_

#include <cstdint>
#include <memory>
#include <vector>

#include "absl/strings/string_view.h"
#include "absl/types/span.h"
#include "converter/converter_interface.h"
#include "converter/immutable_converter_interface.h"
#include "engine/modules.h"
#include "prediction/predictor_interface.h"
#include "prediction/result.h"
#include "request/conversion_request.h"

namespace mozc::prediction {

class Predictor : public PredictorInterface {
 public:
  Predictor() = default;
  Predictor(const engine::Modules &modules, const ConverterInterface &converter,
            const ImmutableConverterInterface &immutable_converters);
  Predictor(std::unique_ptr<PredictorInterface> dictionary_predictor,
            std::unique_ptr<PredictorInterface> user_history_predictor);

  std::vector<Result> Predict(const ConversionRequest &request) const;

  absl::string_view GetPredictorName() const override { return "Predictor"; }

  // Hook(s) for all mutable operations.
  void Finish(const ConversionRequest &request,
              absl::Span<const Result> results, uint32_t revert_id) override;

  // Reverts the last Finish operation.
  void Revert(uint32_t revert_id) override;

  // Clears all history data of UserHistoryPredictor.
  bool ClearAllHistory() override;

  // Clears unused history data of UserHistoryPredictor.
  bool ClearUnusedHistory() override;

  // Clears a specific user history data of UserHistoryPredictor.
  bool ClearHistoryEntry(absl::string_view key,
                         absl::string_view value) override;

  // Syncs user history.
  bool Sync() override;

  // Reloads user history.
  bool Reload() override;

  // Waits for syncer to complete.
  bool Wait() override;

 private:
  std::vector<Result> PredictForDesktop(const ConversionRequest &request) const;

  std::vector<Result> PredictForMixedConversion(
      const ConversionRequest &request) const;

  std::unique_ptr<PredictorInterface> dictionary_predictor_;
  std::unique_ptr<PredictorInterface> user_history_predictor_;
};

}  // namespace mozc::prediction

#endif  // MOZC_PREDICTION_PREDICTOR_H_
