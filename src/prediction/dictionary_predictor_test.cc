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

#include "prediction/dictionary_predictor.h"

#include <algorithm>
#include <cstddef>
#include <cstdint>
#include <cstring>
#include <memory>
#include <string>
#include <utility>
#include <vector>

#include "absl/algorithm/container.h"
#include "absl/log/check.h"
#include "absl/memory/memory.h"
#include "absl/random/random.h"
#include "absl/strings/match.h"
#include "absl/strings/str_cat.h"
#include "absl/strings/string_view.h"
#include "absl/types/span.h"
#include "base/strings/assign.h"
#include "base/util.h"
#include "composer/composer.h"
#include "composer/table.h"
#include "config/config_handler.h"
#include "converter/candidate.h"
#include "converter/connector.h"
#include "data_manager/testing/mock_data_manager.h"
#include "dictionary/dictionary_token.h"
#include "dictionary/pos_matcher.h"
#include "engine/modules.h"
#include "engine/supplemental_model_interface.h"
#include "engine/supplemental_model_mock.h"
#include "prediction/dictionary_prediction_aggregator.h"
#include "prediction/realtime_decoder.h"
#include "prediction/result.h"
#include "protocol/commands.pb.h"
#include "protocol/config.pb.h"
#include "request/conversion_request.h"
#include "request/request_test_util.h"
#include "testing/gmock.h"
#include "testing/gunit.h"
#include "testing/mozctest.h"
#include "testing/test_peer.h"

namespace mozc::prediction {

using ::mozc::dictionary::PosMatcher;
using ::mozc::dictionary::Token;
using ::testing::_;
using ::testing::Field;
using ::testing::Invoke;
using ::testing::Return;
using ::testing::StrictMock;

class DictionaryPredictorTestPeer
    : public testing::TestPeer<DictionaryPredictor> {
 public:
  explicit DictionaryPredictorTestPeer(DictionaryPredictor &predictor)
      : testing::TestPeer<DictionaryPredictor>(predictor) {}

  PEER_STATIC_METHOD(IsAggressiveSuggestion);
  PEER_STATIC_METHOD(RemoveMissSpelledCandidates);
  PEER_STATIC_METHOD(AddRescoringDebugDescription);
  PEER_METHOD(GetLMCost);
  PEER_METHOD(RerankAndFilterResults);
  PEER_METHOD(AggregateTypingCorrectedResultsForMixedConversion);
  PEER_METHOD(SetPredictionCostForMixedConversion);
  PEER_METHOD(MaybeGetPreviousTopResult);
};

class MockRealtimeDecoder : public RealtimeDecoder {
 public:
  ~MockRealtimeDecoder() override = default;

  MOCK_METHOD(std::vector<Result>, Decode, (const ConversionRequest &request),
              (const, override));
};

class MockAggregator : public DictionaryPredictionAggregatorInterface {
 public:
  MOCK_METHOD(std::vector<prediction::Result>, AggregateResultsForDesktop,
              (const ConversionRequest &request), (const, override));
  MOCK_METHOD(std::vector<prediction::Result>,
              AggregateResultsForMixedConversion,
              (const ConversionRequest &request), (const, override));
  MOCK_METHOD(std::vector<prediction::Result>,
              AggregateTypingCorrectedResultsForMixedConversion,
              (const ConversionRequest &request), (const, override));
};

// Helper class to hold predictor objects.
class MockDataAndPredictor {
 public:
  MockDataAndPredictor() : MockDataAndPredictor(nullptr) {}

  explicit MockDataAndPredictor(
      std::unique_ptr<engine::SupplementalModelInterface> supplemental_model) {
    auto mock_aggregator = std::make_unique<MockAggregator>();
    auto mock_decoder = std::make_unique<MockRealtimeDecoder>();
    modules_ = engine::ModulesPresetBuilder()
                   .PresetSupplementalModel(std::move(supplemental_model))
                   .Build(std::make_unique<testing::MockDataManager>())
                   .value();
    // TODO(taku): avoid sharing the pointer owned by std::unique_ptr.
    mock_aggregator_ = mock_aggregator.get();
    mock_decoder_ = mock_decoder.get();
    predictor_ = absl::WrapUnique(new DictionaryPredictor(
        *modules_, std::move(mock_aggregator), std::move(mock_decoder)));
  }

  MockAggregator *mutable_aggregator() { return mock_aggregator_; }
  MockRealtimeDecoder *mutable_realtime_decoder() { return mock_decoder_; }

  const Connector &connector() { return modules_->GetConnector(); }
  const PosMatcher &pos_matcher() { return modules_->GetPosMatcher(); }

  const DictionaryPredictor &predictor() { return *predictor_; }
  DictionaryPredictor *mutable_predictor() { return predictor_.get(); }

  DictionaryPredictorTestPeer predictor_peer() {
    return DictionaryPredictorTestPeer(*predictor_);
  }

 private:
  MockAggregator *mock_aggregator_ = nullptr;
  MockRealtimeDecoder *mock_decoder_ = nullptr;
  std::unique_ptr<engine::Modules> modules_;
  std::unique_ptr<DictionaryPredictor> predictor_;
};

namespace {

Result CreateResult4(absl::string_view key, absl::string_view value,
                     PredictionTypes types,
                     Token::AttributesBitfield token_attrs) {
  Result result;
  strings::Assign(result.key, key);
  strings::Assign(result.value, value);
  result.SetTypesAndTokenAttributes(types, token_attrs);
  return result;
}

Result CreateResult5(absl::string_view key, absl::string_view value, int wcost,
                     PredictionTypes types,
                     Token::AttributesBitfield token_attrs) {
  Result result;
  strings::Assign(result.key, key);
  strings::Assign(result.value, value);
  result.wcost = wcost;
  result.SetTypesAndTokenAttributes(types, token_attrs);
  return result;
}

Result CreateResult6(absl::string_view key, absl::string_view value, int wcost,
                     int cost, PredictionTypes types,
                     Token::AttributesBitfield token_attrs) {
  Result result;
  strings::Assign(result.key, key);
  strings::Assign(result.value, value);
  result.wcost = wcost;
  result.cost = cost;
  result.SetTypesAndTokenAttributes(types, token_attrs);
  return result;
}

Result CreateResult7(absl::string_view key, absl::string_view value, int wcost,
                     int cost, PredictionTypes types,
                     Token::AttributesBitfield token_attrs,
                     float typing_correction_score) {
  Result result = CreateResult6(key, value, wcost, cost, types, token_attrs);
  result.typing_correction_score = typing_correction_score;
  return result;
}

void PushBackInnerSegmentBoundary(size_t key_len, size_t value_len,
                                  size_t content_key_len,
                                  size_t content_value_len, Result *result) {
  uint32_t encoded;
  if (!converter::Candidate::EncodeLengths(key_len, value_len, content_key_len,
                                           content_value_len, &encoded)) {
    return;
  }
  result->inner_segment_boundary.push_back(encoded);
}

bool FindCandidateByKeyValue(absl::Span<const Result> results,
                             absl::string_view key, absl::string_view value) {
  return absl::c_find_if(results, [&](const auto &result) {
           return (result.key == key && result.value == value);
         }) != results.end();
}

bool FindCandidateByValue(absl::Span<const Result> results,
                          absl::string_view value) {
  return absl::c_find_if(results, [&](const auto &result) {
           return (result.value == value);
         }) != results.end();
}

class DictionaryPredictorTest : public testing::TestWithTempUserProfile {
 protected:
  void SetUp() override {
    request_ = std::make_unique<commands::Request>();
    config_ = std::make_unique<config::Config>();
    config::ConfigHandler::GetDefaultConfig(config_.get());
    composer_ = std::make_unique<composer::Composer>(
        composer::Table::GetSharedDefaultTable(), *request_, *config_);
  }

  void PrependHistory(absl::string_view key, absl::string_view value) {
    history_result_.value = absl::StrCat(value, history_result_.value);
    history_result_.key = absl::StrCat(key, history_result_.key);
  }

  void InitHistory(absl::string_view key, absl::string_view value) {
    history_result_.key.clear();
    history_result_.value.clear();
    PrependHistory(key, value);
  }

  ConversionRequest CreateConversionRequestWithOptions(
      ConversionRequest::Options &&options, absl::string_view key = "") const {
    return ConversionRequestBuilder()
        .SetComposer(*composer_)
        .SetRequestView(*request_)
        .SetContextView(context_)
        .SetConfigView(*config_)
        .SetOptions(std::move(options))
        .SetHistoryResultView(history_result_)
        .SetKey(key)
        .Build();
  }

  ConversionRequest CreateConversionRequest(
      ConversionRequest::RequestType request_type,
      absl::string_view key = "") const {
    ConversionRequest::Options options;
    options.request_type = request_type;
    return CreateConversionRequestWithOptions(std::move(options), key);
  }

  std::unique_ptr<composer::Composer> composer_;
  std::unique_ptr<config::Config> config_;
  std::unique_ptr<commands::Request> request_;
  commands::Context context_;
  Result history_result_;
};

TEST_F(DictionaryPredictorTest, IsAggressiveSuggestion) {
  // "ただしい",
  // "ただしいけめんにかぎる",
  EXPECT_TRUE(DictionaryPredictorTestPeer::IsAggressiveSuggestion(
      4,     // query_len
      11,    // key_len
      6000,  // cost
      true,  // is_suggestion
      20));  // total_candidates_size

  // cost <= 4000
  EXPECT_FALSE(DictionaryPredictorTestPeer::IsAggressiveSuggestion(4, 11, 4000,
                                                                   true, 20));

  // not suggestion
  EXPECT_FALSE(DictionaryPredictorTestPeer::IsAggressiveSuggestion(4, 11, 4000,
                                                                   false, 20));

  // total_candidates_size is small
  EXPECT_FALSE(DictionaryPredictorTestPeer::IsAggressiveSuggestion(4, 11, 4000,
                                                                   true, 5));

  // query_length = 5
  EXPECT_FALSE(DictionaryPredictorTestPeer::IsAggressiveSuggestion(5, 11, 6000,
                                                                   true, 20));

  // "それでも",
  // "それでもぼくはやっていない",
  EXPECT_TRUE(DictionaryPredictorTestPeer::IsAggressiveSuggestion(4, 13, 6000,
                                                                  true, 20));

  // cost <= 4000
  EXPECT_FALSE(DictionaryPredictorTestPeer::IsAggressiveSuggestion(4, 13, 4000,
                                                                   true, 20));
}

TEST_F(DictionaryPredictorTest, RemoveMissSpelledCandidates) {
  const ConversionRequest req_len1 =
      ConversionRequestBuilder().SetKey("1").Build();
  const ConversionRequest req_len3 =
      ConversionRequestBuilder().SetKey("111").Build();

  {
    std::vector<Result> results = {
        CreateResult4("ばっく", "バッグ", prediction::UNIGRAM,
                      Token::SPELLING_CORRECTION),
        CreateResult4("ばっぐ", "バッグ", prediction::UNIGRAM, Token::NONE),
        CreateResult4("ばっく", "バッく", prediction::UNIGRAM, Token::NONE),
    };
    DictionaryPredictorTestPeer::RemoveMissSpelledCandidates(
        req_len1, absl::MakeSpan(results));

    ASSERT_EQ(3, results.size());
    EXPECT_TRUE(results[0].removed);
    EXPECT_FALSE(results[1].removed);
    EXPECT_TRUE(results[2].removed);
    EXPECT_EQ(results[0].types, prediction::UNIGRAM);
    EXPECT_EQ(results[1].types, prediction::UNIGRAM);
    EXPECT_EQ(results[2].types, prediction::UNIGRAM);
  }
  {
    std::vector<Result> results = {
        CreateResult4("ばっく", "バッグ", prediction::UNIGRAM,
                      Token::SPELLING_CORRECTION),
        CreateResult4("てすと", "テスト", prediction::UNIGRAM, Token::NONE),
    };
    DictionaryPredictorTestPeer::RemoveMissSpelledCandidates(
        req_len1, absl::MakeSpan(results));

    CHECK_EQ(2, results.size());
    EXPECT_FALSE(results[0].removed);
    EXPECT_FALSE(results[1].removed);
    EXPECT_EQ(results[0].types, prediction::UNIGRAM);
    EXPECT_EQ(results[1].types, prediction::UNIGRAM);
  }
  {
    std::vector<Result> results = {
        CreateResult4("ばっく", "バッグ", prediction::UNIGRAM,
                      Token::SPELLING_CORRECTION),
        CreateResult4("ばっく", "バック", prediction::UNIGRAM, Token::NONE),
    };
    DictionaryPredictorTestPeer::RemoveMissSpelledCandidates(
        req_len1, absl::MakeSpan(results));

    CHECK_EQ(2, results.size());
    EXPECT_TRUE(results[0].removed);
    EXPECT_TRUE(results[1].removed);
  }
  {
    std::vector<Result> results = {
        CreateResult4("ばっく", "バッグ", prediction::UNIGRAM,
                      Token::SPELLING_CORRECTION),
        CreateResult4("ばっく", "バック", prediction::UNIGRAM, Token::NONE),
    };
    DictionaryPredictorTestPeer::RemoveMissSpelledCandidates(
        req_len3, absl::MakeSpan(results));

    CHECK_EQ(2, results.size());
    EXPECT_FALSE(results[0].removed);
    EXPECT_TRUE(results[1].removed);
    EXPECT_EQ(results[0].types, prediction::UNIGRAM);
    EXPECT_EQ(results[1].types, prediction::UNIGRAM);
  }
}

TEST_F(DictionaryPredictorTest, GetLMCost) {
  auto data_and_predictor = std::make_unique<MockDataAndPredictor>();
  DictionaryPredictorTestPeer predictor_peer =
      data_and_predictor->predictor_peer();
  const Connector &connector = data_and_predictor->connector();

  Result result;
  result.wcost = 64;

  for (int rid = 0; rid < 100; ++rid) {
    for (int lid = 0; lid < 100; ++lid) {
      result.lid = lid;
      const int c1 = connector.GetTransitionCost(rid, result.lid);
      const int c2 = connector.GetTransitionCost(0, result.lid);
      result.types = prediction::SUFFIX;
      EXPECT_EQ(predictor_peer.GetLMCost(result, rid), c1 + result.wcost);

      result.types = prediction::REALTIME;
      EXPECT_EQ(predictor_peer.GetLMCost(result, rid),
                std::min(c1, c2) + result.wcost);
    }
  }
}

TEST_F(DictionaryPredictorTest, SetPredictionCostForMixedConversion) {
  auto data_and_predictor = std::make_unique<MockDataAndPredictor>();
  DictionaryPredictorTestPeer predictor_peer =
      data_and_predictor->predictor_peer();

  std::vector<Result> results = {
      CreateResult4("てすと", "てすと", prediction::UNIGRAM, Token::NONE),
      CreateResult4("てすと", "テスト", prediction::UNIGRAM, Token::NONE),
      CreateResult4("てすとてすと", "テストテスト", prediction::UNIGRAM,
                    Token::NONE),
  };

  const ConversionRequest convreq =
      CreateConversionRequest(ConversionRequest::PREDICTION, "てすと");
  predictor_peer.SetPredictionCostForMixedConversion(convreq,
                                                     absl::MakeSpan(results));

  EXPECT_EQ(results.size(), 3);
  EXPECT_EQ(results[0].value, "てすと");
  EXPECT_EQ(results[1].value, "テスト");
  EXPECT_EQ(results[2].value, "テストテスト");
  EXPECT_GT(results[2].cost, results[0].cost);
  EXPECT_GT(results[2].cost, results[1].cost);
}

TEST_F(DictionaryPredictorTest, SetLMCostForUserDictionaryWord) {
  auto data_and_predictor = std::make_unique<MockDataAndPredictor>();
  DictionaryPredictorTestPeer predictor_peer =
      data_and_predictor->predictor_peer();

  constexpr absl::string_view kAikaHiragana = "あいか";
  constexpr absl::string_view kAikaKanji = "愛佳";

  {
    // Cost of words in user dictionary should be decreased.
    constexpr int kOriginalWordCost = 10000;
    std::vector<Result> results = {
        CreateResult5(kAikaHiragana, kAikaKanji, kOriginalWordCost,
                      prediction::UNIGRAM, Token::USER_DICTIONARY),
    };

    const ConversionRequest convreq =
        CreateConversionRequest(ConversionRequest::PREDICTION, kAikaHiragana);
    predictor_peer.SetPredictionCostForMixedConversion(convreq,
                                                       absl::MakeSpan(results));

    EXPECT_EQ(results.size(), 1);
    EXPECT_EQ(results[0].value, kAikaKanji);
    EXPECT_GT(kOriginalWordCost, results[0].cost);
    EXPECT_LE(1, results[0].cost);
  }

  {
    // Cost of words in user dictionary should not be decreased to below 1.
    constexpr int kOriginalWordCost = 10;
    std::vector<Result> results = {
        CreateResult5(kAikaHiragana, kAikaKanji, kOriginalWordCost,
                      prediction::UNIGRAM, Token::USER_DICTIONARY),
    };

    const ConversionRequest convreq =
        CreateConversionRequest(ConversionRequest::PREDICTION, kAikaHiragana);
    predictor_peer.SetPredictionCostForMixedConversion(convreq,
                                                       absl::MakeSpan(results));

    EXPECT_EQ(results.size(), 1);
    EXPECT_EQ(results[0].value, kAikaKanji);
    EXPECT_GT(kOriginalWordCost, results[0].cost);
    EXPECT_LE(1, results[0].cost);
  }

  {
    // Cost of general symbols should not be decreased.
    constexpr int kOriginalWordCost = 10000;
    std::vector<Result> results = {
        CreateResult5(kAikaHiragana, kAikaKanji, kOriginalWordCost,
                      prediction::UNIGRAM, Token::USER_DICTIONARY),
    };
    ASSERT_EQ(1, results.size());
    results[0].lid = data_and_predictor->pos_matcher().GetGeneralSymbolId();
    results[0].rid = results[0].lid;

    const ConversionRequest convreq =
        CreateConversionRequest(ConversionRequest::PREDICTION, kAikaHiragana);
    predictor_peer.SetPredictionCostForMixedConversion(convreq,
                                                       absl::MakeSpan(results));

    EXPECT_EQ(results.size(), 1);
    EXPECT_EQ(results[0].value, kAikaKanji);
    EXPECT_LE(kOriginalWordCost, results[0].cost);
  }

  {
    // Cost of words not in user dictionary should not be decreased.
    constexpr int kOriginalWordCost = 10000;
    std::vector<Result> results = {
        CreateResult5(kAikaHiragana, kAikaKanji, kOriginalWordCost,
                      prediction::UNIGRAM, Token::NONE),
    };

    const ConversionRequest convreq =
        CreateConversionRequest(ConversionRequest::PREDICTION, kAikaHiragana);
    predictor_peer.SetPredictionCostForMixedConversion(convreq,
                                                       absl::MakeSpan(results));

    EXPECT_EQ(results.size(), 1);
    EXPECT_EQ(results[0].value, kAikaKanji);
    EXPECT_EQ(results[0].cost, kOriginalWordCost);
  }
}

TEST_F(DictionaryPredictorTest, SuggestSpellingCorrection) {
  auto data_and_predictor = std::make_unique<MockDataAndPredictor>();
  const DictionaryPredictor &predictor = data_and_predictor->predictor();
  MockAggregator *aggregator = data_and_predictor->mutable_aggregator();
  EXPECT_CALL(*aggregator, AggregateResultsForDesktop(_))
      .WillOnce(Return(std::vector<Result>{
          CreateResult5("あぼがど", "アボカド", 500, prediction::UNIGRAM,
                        Token::SPELLING_CORRECTION),
          CreateResult5("あぼがど", "アボガド", 500, prediction::UNIGRAM,
                        Token::NONE)}));

  const ConversionRequest convreq =
      CreateConversionRequest(ConversionRequest::PREDICTION, "あぼがど");
  const std::vector<Result> results = predictor.Predict(convreq);

  EXPECT_TRUE(FindCandidateByValue(results, "アボカド"));
}

TEST_F(DictionaryPredictorTest, DoNotSuggestSpellingCorrectionBeforeMismatch) {
  auto data_and_predictor = std::make_unique<MockDataAndPredictor>();
  const DictionaryPredictor &predictor = data_and_predictor->predictor();
  MockAggregator *aggregator = data_and_predictor->mutable_aggregator();

  EXPECT_CALL(*aggregator, AggregateResultsForDesktop(_))
      .WillOnce(Return(std::vector<Result>{
          CreateResult5("あぼがど", "アボカド", 500, prediction::UNIGRAM,
                        Token::SPELLING_CORRECTION),
          CreateResult5("あぼがど", "アボガド", 500, prediction::UNIGRAM,
                        Token::NONE),
      }));

  const ConversionRequest convreq =
      CreateConversionRequest(ConversionRequest::PREDICTION, "あぼが");
  const std::vector<Result> results = predictor.Predict(convreq);

  EXPECT_FALSE(FindCandidateByValue(results, "アボカド"));
}

TEST_F(DictionaryPredictorTest, MobileZeroQuery) {
  auto data_and_predictor = std::make_unique<MockDataAndPredictor>();
  const DictionaryPredictor &predictor = data_and_predictor->predictor();
  MockAggregator *aggregator = data_and_predictor->mutable_aggregator();

  EXPECT_CALL(*aggregator, AggregateResultsForMixedConversion(_))
      .WillOnce(Return(std::vector<Result>{
          CreateResult5("", "", 500, prediction::BIGRAM, Token::NONE),
          CreateResult5("いん", "院", 600, prediction::BIGRAM, Token::NONE),
          CreateResult5("せい", "生", 600, prediction::BIGRAM, Token::NONE),
          CreateResult5("やきゅう", "野球", 1000, prediction::BIGRAM,
                        Token::NONE),
          CreateResult5("じゅけん", "受験", 1000, prediction::BIGRAM,
                        Token::NONE),
          CreateResult5("にゅうし", "入試", 1000, prediction::BIGRAM,
                        Token::NONE),
          CreateResult5("にゅうしせんたー", "入試センター", 2000,
                        prediction::BIGRAM, Token::NONE),
      }));

  InitHistory("だいがく", "大学");
  PrependHistory("とうきょう", "東京");  // not used

  request_test_util::FillMobileRequest(request_.get());
  const ConversionRequest convreq =
      CreateConversionRequest(ConversionRequest::PREDICTION, "");
  const std::vector<Result> results = predictor.Predict(convreq);

  EXPECT_TRUE(FindCandidateByKeyValue(results, "にゅうし", "入試"));
  EXPECT_TRUE(
      FindCandidateByKeyValue(results, "にゅうしせんたー", "入試センター"));
}

TEST_F(DictionaryPredictorTest, PredictivePenaltyForBigramResults) {
  auto data_and_predictor = std::make_unique<MockDataAndPredictor>();
  const DictionaryPredictor &predictor = data_and_predictor->predictor();
  MockAggregator *aggregator = data_and_predictor->mutable_aggregator();

  EXPECT_CALL(*aggregator, AggregateResultsForMixedConversion(_))
      .WillOnce(Return(std::vector<Result>{
          CreateResult5("にゅうし", "入試", 3000, prediction::BIGRAM,
                        Token::NONE),
          CreateResult5("にゅうしせんたー", "入試センター", 4000,
                        prediction::BIGRAM, Token::NONE),
          CreateResult5("にゅうしせんたーしけんたいさく",
                        "入試センター試験対策", 5000, prediction::BIGRAM,
                        Token::NONE),
          CreateResult5("にゅうし", "乳歯", 2000, prediction::UNIGRAM,
                        Token::NONE)}));

  InitHistory("だいがく", "大学");
  PrependHistory("とうきょう", "東京");  // not used

  request_test_util::FillMobileRequest(request_.get());
  const ConversionRequest convreq =
      CreateConversionRequest(ConversionRequest::PREDICTION, "にゅうし");
  const std::vector<Result> results = predictor.Predict(convreq);

  auto get_rank_by_value = [&](absl::string_view value) {
    for (int i = 0; i < results.size(); ++i) {
      if (results[i].value == value) {
        return i;
      }
    }
    return -1;
  };
  EXPECT_LT(get_rank_by_value("乳歯"),
            get_rank_by_value("入試センター試験対策"));
}

TEST_F(DictionaryPredictorTest, PropagateAttributes) {
  auto data_and_predictor = std::make_unique<MockDataAndPredictor>();
  const DictionaryPredictor &predictor = data_and_predictor->predictor();
  MockAggregator *aggregator = data_and_predictor->mutable_aggregator();
  MockRealtimeDecoder *realtime_decoder =
      data_and_predictor->mutable_realtime_decoder();

  // Exact key will not be filtered in mobile request
  request_test_util::FillMobileRequest(request_.get());

  // Small prefix penalty
  {
    Result result;
    result.cost = 10;
    EXPECT_CALL(*realtime_decoder, Decode(_))
        .WillRepeatedly(Return(std::vector<Result>({result})));
  }

  auto get_top_result = [&aggregator, &predictor, this](
                            const Result &aggregator_result,
                            PredictionTypes prediction_types, Result *result) {
    EXPECT_CALL(*aggregator, AggregateResultsForMixedConversion(_))
        .WillOnce(Return(std::vector<Result>({aggregator_result})));
    const ConversionRequest convreq =
        CreateConversionRequest(ConversionRequest::PREDICTION, "てすと");
    const std::vector<Result> results = predictor.Predict(convreq);
    if (results.empty()) {
      return false;
    }
    *result = results[0];
    return true;
  };

  Result c;
  {
    // PREFIX: consumed_key_size
    Result result =
        CreateResult5("てす", "てす", 50, prediction::PREFIX, Token::NONE);
    result.consumed_key_size = Util::CharsLen("てす");

    EXPECT_TRUE(get_top_result(result, prediction::PREFIX, &c));
    EXPECT_EQ(c.value, "てす");
    EXPECT_EQ(c.candidate_attributes,
              converter::Candidate::PARTIALLY_KEY_CONSUMED |
                  converter::Candidate::AUTO_PARTIAL_SUGGESTION);
    EXPECT_EQ(c.consumed_key_size, 2);
  }
  {
    // REALTIME_TOP
    Result result = CreateResult5(
        "てすと", "リアルタイムトップ", 100,
        prediction::REALTIME_TOP | prediction::REALTIME, Token::NONE);

    EXPECT_TRUE(get_top_result(result, prediction::REALTIME_TOP, &c));
    EXPECT_EQ(c.value, "リアルタイムトップ");
    EXPECT_EQ(c.candidate_attributes,
              converter::Candidate::REALTIME_CONVERSION |
                  converter::Candidate::NO_VARIANTS_EXPANSION);
  }
  {
    // REALTIME: inner_segment_boundary
    Result result = CreateResult5("てすと", "リアルタイム", 100,
                                  prediction::REALTIME, Token::NONE);
    uint32_t encoded;
    converter::Candidate::EncodeLengths(strlen("てす"), strlen("リアル"),
                                        strlen("て"), strlen("リア"), &encoded);
    result.inner_segment_boundary.push_back(encoded);
    converter::Candidate::EncodeLengths(strlen("と"), strlen("タイム"),
                                        strlen("と"), strlen("タイム"),
                                        &encoded);
    result.inner_segment_boundary.push_back(encoded);

    EXPECT_TRUE(get_top_result(result, prediction::REALTIME, &c));
    EXPECT_EQ(c.value, "リアルタイム");
    EXPECT_EQ(c.candidate_attributes,
              converter::Candidate::REALTIME_CONVERSION);
    EXPECT_EQ(c.inner_segment_boundary.size(), 2);
  }
  {
    // SPELLING_CORRECTION
    Result result =
        CreateResult5("てすと", "SPELLING_CORRECTION", 300, prediction::UNIGRAM,
                      Token::SPELLING_CORRECTION);

    EXPECT_TRUE(get_top_result(result, prediction::UNIGRAM, &c));
    EXPECT_EQ(c.value, "SPELLING_CORRECTION");
    EXPECT_EQ(c.candidate_attributes,
              converter::Candidate::SPELLING_CORRECTION);
  }
  {
    // TYPING_CORRECTION
    Result result = CreateResult5("てすと", "TYPING_CORRECTION", 300,
                                  prediction::TYPING_CORRECTION, Token::NONE);

    EXPECT_TRUE(get_top_result(result, prediction::TYPING_CORRECTION, &c));
    EXPECT_EQ(c.value, "TYPING_CORRECTION");
    EXPECT_EQ(c.candidate_attributes, converter::Candidate::TYPING_CORRECTION);
  }
  {
    // USER_DICTIONARY
    Result result = CreateResult5("てすと", "ユーザー辞書", 300,
                                  prediction::UNIGRAM, Token::USER_DICTIONARY);

    EXPECT_TRUE(get_top_result(result, prediction::UNIGRAM, &c));
    EXPECT_EQ(c.value, "ユーザー辞書");
    EXPECT_EQ(c.candidate_attributes,
              converter::Candidate::USER_DICTIONARY |
                  converter::Candidate::NO_MODIFICATION |
                  converter::Candidate::NO_VARIANTS_EXPANSION);
  }
  {
    // removed
    Result result = CreateResult5("てすと", "REMOVED", 300, prediction::BIGRAM,
                                  Token::NONE);
    result.removed = true;

    EXPECT_FALSE(get_top_result(result, prediction::UNIGRAM, &c));
  }
}

TEST_F(DictionaryPredictorTest, MergeAttributesForDebug) {
  auto data_and_predictor = std::make_unique<MockDataAndPredictor>();
  DictionaryPredictorTestPeer predictor_peer =
      data_and_predictor->predictor_peer();

  std::vector<Result> results = {
      CreateResult4("a0", "A0", prediction::REALTIME, Token::NONE),
      CreateResult4("a1", "A1", prediction::REALTIME, Token::NONE),
      CreateResult4("a2", "A2", prediction::REALTIME, Token::NONE),
      CreateResult4("a3", "A3", prediction::REALTIME, Token::NONE),
      CreateResult4("a0", "A0", prediction::SUFFIX, Token::NONE),
      CreateResult4("a1", "A1", prediction::SUFFIX, Token::NONE),
      CreateResult4("a2", "A2", prediction::SUFFIX, Token::NONE),
      CreateResult4("a3", "A3", prediction::SUFFIX, Token::NONE),
  };

  absl::BitGen urbg;
  std::shuffle(results.begin(), results.end(), urbg);

  // Enables debug mode.
  config_->set_verbose_level(1);
  const ConversionRequest convreq =
      CreateConversionRequest(ConversionRequest::SUGGESTION, "test");
  results = predictor_peer.RerankAndFilterResults(convreq, results);

  for (size_t i = 0; i < results.size(); ++i) {
    EXPECT_EQ(results[i].description, "RS");
  }
}

TEST_F(DictionaryPredictorTest, PropagateResultCosts) {
  auto data_and_predictor = std::make_unique<MockDataAndPredictor>();
  DictionaryPredictorTestPeer predictor_peer =
      data_and_predictor->predictor_peer();

  constexpr int kTestSize = 20;
  std::vector<Result> results(kTestSize);
  for (size_t i = 0; i < kTestSize; ++i) {
    Result *result = &results[i];
    result->key = std::string(1, 'a' + i);
    result->value = std::string(1, 'A' + i);
    result->wcost = i;
    result->cost = i + 1000;
    result->SetTypesAndTokenAttributes(prediction::REALTIME, Token::NONE);
  }
  absl::BitGen urbg;
  std::shuffle(results.begin(), results.end(), urbg);

  const ConversionRequest convreq = CreateConversionRequestWithOptions(
      {
          .request_type = ConversionRequest::SUGGESTION,
          .max_dictionary_prediction_candidates_size = kTestSize,
      },
      "test");

  results = predictor_peer.RerankAndFilterResults(convreq, results);

  ASSERT_EQ(kTestSize, results.size());
  for (size_t i = 0; i < results.size(); ++i) {
    EXPECT_EQ(results[i].cost, i + 1000);
  }
}

TEST_F(DictionaryPredictorTest, PredictNCandidates) {
  auto data_and_predictor = std::make_unique<MockDataAndPredictor>();
  DictionaryPredictorTestPeer predictor_peer =
      data_and_predictor->predictor_peer();

  constexpr int kTotalCandidateSize = 100;
  constexpr int kLowCostCandidateSize = 5;
  std::vector<Result> results(kTotalCandidateSize);
  for (size_t i = 0; i < kTotalCandidateSize; ++i) {
    Result *result = &results[i];
    result->key = std::string(1, 'a' + i);
    result->value = std::string(1, 'A' + i);
    result->wcost = i;
    result->SetTypesAndTokenAttributes(prediction::REALTIME, Token::NONE);
    if (i < kLowCostCandidateSize) {
      result->cost = i + 1000;
    } else {
      result->cost = i + Result::kInvalidCost;
    }
  }
  absl::BitGen urbg;
  std::shuffle(results.begin(), results.end(), urbg);

  const ConversionRequest convreq = CreateConversionRequestWithOptions(
      {
          .request_type = ConversionRequest::SUGGESTION,
          .max_dictionary_prediction_candidates_size =
              kLowCostCandidateSize + 1,
      },
      "test");

  results = predictor_peer.RerankAndFilterResults(convreq, results);

  ASSERT_EQ(kLowCostCandidateSize, results.size());
  for (size_t i = 0; i < results.size(); ++i) {
    EXPECT_EQ(results[i].cost, i + 1000);
  }
}

TEST_F(DictionaryPredictorTest, SuggestFilteredwordForExactMatchOnMobile) {
  auto data_and_predictor = std::make_unique<MockDataAndPredictor>();
  const DictionaryPredictor &predictor = data_and_predictor->predictor();
  // turn on mobile mode
  request_test_util::FillMobileRequest(request_.get());

  {
    MockAggregator *aggregator = data_and_predictor->mutable_aggregator();

    EXPECT_CALL(*aggregator, AggregateResultsForMixedConversion(_))
        .WillRepeatedly(Return(std::vector<Result>{
            CreateResult5("ふぃるたーたいしょう", "フィルター対象", 100,
                          prediction::UNIGRAM, Token::NONE),
            CreateResult5("ふぃるたーたいしょう", "フィルター大将", 200,
                          prediction::UNIGRAM, Token::NONE),
        }));
  }

  // Note: The suggestion filter entry "フィルター" for test is not
  // appropriate here, as Katakana entry will be added by real time
  // conversion. Here, we want to confirm the behavior including unigram
  // prediction.
  const ConversionRequest convreq1 = CreateConversionRequest(
      ConversionRequest::SUGGESTION, "ふぃるたーたいしょう");
  std::vector<Result> results = predictor.Predict(convreq1);
  EXPECT_TRUE(FindCandidateByValue(results, "フィルター対象"));
  EXPECT_TRUE(FindCandidateByValue(results, "フィルター大将"));

  // However, filtered word should not be the top.
  EXPECT_EQ(results[0].value, "フィルター大将");

  // Should not be there for non-exact suggestion.
  const ConversionRequest convreq2 = CreateConversionRequest(
      ConversionRequest::SUGGESTION, "ふぃるたーたいし");
  results = predictor.Predict(convreq2);
  EXPECT_FALSE(FindCandidateByValue(results, "フィルター対象"));
}

TEST_F(DictionaryPredictorTest, SuppressFilteredwordForExactMatch) {
  auto data_and_predictor = std::make_unique<MockDataAndPredictor>();
  const DictionaryPredictor &predictor = data_and_predictor->predictor();

  {
    MockAggregator *aggregator = data_and_predictor->mutable_aggregator();

    EXPECT_CALL(*aggregator, AggregateResultsForDesktop(_))
        .WillRepeatedly(Return(std::vector<Result>{
            CreateResult5("ふぃるたーたいしょう", "フィルター対象", 100,
                          prediction::UNIGRAM, Token::NONE),
            CreateResult5("ふぃるたーたいしょう", "フィルター大将", 200,
                          prediction::UNIGRAM, Token::NONE),
        }));
  }

  // Note: The suggestion filter entry "フィルター" for test is not
  // appropriate here, as Katakana entry will be added by real time
  // conversion. Here, we want to confirm the behavior including unigram
  // prediction.
  const ConversionRequest convreq = CreateConversionRequest(
      ConversionRequest::SUGGESTION, "ふぃるたーたいしょう");
  const std::vector<Result> results = predictor.Predict(convreq);
  EXPECT_FALSE(FindCandidateByValue(results, "フィルター対象"));
}

TEST_F(DictionaryPredictorTest, DoNotFilterExactUnigramOnMobile) {
  auto data_and_predictor = std::make_unique<MockDataAndPredictor>();
  const DictionaryPredictor &predictor = data_and_predictor->predictor();
  request_test_util::FillMobileRequest(request_.get());

  {
    MockAggregator *aggregator = data_and_predictor->mutable_aggregator();

    std::vector<Result> results;
    for (int i = 0; i < 30; ++i) {
      // Exact entries
      results.push_back(CreateResult5("てすと", absl::StrCat(i, "テストE"),
                                      5000 + i, prediction::UNIGRAM,
                                      Token::NONE));
      // Predictive entries
      results.push_back(CreateResult5("てすとて", absl::StrCat(i, "テストP"),
                                      100 + i, prediction::UNIGRAM,
                                      Token::NONE));
    }

    EXPECT_CALL(*aggregator, AggregateResultsForMixedConversion(_))
        .WillOnce(Return(results));
  }

  const ConversionRequest convreq = CreateConversionRequestWithOptions(
      {
          .request_type = ConversionRequest::PREDICTION,
          .max_dictionary_prediction_candidates_size = 100,
      },
      "てすと");
  const std::vector<Result> results = predictor.Predict(convreq);
  int exact_count = 0;
  for (const Result &result : results) {
    if (absl::StrContains(result.value, "テストE")) {
      exact_count++;
    }
  }
  EXPECT_EQ(exact_count, 30);
}

TEST_F(DictionaryPredictorTest, DoNotFilterUnigrmsForHandwriting) {
  auto data_and_predictor = std::make_unique<MockDataAndPredictor>();
  const DictionaryPredictor &predictor = data_and_predictor->predictor();

  // Destkop doesn't support handwriting.
  request_test_util::FillMobileRequest(request_.get());

  // Fill handwriting request and composer
  {
    request_->set_zero_query_suggestion(true);
    request_->set_mixed_conversion(true);
    request_->set_kana_modifier_insensitive_conversion(false);
    request_->set_auto_partial_suggestion(false);

    commands::SessionCommand command;
    commands::SessionCommand::CompositionEvent *composition_event =
        command.add_composition_events();
    composition_event->set_composition_string("かん字");
    composition_event->set_probability(1.0);
    composer_->SetCompositionsForHandwriting(command.composition_events());
  }

  {
    MockAggregator *aggregator = data_and_predictor->mutable_aggregator();

    std::vector<Result> results;
    for (int i = 0; i < 10; ++i) {
      // Exact entries
      results.push_back(CreateResult5("かん字", absl::StrCat(i, "漢字E"),
                                      5000 + i, prediction::UNIGRAM,
                                      Token::NONE));
    }
    for (int i = 0; i < 10; ++i) {
      // Keys can be longer than the segment key
      results.push_back(CreateResult5("かんじよみ", absl::StrCat(i, "漢字E"),
                                      5000 + i, prediction::UNIGRAM,
                                      Token::NONE));
    }

    EXPECT_CALL(*aggregator, AggregateResultsForMixedConversion(_))
        .WillOnce(Return(results));
  }

  const ConversionRequest convreq_for_prediction =
      CreateConversionRequestWithOptions(
          {
              .request_type = ConversionRequest::PREDICTION,
              .max_dictionary_prediction_candidates_size = 100,
          },
          "かん字");
  const std::vector<Result> results = predictor.Predict(convreq_for_prediction);
  int exact_count = 0;
  for (const Result &result : results) {
    if (absl::StrContains(result.value, "漢字E")) {
      exact_count++;
    }
  }
  EXPECT_EQ(exact_count, 20);
}

TEST_F(DictionaryPredictorTest, DoNotFilterZeroQueryCandidatesOnMobile) {
  auto data_and_predictor = std::make_unique<MockDataAndPredictor>();
  const DictionaryPredictor &predictor = data_and_predictor->predictor();
  request_test_util::FillMobileRequest(request_.get());

  {
    MockAggregator *aggregator = data_and_predictor->mutable_aggregator();

    // Entries for zero query
    std::vector<Result> results;
    for (int i = 0; i < 10; ++i) {
      results.push_back(CreateResult5("てすと", absl::StrCat(i, "テストS"), 100,
                                      prediction::SUFFIX, Token::NONE));
    }

    EXPECT_CALL(*aggregator, AggregateResultsForMixedConversion(_))
        .WillRepeatedly(Return(results));
  }

  InitHistory("わたし", "私");
  const ConversionRequest convreq =
      CreateConversionRequest(ConversionRequest::PREDICTION, "");
  const std::vector<Result> results = predictor.Predict(convreq);
  EXPECT_EQ(results.size(), 10);
}

TEST_F(DictionaryPredictorTest,
       DoNotFilterOneSegmentRealtimeCandidatesOnMobile) {
  auto data_and_predictor = std::make_unique<MockDataAndPredictor>();
  const DictionaryPredictor &predictor = data_and_predictor->predictor();
  // turn on mobile mode
  request_test_util::FillMobileRequest(request_.get());

  {
    MockAggregator *aggregator = data_and_predictor->mutable_aggregator();
    std::vector<Result> results;
    results.push_back(CreateResult5(
        "かった", "買った", 300,
        prediction::REALTIME_TOP | prediction::REALTIME, Token::NONE));
    PushBackInnerSegmentBoundary(9, 9, 9, 9, &results.back());
    results.push_back(CreateResult5("かった", "飼った", 1000,
                                    prediction::REALTIME, Token::NONE));
    PushBackInnerSegmentBoundary(9, 9, 9, 9, &results.back());
    results.push_back(CreateResult5("かつた", "勝田", 1001,
                                    prediction::REALTIME, Token::NONE));
    PushBackInnerSegmentBoundary(9, 6, 9, 6, &results.back());
    results.push_back(CreateResult5("かつた", "勝太", 1002,
                                    prediction::REALTIME, Token::NONE));
    PushBackInnerSegmentBoundary(9, 6, 9, 6, &results.back());
    results.push_back(CreateResult5("かつた", "鹿田", 1003,
                                    prediction::REALTIME, Token::NONE));
    PushBackInnerSegmentBoundary(9, 6, 9, 6, &results.back());
    results.push_back(CreateResult5("かつた", "かつた", 1004,
                                    prediction::REALTIME, Token::NONE));
    PushBackInnerSegmentBoundary(9, 9, 9, 9, &results.back());
    results.push_back(CreateResult5("かった", "刈った", 1005,
                                    prediction::REALTIME, Token::NONE));
    PushBackInnerSegmentBoundary(9, 9, 9, 9, &results.back());
    results.push_back(CreateResult5("かった", "勝った", 1006,
                                    prediction::REALTIME, Token::NONE));
    PushBackInnerSegmentBoundary(9, 9, 9, 9, &results.back());

    EXPECT_CALL(*aggregator, AggregateResultsForMixedConversion(_))
        .WillRepeatedly(Return(results));
  }

  const ConversionRequest convreq =
      CreateConversionRequest(ConversionRequest::PREDICTION, "かつた");
  const std::vector<Result> results = predictor.Predict(convreq);
  EXPECT_GE(results.size(), 8);
}

TEST_F(DictionaryPredictorTest, FixSRealtimeTopCandidatesCostOnMobile) {
  auto data_and_predictor = std::make_unique<MockDataAndPredictor>();
  const DictionaryPredictor &predictor = data_and_predictor->predictor();
  // turn on mobile mode
  request_test_util::FillMobileRequest(request_.get());

  {
    MockAggregator *aggregator = data_and_predictor->mutable_aggregator();
    std::vector<Result> results;
    results.push_back(CreateResult5(
        "かった", "買った", 1002,
        prediction::REALTIME_TOP | prediction::REALTIME, Token::NONE));
    PushBackInnerSegmentBoundary(9, 9, 9, 9, &results.back());
    results.push_back(CreateResult5("かった", "飼った", 1000,
                                    prediction::REALTIME, Token::NONE));
    PushBackInnerSegmentBoundary(9, 9, 9, 9, &results.back());
    results.push_back(CreateResult5("かつた", "勝田", 1001,
                                    prediction::REALTIME, Token::NONE));
    PushBackInnerSegmentBoundary(9, 6, 9, 6, &results.back());
    EXPECT_CALL(*aggregator, AggregateResultsForMixedConversion(_))
        .WillRepeatedly(Return(results));
  }

  const ConversionRequest convreq =
      CreateConversionRequest(ConversionRequest::PREDICTION, "かった");
  const std::vector<Result> results = predictor.Predict(convreq);
  EXPECT_EQ(results[0].value, "買った");
}

TEST_F(DictionaryPredictorTest, SingleKanjiCost) {
  auto data_and_predictor = std::make_unique<MockDataAndPredictor>();
  const DictionaryPredictor &predictor = data_and_predictor->predictor();
  // turn on mobile mode
  request_test_util::FillMobileRequest(request_.get());

  {
    MockAggregator *aggregator = data_and_predictor->mutable_aggregator();
    std::vector<Result> results;
    results.push_back(
        CreateResult5("さか", "坂", 400, prediction::REALTIME, Token::NONE));
    results.push_back(
        CreateResult5("さが", "佐賀", 500, prediction::REALTIME, Token::NONE));
    results.push_back(
        CreateResult5("さか", "咲か", 2000, prediction::UNIGRAM, Token::NONE));
    results.push_back(
        CreateResult5("さか", "阪", 2500, prediction::UNIGRAM, Token::NONE));
    results.push_back(
        CreateResult5("さか", "サカ", 10000, prediction::UNIGRAM, Token::NONE));
    results.push_back(
        CreateResult5("さがす", "探す", 300, prediction::UNIGRAM, Token::NONE));
    results.push_back(CreateResult5("さがし", "探し", 3000, prediction::UNIGRAM,
                                    Token::NONE));
    results.push_back(
        CreateResult5("さかい", "堺", 800, prediction::UNIGRAM, Token::NONE));
    results.push_back(
        CreateResult5("さか", "坂", 9000, prediction::UNIGRAM, Token::NONE));
    results.push_back(
        CreateResult5("さか", "逆", 0, prediction::SINGLE_KANJI, Token::NONE));
    results.push_back(
        CreateResult5("さか", "坂", 1, prediction::SINGLE_KANJI, Token::NONE));
    results.push_back(
        CreateResult5("さか", "酒", 2, prediction::SINGLE_KANJI, Token::NONE));
    results.push_back(
        CreateResult5("さか", "栄", 3, prediction::SINGLE_KANJI, Token::NONE));
    results.push_back(
        CreateResult5("さか", "盛", 4, prediction::SINGLE_KANJI, Token::NONE));
    results.push_back(
        CreateResult5("さ", "差", 1000, prediction::SINGLE_KANJI, Token::NONE));
    results.push_back(
        CreateResult5("さ", "佐", 1001, prediction::SINGLE_KANJI, Token::NONE));
    for (int i = 0; i < results.size(); ++i) {
      if (results[i].types == prediction::SINGLE_KANJI) {
        results[i].lid = data_and_predictor->pos_matcher().GetGeneralSymbolId();
        results[i].rid = data_and_predictor->pos_matcher().GetGeneralSymbolId();
      } else {
        results[i].lid = data_and_predictor->pos_matcher().GetGeneralNounId();
        results[i].rid = data_and_predictor->pos_matcher().GetGeneralNounId();
      }
    }

    EXPECT_CALL(*aggregator, AggregateResultsForMixedConversion(_))
        .WillRepeatedly(Return(results));
  }

  std::vector<Result> results;
  auto get_rank_by_value = [&](absl::string_view value) {
    for (int i = 0; i < results.size(); ++i) {
      if (results[i].value == value) {
        return i;
      }
    }
    return -1;
  };

  {
    const ConversionRequest convreq =
        CreateConversionRequest(ConversionRequest::PREDICTION, "さか");
    results = predictor.Predict(convreq);
    EXPECT_NE(get_rank_by_value("佐"), -1);
    EXPECT_LT(get_rank_by_value("佐"), results.size() - 1);
    EXPECT_LT(get_rank_by_value("坂"), get_rank_by_value("逆"));
    EXPECT_LT(get_rank_by_value("咲か"), get_rank_by_value("逆"));
    EXPECT_LT(get_rank_by_value("阪"), get_rank_by_value("逆"));
    EXPECT_LT(get_rank_by_value("逆"), get_rank_by_value("差"));
  }
}

TEST_F(DictionaryPredictorTest, SingleKanjiFallbackOffsetCost) {
  auto data_and_predictor = std::make_unique<MockDataAndPredictor>();
  const DictionaryPredictor &predictor = data_and_predictor->predictor();
  // turn on mobile mode
  request_test_util::FillMobileRequest(request_.get());

  {
    MockAggregator *aggregator = data_and_predictor->mutable_aggregator();
    std::vector<Result> results;
    results.push_back(
        CreateResult5("ああ", "ああ", 5000, prediction::UNIGRAM, Token::NONE));
    results.push_back(
        CreateResult5("ああ", "アア", 4500, prediction::UNIGRAM, Token::NONE));
    results.push_back(
        CreateResult5("ああ", "吁", 0, prediction::SINGLE_KANJI, Token::NONE));
    results.push_back(
        CreateResult5("ああ", "咨", 1, prediction::SINGLE_KANJI, Token::NONE));
    results.push_back(
        CreateResult5("ああ", "噫", 2, prediction::SINGLE_KANJI, Token::NONE));
    results.push_back(
        CreateResult5("あ", "亜", 1000, prediction::SINGLE_KANJI, Token::NONE));
    results.push_back(
        CreateResult5("あ", "亞", 1001, prediction::SINGLE_KANJI, Token::NONE));
    for (int i = 0; i < results.size(); ++i) {
      if (results[i].types == prediction::SINGLE_KANJI) {
        results[i].lid = data_and_predictor->pos_matcher().GetGeneralSymbolId();
        results[i].rid = data_and_predictor->pos_matcher().GetGeneralSymbolId();
      } else {
        results[i].lid = data_and_predictor->pos_matcher().GetGeneralNounId();
        results[i].rid = data_and_predictor->pos_matcher().GetGeneralNounId();
      }
    }

    EXPECT_CALL(*aggregator, AggregateResultsForMixedConversion(_))
        .WillRepeatedly(Return(results));
  }

  const ConversionRequest convreq =
      CreateConversionRequest(ConversionRequest::PREDICTION, "ああ");
  const std::vector<Result> results = predictor.Predict(convreq);
  ASSERT_EQ(results.size(), 7);
  ASSERT_EQ(results[0].value, "アア");
  ASSERT_EQ(results[1].value, "ああ");
}

TEST_F(DictionaryPredictorTest, Dedup) {
  auto data_and_predictor = std::make_unique<MockDataAndPredictor>();
  DictionaryPredictorTestPeer predictor_peer =
      data_and_predictor->predictor_peer();
  // turn on mobile mode
  request_test_util::FillMobileRequest(request_.get());

  {
    constexpr int kSize = 5;
    std::vector<Result> results;
    for (int i = 0; i < kSize; ++i) {
      results.push_back(CreateResult6("test", absl::StrCat("value", i), 0, i,
                                      prediction::REALTIME, Token::NONE));
      results.push_back(CreateResult6("test", absl::StrCat("value", i), 0,
                                      kSize + i, prediction::PREFIX,
                                      Token::NONE));
      results.push_back(
          CreateResult6("test", absl::StrCat("value", i), 0, 2 * kSize + i,
                        prediction::TYPING_CORRECTION, Token::NONE));
      results.push_back(CreateResult6("test", absl::StrCat("value", i), 0,
                                      3 * kSize + i, prediction::UNIGRAM,
                                      Token::NONE));
    }

    const ConversionRequest convreq =
        CreateConversionRequest(ConversionRequest::PREDICTION, "test");
    results = predictor_peer.RerankAndFilterResults(convreq, results);
    EXPECT_EQ(results.size(), kSize);
  }
}

TEST_F(DictionaryPredictorTest, TypingCorrectionResultsLimit) {
  auto data_and_predictor = std::make_unique<MockDataAndPredictor>();
  DictionaryPredictorTestPeer predictor_peer =
      data_and_predictor->predictor_peer();

  // turn on mobile mode
  request_test_util::FillMobileRequest(request_.get());

  std::vector<Result> results = {
      CreateResult6("tc_key0", "tc_value0", 0, 0, prediction::TYPING_CORRECTION,
                    Token::NONE),
      CreateResult6("tc_key0", "tc_value1", 0, 1, prediction::TYPING_CORRECTION,
                    Token::NONE),
      CreateResult6("tc_key0", "tc_value2", 0, 2, prediction::TYPING_CORRECTION,
                    Token::NONE),
      CreateResult6("tc_key1", "tc_value3", 0, 3, prediction::TYPING_CORRECTION,
                    Token::NONE),
      CreateResult6("tc_key1", "tc_value4", 0, 4, prediction::TYPING_CORRECTION,
                    Token::NONE),
      CreateResult6("tc_key1", "tc_value5", 0, 5, prediction::TYPING_CORRECTION,
                    Token::NONE),
      CreateResult6("tc_key1", "tc_value6", 0, 6, prediction::TYPING_CORRECTION,
                    Token::NONE),
  };

  const ConversionRequest convreq =
      CreateConversionRequest(ConversionRequest::PREDICTION, "original_key");
  results = predictor_peer.RerankAndFilterResults(convreq, results);

  EXPECT_EQ(results.size(), 3);
  EXPECT_TRUE(FindCandidateByValue(results, "tc_value0"));
  EXPECT_TRUE(FindCandidateByValue(results, "tc_value1"));
  EXPECT_TRUE(FindCandidateByValue(results, "tc_value2"));
}

TEST_F(DictionaryPredictorTest, SortResult) {
  auto data_and_predictor = std::make_unique<MockDataAndPredictor>();
  DictionaryPredictorTestPeer predictor_peer =
      data_and_predictor->predictor_peer();
  // turn on mobile mode
  request_test_util::FillMobileRequest(request_.get());

  std::vector<Result> results = {
      CreateResult6("test", "テストＡ", 0, 10, prediction::UNIGRAM,
                    Token::NONE),
      CreateResult6("test", "テストＢ", 0, 100, prediction::UNIGRAM,
                    Token::NONE),
      CreateResult6("test", "テスト０００", 0, 1, prediction::UNIGRAM,
                    Token::NONE),
      CreateResult6("test", "テスト００", 0, 1, prediction::UNIGRAM,
                    Token::NONE),
      CreateResult6("test", "テスト１０", 0, 1, prediction::UNIGRAM,
                    Token::NONE),
      CreateResult6("test", "テスト０", 0, 1, prediction::UNIGRAM, Token::NONE),
      CreateResult6("test", "テスト１", 0, 1, prediction::UNIGRAM, Token::NONE),
  };
  const ConversionRequest convreq =
      CreateConversionRequest(ConversionRequest::PREDICTION, "test");
  results = predictor_peer.RerankAndFilterResults(convreq, results);

  ASSERT_EQ(results.size(), 7);
  ASSERT_EQ(results[0].value, "テスト０");      // cost:1
  ASSERT_EQ(results[1].value, "テスト１");      // cost:1
  ASSERT_EQ(results[2].value, "テスト００");    // cost:1
  ASSERT_EQ(results[3].value, "テスト１０");    // cost:1
  ASSERT_EQ(results[4].value, "テスト０００");  // cost:1
  ASSERT_EQ(results[5].value, "テストＡ");      // cost:10
  ASSERT_EQ(results[6].value, "テストＢ");      // cost:100
}

TEST_F(DictionaryPredictorTest, SetCostForRealtimeTopCandidate) {
  auto data_and_predictor = std::make_unique<MockDataAndPredictor>();
  const DictionaryPredictor &predictor = data_and_predictor->predictor();

  {
    MockAggregator *aggregator = data_and_predictor->mutable_aggregator();

    EXPECT_CALL(*aggregator, AggregateResultsForDesktop(_))
        .WillOnce(Return(std::vector<Result>{
            CreateResult5("あいう", "会いう", 100,
                          prediction::REALTIME_TOP | prediction::REALTIME,
                          Token::NONE),
            CreateResult5("あいうえ", "会いうえ", 1000, prediction::REALTIME,
                          Token::NONE)}));
  }

  request_->set_mixed_conversion(false);
  const ConversionRequest convreq = CreateConversionRequestWithOptions(
      {.request_type = ConversionRequest::SUGGESTION,
       .use_actual_converter_for_realtime_conversion = true},
      "あいう");

  const std::vector<Result> results = predictor.Predict(convreq);
  EXPECT_EQ(results.size(), 2);
  EXPECT_EQ(results[0].value, "会いう");
}

TEST_F(DictionaryPredictorTest, InvalidPrefixCandidate) {
  auto data_and_predictor = std::make_unique<MockDataAndPredictor>();
  const DictionaryPredictor &predictor = data_and_predictor->predictor();
  MockAggregator *aggregator = data_and_predictor->mutable_aggregator();
  MockRealtimeDecoder *realtime_decoder =
      data_and_predictor->mutable_realtime_decoder();

  // Exact key will not be filtered in mobile request
  request_test_util::FillMobileRequest(request_.get());

  {
    Result result;
    result.key = "ーひー";
    result.value = "ーひー";
    result.key = "ーひー";
    result.cost = 0;
    EXPECT_CALL(*realtime_decoder, Decode(_))
        .WillRepeatedly(Return(std::vector<Result>({result})));
  }

  {
    EXPECT_CALL(*aggregator, AggregateResultsForDesktop(_))
        .WillRepeatedly(Return(std::vector<Result>{
            CreateResult6("こ", "子", 0, 10, prediction::PREFIX, Token::NONE),
            CreateResult6("こーひー", "コーヒー", 0, 100, prediction::UNIGRAM,
                          Token::NONE),
            CreateResult6("こーひー", "珈琲", 0, 200, prediction::UNIGRAM,
                          Token::NONE),
            CreateResult6("こーひー", "coffee", 0, 300, prediction::UNIGRAM,
                          Token::NONE)}));
  }

  const ConversionRequest convreq =
      CreateConversionRequest(ConversionRequest::PREDICTION, "こーひー");
  const std::vector<Result> results = predictor.Predict(convreq);
  EXPECT_FALSE(FindCandidateByValue(results, "子"));
}

TEST_F(DictionaryPredictorTest, AggregateTypingCorrectedResultsTest) {
  auto data_and_predictor = std::make_unique<MockDataAndPredictor>();
  MockAggregator *aggregator = data_and_predictor->mutable_aggregator();
  EXPECT_CALL(*aggregator, AggregateTypingCorrectedResultsForMixedConversion(_))
      .WillRepeatedly(Return(std::vector<Result>{
          CreateResult7("とうきょう", "東京", 100, 0,
                        prediction::UNIGRAM | prediction::TYPING_CORRECTION,
                        Token::NONE, 0.8),
          CreateResult7("とうきょう", "トウキョウ", 200, 0,
                        prediction::UNIGRAM | prediction::TYPING_CORRECTION,
                        Token::NONE, 0.4),
      }));

  config_->set_use_typing_correction(true);

  DictionaryPredictorTestPeer predictor_peer =
      data_and_predictor->predictor_peer();

  // 0.8 900
  {
    const ConversionRequest convreq =
        CreateConversionRequest(ConversionRequest::PREDICTION, "とあきよう");
    const std::vector<Result> results =
        predictor_peer.AggregateTypingCorrectedResultsForMixedConversion(
            convreq);
    EXPECT_EQ(results.size(), 2);
  }

  // disable typing correction.
  {
    config_->set_use_typing_correction(false);
    const ConversionRequest convreq =
        CreateConversionRequest(ConversionRequest::PREDICTION, "とあきよう");
    const std::vector<Result> results =
        predictor_peer.AggregateTypingCorrectedResultsForMixedConversion(
            convreq);
    EXPECT_TRUE(results.empty());
  }
}

TEST_F(DictionaryPredictorTest, Rescoring) {
  auto supplemental_model = std::make_unique<engine::MockSupplementalModel>();
  EXPECT_CALL(*supplemental_model, RescoreResults(_, _))
      .WillRepeatedly(Invoke(
          [](const ConversionRequest &request, absl::Span<Result> results) {
            for (Result &r : results) r.cost = 100;
          }));

  auto data_and_predictor =
      std::make_unique<MockDataAndPredictor>(std::move(supplemental_model));
  const DictionaryPredictor &predictor = data_and_predictor->predictor();
  MockAggregator *aggregator = data_and_predictor->mutable_aggregator();
  EXPECT_CALL(*aggregator, AggregateResultsForDesktop(_))
      .WillOnce(Return(std::vector<Result>{
          CreateResult5("こーひー", "コーヒー", 500, prediction::UNIGRAM,
                        Token::NONE),
          CreateResult5("こーひー", "珈琲", 600, prediction::UNIGRAM,
                        Token::NONE),
          CreateResult5("こーひー", "coffee", 700, prediction::UNIGRAM,
                        Token::NONE),
      }));

  const ConversionRequest convreq =
      CreateConversionRequest(ConversionRequest::PREDICTION, "こーひー");
  const std::vector<Result> results = predictor.Predict(convreq);

  ASSERT_EQ(results.size(), 3);
  EXPECT_THAT(results, ::testing::ElementsAreArray({
                           Field(&Result::cost, 100),
                           Field(&Result::cost, 100),
                           Field(&Result::cost, 100),
                       }));
}

TEST_F(DictionaryPredictorTest, DoNotRescoreHandwriting) {
  // Use StrictMock to make sure that RescoreResults(), PostCorrect() are not be
  // called
  auto supplemental_model =
      std::make_unique<StrictMock<engine::MockSupplementalModel>>();
  auto data_and_predictor =
      std::make_unique<MockDataAndPredictor>(std::move(supplemental_model));

  // Fill handwriting config, request and composer
  {
    config_->set_use_typing_correction(false);
    request_->set_zero_query_suggestion(true);
    request_->set_mixed_conversion(false);
    request_->set_kana_modifier_insensitive_conversion(false);
    request_->set_auto_partial_suggestion(false);

    commands::SessionCommand command;
    commands::SessionCommand::CompositionEvent *composition_event =
        command.add_composition_events();
    composition_event->set_composition_string("かん字");
    composition_event->set_probability(1.0);
    composer_->SetCompositionsForHandwriting(command.composition_events());
  }

  const DictionaryPredictor &predictor = data_and_predictor->predictor();
  MockAggregator *aggregator = data_and_predictor->mutable_aggregator();
  EXPECT_CALL(*aggregator, AggregateResultsForDesktop(_))
      .WillOnce(Return(std::vector<Result>{
          CreateResult5("かんじ", "かん字", 0, prediction::UNIGRAM,
                        Token::NONE),
          CreateResult5("かんじ", "漢字", 500, prediction::UNIGRAM,
                        Token::NONE)}));

  ConversionRequest convreq =
      CreateConversionRequest(ConversionRequest::PREDICTION, "かんじ");
  predictor.Predict(convreq);
}

TEST_F(DictionaryPredictorTest, DoNotApplyPostCorrection) {
  // Use StrictMock to make sure that PostCorrect() is not be called
  auto supplemental_model = std::make_unique<engine::MockSupplementalModel>();
  auto data_and_predictor =
      std::make_unique<MockDataAndPredictor>(std::move(supplemental_model));

  config_->set_use_typing_correction(false);

  const DictionaryPredictor &predictor = data_and_predictor->predictor();
  MockAggregator *aggregator = data_and_predictor->mutable_aggregator();
  EXPECT_CALL(*aggregator, AggregateResultsForDesktop(_))
      .WillOnce(Return(std::vector<Result>{
          CreateResult5("かんじ", "かん字", 0, prediction::UNIGRAM,
                        Token::NONE),
          CreateResult5("かんじ", "漢字", 500, prediction::UNIGRAM,
                        Token::NONE)}));

  const ConversionRequest convreq =
      CreateConversionRequest(ConversionRequest::PREDICTION, "かんじ");
  predictor.Predict(convreq);
}

TEST_F(DictionaryPredictorTest, MaybeGetPreviousTopResultTest) {
  auto data_and_predictor = std::make_unique<MockDataAndPredictor>();
  DictionaryPredictorTestPeer predictor_peer =
      data_and_predictor->predictor_peer();

  // Result for しがこ (Initialize the prev_top).
  Result init_top =
      CreateResult4("しがこ", "志賀湖", prediction::UNIGRAM, Token::NONE);

  // Result for しがこう
  Result pre_top = CreateResult4("しがこうげん", "志賀高原",
                                 prediction::UNIGRAM, Token::NONE);

  // Result for しがこうげ. Inconsistent with prev top.
  Result cur_top =
      CreateResult4("しがこうげ", "子が原", prediction::UNIGRAM, Token::NONE);

  // Result for しがこうげ, but already consistent with the prev_top.
  Result cur_already_consintent_top = CreateResult4(
      "しがこうげんすきー", "志賀高原スキー", prediction::UNIGRAM, Token::NONE);

  pre_top.cost = 1000;
  cur_top.cost = 500;
  cur_already_consintent_top.cost = 500;

  auto *params = request_->mutable_decoder_experiment_params();

  auto create_request = [&](absl::string_view key) {
    return CreateConversionRequest(ConversionRequest::SUGGESTION, key);
  };

  // max diff is zero. No insertion happens.
  {
    params->set_candidate_consistency_cost_max_diff(0);

    EXPECT_FALSE(predictor_peer.MaybeGetPreviousTopResult(
        init_top, create_request("しが")));

    EXPECT_FALSE(predictor_peer.MaybeGetPreviousTopResult(
        pre_top, create_request("しがこう")));

    EXPECT_FALSE(predictor_peer.MaybeGetPreviousTopResult(
        pre_top, create_request("しがこうげ")));
  }

  // max diff is 2000.
  {
    params->set_candidate_consistency_cost_max_diff(2000);

    EXPECT_FALSE(predictor_peer.MaybeGetPreviousTopResult(
        init_top, create_request("しが")));

    EXPECT_FALSE(predictor_peer.MaybeGetPreviousTopResult(
        pre_top, create_request("しがこう")));

    auto result = predictor_peer.MaybeGetPreviousTopResult(
        cur_top, create_request("しがこうげ"));
    EXPECT_TRUE(result);
    EXPECT_EQ(result->value, "志賀高原");
  }

  // top is partial
  {
    EXPECT_FALSE(predictor_peer.MaybeGetPreviousTopResult(
        init_top, create_request("しが")));

    EXPECT_FALSE(predictor_peer.MaybeGetPreviousTopResult(
        pre_top, create_request("しがこう")));

    auto cur_top_prefix = cur_top;
    cur_top_prefix.types |= PREFIX;
    EXPECT_FALSE(predictor_peer.MaybeGetPreviousTopResult(
        cur_top_prefix, create_request("しがこうげ")));
  }

  // Already consistent.
  {
    EXPECT_FALSE(predictor_peer.MaybeGetPreviousTopResult(
        init_top, create_request("しが")));

    EXPECT_FALSE(predictor_peer.MaybeGetPreviousTopResult(
        pre_top, create_request("しがこう")));

    EXPECT_FALSE(predictor_peer.MaybeGetPreviousTopResult(
        cur_already_consintent_top, create_request("しがこうげ")));
  }

  // max diff is 200 -> not inserted
  {
    params->set_candidate_consistency_cost_max_diff(200);

    EXPECT_FALSE(predictor_peer.MaybeGetPreviousTopResult(
        init_top, create_request("しが")));

    EXPECT_FALSE(predictor_peer.MaybeGetPreviousTopResult(
        pre_top, create_request("しがこう")));

    EXPECT_FALSE(predictor_peer.MaybeGetPreviousTopResult(
        cur_top, create_request("しがこうげ")));
  }

  // No insertion happens when typing backspaces.
  {
    params->set_candidate_consistency_cost_max_diff(2000);

    EXPECT_FALSE(predictor_peer.MaybeGetPreviousTopResult(
        cur_top, create_request("しがこうげ")));

    EXPECT_FALSE(predictor_peer.MaybeGetPreviousTopResult(
        pre_top, create_request("しがこう")));

    EXPECT_FALSE(predictor_peer.MaybeGetPreviousTopResult(
        init_top, create_request("しが")));
  }
}

TEST_F(DictionaryPredictorTest, FilterNwpSuffixCandidates) {
  auto data_and_predictor = std::make_unique<MockDataAndPredictor>();
  const DictionaryPredictor &predictor = data_and_predictor->predictor();
  const Connector &connector = data_and_predictor->connector();
  request_test_util::FillMobileRequest(request_.get());
  constexpr int kThreshold = 1000;
  request_->mutable_decoder_experiment_params()
      ->set_suffix_nwp_transition_cost_threshold(kThreshold);

  {
    MockAggregator *aggregator = data_and_predictor->mutable_aggregator();

    std::vector<Result> results;
    {
      Result result;
      strings::Assign(result.key, "てすと");
      strings::Assign(result.value, "テスト");
      result.types = prediction::SUFFIX;
      result.cost = 1000;
      result.lid = data_and_predictor->pos_matcher().GetGeneralNounId();
      result.rid = data_and_predictor->pos_matcher().GetGeneralNounId();
      results.push_back(result);
    }

    EXPECT_CALL(*aggregator, AggregateResultsForMixedConversion(_))
        .WillRepeatedly(Return(results));
  }

  const std::vector<int> test_ids = {
      data_and_predictor->pos_matcher().GetGeneralNounId(),
      data_and_predictor->pos_matcher().GetGeneralSymbolId(),
      data_and_predictor->pos_matcher().GetFunctionalId(),
      data_and_predictor->pos_matcher().GetAdverbId(),
      data_and_predictor->pos_matcher().GetCounterSuffixWordId(),
  };

  for (int id : test_ids) {
    InitHistory("こみっと", "コミット");
    history_result_.rid = id;
    const ConversionRequest convreq = CreateConversionRequestWithOptions(
        {
            .request_type = ConversionRequest::PREDICTION,
            .max_dictionary_prediction_candidates_size = 100,
        },
        "");
    if (connector.GetTransitionCost(
            id, data_and_predictor->pos_matcher().GetGeneralNounId()) >
        kThreshold) {
      EXPECT_TRUE(predictor.Predict(convreq).empty());
    } else {
      const std::vector<Result> results = predictor.Predict(convreq);
      EXPECT_EQ(results.size(), 1);
      EXPECT_EQ(results[0].value, "テスト");
    }
  }
}

}  // namespace
}  // namespace mozc::prediction
