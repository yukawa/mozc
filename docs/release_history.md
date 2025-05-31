Release History

===============


## Release 2018-02-26 (2018-02-26)
Commit: [afb03ddfe72dde4cf2409863a3bfea160f7a66d8](https://github.com/google/mozc/commit/afb03ddfe72dde4cf2409863a3bfea160f7a66d8)
Summary:
Pull google/googletest@8a6158717bc1587a26e6134179eb9e2a9f1c2185

This CL updates src/third_party/gtest as follows:
  from: google/googletest@82b11b8cfcca464c2ac74b623d04e74452e74f32
    to: google/googletest@8a6158717bc1587a26e6134179eb9e2a9f1c2185

BUG=
TEST=unittest

## Release 2.26.4660.102 (2022-04-02)
Commit: [48bbce597765dfa52210417e6b88f38aaf024f6d](https://github.com/google/mozc/commit/48bbce597765dfa52210417e6b88f38aaf024f6d)
Summary:
Summary of changes based on commits:
- Update BUILD_OSS to 4660. (063c41f1d)
- Remove `indexOf` from `Segment`. (d52b3a5f6)
- Call `setMinimumSectionSize` to minimize unexpected margins. (81108defe)
- Add missing reference (&) for const std::string& arguments. (7f8f97e93)
- Fix build break of android:gen_touch_event_stats (a8edb2dea)
- Update BUILD_OSS to 4656. (0dcb97753)
- Add visibility to 'japanese_util' build rule. (cf2ee75a1)
- Fix flickering of candidate windows. (7d0959e1d)
- Use Qt's thread instead of Mozc's thread. (e295b47f4)
- Use Qt's signal connections instead of the loop with Abseil's mutex lock. (ec9f3227c)
- Simplify the logic of qt_mozc_renderer. (05c3af60d)
- Simplify the implementation of `qt_mozc_renderer`. (17dda1f30)
- Update the mac_sdk to 12.1 (a403341d3)
- Make QtServer directly use IPCServer. (c51806359)
- [Code Cleanup] Migrate callers of Japanese util functions in Util class to use the new ones in japanese_util namespace. (ba8c61b09)
- Update the condition of rewrite type. ARABIC_FIRST when a user types numeric keys, or the base candidate comes from user dictioanry. (df81f8eb5)
- - Added API to support Japanese spellchecker in Native Mozc layer. - Moved the testing logic of Japanese spellchecker from Java to client (3b686485c)
- Remove MozcDrawable code and data. #cleanup (669e70cd0)
- Update BUILD_OSS to 4646. (cdb6ca326)
- Set the right description for half-width tilde. (a0d2cf142)
- Remove the candidate description if the candidate is normalized. (d546d6a2c)
- Add NormalizeTextWithFlag. (ce69c277f)
- Remove unnecessary functions from FreeList. (b5e2d5023)
- Change the arguments and return value of NormalizeText. (d1ec61ca5)
- Fix a typo. (7f02ce192)
- Add necessary files for ZeroFieldsBase. (2812648d7)
- - Added spellchecker's model data to DataManager. - Added new commands for spellchecker. (ae4a1850a)
- Replace absl::make_unique by std's one. #codehealth (959ecd939)
- Bug fix: Fix candidate insersion position. (9c2ab6ef4)
- Get rid of unnecessary std::unique_ptr from session_test.cc. #codehealth (049e6d159)
- Get rid of six library from Mozc part 3. #codehealth (926b4f1da)
- Get rid of six library from Mozc part 2. #codehealth (84c3644e9)
- Get rid of six library from Mozc. #codehealth (7523c2ec5)
- Use std::min<T>() instead of std::min() (and std::max as well). (75794c9c4)
- Add variant Kanji characters with specific readings. (1e7bc5315)
- Added params to use the default large spatial penalty for extermly short keys. (b7d36d5ef)
- Replace deprecated variables with new ones. (918f69330)
- Add description.txt to the GYP rule. (f810eabe9)
- Add EXPECT_CANDIDATE_DESCRIPTION to session_handler_scenario_test.cc (57adfad2a)
- Update BUILD_OSS to 4632 (7329757e1)
- - Added support for words registered as shortcuts to be displayed during conversion. - Refactoring on cost and POS-id population of user dictionary. They are populated when looking up the user dictionary. (23a6baa48)
- Update the entries of eszett chars (ß, ẞ). (118d61530)
- Remove unintentionally added line. (0025cba8e)
- Apply formatter to .mm files. (9f5815e79)
- Remove the parent directory from Qt include paths. (bced92c01)
- Replace deprecated values with preferred values. (a6476b845)
- Include CoreGraphics/CoreGraphics.h explicitly. (8ca0cfb18)
- Add comments to #else and #endif. (da8329f94)
- Update the BUILD_OSS to 4624. (56ad8ab03)
- Update third_party/protobuf to v3.19.3 (dcf9cb0c8)
- Update protobuf.gyp to support v3.19.3. (0083058c7)
- Update package versions (b04f95c8e)
- Make MOZC_DOCUMENT_DIR configurable. (15c631d59)
- Update build paths in build_mozc_in_docker.md. (f37d831ec)
- Rename MOZC_SERVER_DIRECTORY to MOZC_SERVER_DIR in base/base.gyp (fdb294a8b)
- Update the BUILD_OSS to 4617. (273be57ac)
- Rename MOZC_SERVER_DIRECTORY to MOZC_SERVER_DIR (a80c919e5)
- Make the browser opening command configurable. (09d4c7d98)
- Add an entry reported from GitHub. (bdfac1f28)
- Make the mozc install directory configurable. (500768f15)
- Add entries to aux_dictionary and evaluation test cases. (434178120)
- Replace setBackgroundColor with setBackgroundColor. (b466a5290)
- Update the BUILD number to 4610. (c914d1dfe)
- Remove QT_VERSION from mozc_version.txt (6d4e3014b)
- Remove checking QT_VERSION. (cf2472d5d)
- Add entries to aux_dictionary.tsv (c67b4c91b)
- Add cost_offset to aux_dictionary (f6d294e31)
- Add test cases reported from the GitHub issues. (26409ddd0)
- Use BUILD_OSS for generating dictionary_oss/evaluation.txt (794d3b9e8)
- Update BUILD.bazel (3a14ad36a)
- Add evaluation test cases and update aux_dictionary. (c539217f5)
- Update the BUILD number to 4596. (3735608fd)
- Move Japanese util functions from Util class to japanese_util namespace. (2a0233439)
- Update BUILD.bazel. (5b29cbd05)
- Remove Util::SplitStringUsing and Util::SplitStringAllowEmpty. (4601b9862)
- Migrate remaining Util::SplitString functions to Abseil's equivalents. (0c769ca1f)
- Delete unused main files. (12bd18618)
- Migrate Util::SplitStringUsing to absl::StrSplit. (0d2ab39da)
- Migrate Util::SplitStringUsing to absl::StrSplit under rewriter/. (4eef6c1ac)
- Migrate Util::SplitStringUsing to absl::StrSplit under composer/. (1470f1519)
- Migrate Util::SplitStringUsing to absl::StrSplit under session/. (9ecd65e08)
- Update BUILD.bazel (b84e8c6ae)
- Migrate Util::SplitStringUsing to absl::StrSplit under dictionary/. (91446a7df)
- Migrate Util::SplitStringUsing to absl::StrSplit under converter/. (ce137f791)
- Migrate Util::SplitStringUsing to absl::StrSplit in base/. (b818bf1cd)
- Migrate Util::SplitStringUsing to absl::StrSplit for base/url_test.cc. (74fab3461)
- Migrate Util::EndsWith to absl::EndsWith. (9ad0d73c8)
- Change Mozc not to show character width description "[全]" for candidates not having corresponding halfwidth form. (b909766a9)
- Migrate Util::StartsWith to absl::StartsWith. (1adb8b90b)
- Fix a build break on the OSS build. (89be24134)
- Fix a build break on the OSS build. (c2edee458)
- Update the BUILD number to 4577. (01306d0c6)
- Migrate Util::ConcatStrings to absl::StrCat and absl::StrAppend. (28387e650)
- Migrate Util::JoinStrings to absl::StrJoin. (a7ad18a0e)
- Migrates uses of associative containers to more performant types (25654ccd4)
- Migrates uses of associative containers to more performant types (748b44134)
- Add a missing comment #codehealth (2dff7066e)
- Migrates uses of associative containers to more performant types (2a86009fc)
- Improve the performance of Viterbi algorithm. (ded8cc75a)
- inputlogic: Move protos to chrome/inputs/service. (507f1211d)
- Update the BUILD number to 4570. (0afa393b3)
- Reduce MozcDrawable dependency as much as possible. #codehealth (343c97bc5)
- Update the BUILD number to 4563. (24d9b4b97)
- Improve the performance of base/trie.h. (0eed3073d)
- Use modern libraries in base/trie.h. (fbeee817d)
- Remove Mozc's mutex library. (4b579a914)
- Fix build break on Mac. (74a22563a)
- Migrate mozc::CallOnce to absl::call_once for Mac code. (387e2e7ae)
- Migrate mozc::once_t to absl::once_flag for Windows modules. (c756b98e1)
- Migrate mozc::CallOnce to absl::call_once for random_keyevents_generator. (05c9fcd0c)
- Remove ResetOnce() for mozc::once_t. (12062c9d7)
- Migrates uses of associative containers to more performant types (1296aa064)
- Update the Abseil version to 20211102.0 (c9c46b8fb)
- Update the BUILD version to 4556. (3dc692847)
- Delete Util::StringPrintf. (aefe8ddf4)
- Delete unused mozc::Mutex. (2fbda10bf)
- Migrate mozc::Util::StringPrintf to absl::StrFormat. (43943ba96)
- Migrate mozc::Mutex to absl::Mutex for renderer/. (1dffd4d7c)
- Migrates uses of associative containers to more performant types (1e902d7ba)
- Fix the bug that LogStreamImpl locks the mutex twice. (facec4e29)
- Fix build break on Linux. (35c38fe57)
- Fix build break on Kokoro. (b6a61d4e6)
- Migrate mozc::Mutex to absl::Mutex. (2d6eb524f)
- Migrate mozc::Mutex to absl::Mutex for renderer/win/. (acad61397)
- Migrate mozc::Mutex to absl::Mutex for renderer/mac/. (ad3cf81b7)
- Migrates uses of associative containers to more performant types (f0c393318)
- Migrate mozc::Mutex to absl::Mutex under ipc/. (e5b36f96d)
- Migrate mozc::Mutex to absl::Mutex under ios/. (bd8369132)
- Migrate mozc::Mutex to absl::Mutex under config/. (fc53d345b)
- Migrate mozc::Mutex to absl::Mutex for base/. (08ad7ddc2)
- Replace mozc::ReaderWriterMutex by absl::Mutex. (9310cd908)
- Refactoring of logging. (96e09b3b5)
- Introduce CHECK_OK for absl::Status and absl::StatusOr<T>. (838f07ccd)
- Add a section for `--test_arg=--logtostderr --test_output=all` (bd7340363)
- Add Logging::SetLogToStderr. (bbb9677e7)
- Introduce FileUtil::GetContents, FileUtil::SetContents, and FileUnlinker. (a79436c82)
- Remove MmapSyncInterface. (5e7fdb755)
- Changed IsEquivalent to explicitly return an error if file(s) doesn't exist. (33545b427)
- Return absl::StatusOr<FileTimeStamp> for FileUtil::GetModificationTime. (88656e14b)
- Fix error_code handling of FileUtil::IsEquivalent. (2840f4cf5)
- Return absl::StatusOr<bool> from FileUtil::IsEqualFile. (62fe8f8f3)
- Return absl::Status from FileUtil::RemoveDirectory. (90a6fb48c)
- Fix build break on iPhone. (3dc26070f)
- [Code cleanup] Update field order to minimize padding (TestItem) (34c9d390a)
- mozc: Add some missing comments for #else and #endif. (b79fde2dc)
- [Code cleanup] Update field order to minimize padding (DictionaryPredictor) (c88e80f5e)
- Convert binary to utf-8 string in postbuilds_win.py. (e37031cb5)
- Enable to set the version number via MOZC_VERSION environment variable. (8adde9ee4)
- [Code cleanup] Update field order to minimize padding   (ConverterMock::ConverterInput) (27141ab46)
- Code refactoring (d0d8a87c1)
- Add evaluation test cases (85b04db41)
- Fix the sample configuration format. (aa48b23dc)
- Improved conversion logics / code refactoring (4c60f9c5a)
- Add evaluation test cases reported from the GitHub issues. (13a4143a1)
- Update the document. (46eb918b2)
- Code refactoring (absl::Status / capital cases) (7a2decc75)
- Add evaluation test cases reported from the GitHub issues. (3cac9a570)
- Update the build paths and install paths. (b91499358)
- Enable setting an extra date format. (a2d2b5779)
- Update documents. (10b69af9e)
- Code refactoring (3ae5fc284)
- Add evaluation test cases reported from the GitHub issues. (b88039602)
- Code refactoring (a3e19dec2)
- Code refactoring (1bed73e10)
- Code refactoring (7e8beed3d)
- Add configuration path and configuration files sections. (0a1d96f40)
- Add evaluation test cases (9dc639602)
- Fix the invalid candidate window size issue (d455bc33f)
- Remove iterator_adopter / code refactoring (68398eb5d)
- Update aux_dictionary. (fed70bc90)
- Code refactoring (e9be81286)
- Added evaluation test cases (eb594ddb9)
- Code refactoring (ab11cffb8)
- Code refactoring (399c91aa0)
- Refactoring / Add tools and tests. (7e2420b63)
- Add a timeout feature to the composer. (296620c04)
- Fixed build failures of unittests. (87f9ce226)
- Replaced `const` with `constexpr`. (fdfb4f9ed)
- Refactoring of `Composer`. (07c694e76)
- Set `Qt::AA_EnableHighDpiScaling` to the Qt attributes. (f76f5b176)
- Update the regression test result. (d08f2a8d9)
- Update documents. (18b2b32b4)
- Introduced aux_dictionary.tsv (7500b9bfc)
- Refactoring of quality regression test tools. (0e868861e)
- Refactoring of Bazel files. (1574f8e8c)
- Fix the format. (515b4f47c)
- Update documents. (23ca44438)
- Update documents. (343cc4114)
- Refactoring of Bazel files. (9f44ea26b)
- Add quality regression test tools and results. (0d95d4810)
- Add notes for build on other Linux environment. (f95d52365)
- Renam Bazel build rules around protobuf. (765422397)
- Added functions to FileUtil. (171aebaf3)
- Support ImeOn / ImeOff keys on Windows (8e8e24ef0)
- Fix the high CPU usage (around 100%) issue of Qt-based Mozc Renderer. (78066db57)
- Add diff b/w Bazel and GYP. (d03146963)
- Changed the default renderer to the Qt-based on the Bazel build. (865e918d2)
- Code refactoring. (a7919864e)
- Update the target Abseil version to 20210324.1. (eba0e64ef)
- Update Qt-based Mozc renderer [Experimental] (a191e8219)
- Fix build on Windows. (fc9355039)
- Reduce flickering of the Qt based candidate window (027238dd0)
- Initial implementation of Qt-based renderer. (3b3068e92)
- Rename BUILD to BUILD.bazel. (ce1b73d71)
- Code refactoring (fix potential memory leaks / Windows script) (13a0f0af9)
- Improved modifier insensitive conversions / Fixed TSAN errors. (fc187dafa)
- Remove code for Python2 (b03ab3ff5)
- Update the target name to build the installer with Bazel. (1ddec765e)
- Code refactoring (c1a9cf43d)
- Update the document for macOS build. (b040c0450)
- Removed no longer used files (JIS0212.TXT, etc). (b199f4d8d)
- Enabled Bazel to build Mozc.pkg / code refactoring (d3816084b)
- Update the document for build on macOS. (9a44dac16)
- Add a zip-code dictionary / code refactoring (2d434cb61)
- Removed the “機種依存文字” label, etc. (473a26ccd)
- Enabled to configure whether the ibus-mozc is active on launch. (467a91c5b)
- Added a Bazel build rule for icons. (f4c82a51c)
- Code refactoring (string → std::string, etc.). (8ad7b19d8)
- Added icons in 48x48 PNG and SVG. (185491de8)
- Relocated plist files for macOS. (884d9f4b6)
- Fixed issues on the Emacs client. (b8dc3b676)
- Code refactoring (std::string, cstdint, CopyFrom -> operator=) (36c81efa6)
- Add src/bazel-src_* to .gitignore. (2f958a934)
- Code refactoring (nullptr / std::string / StrContains) (492e6227d)
- Migrate to absl::flags / Fix typos. (4a9905055)
- Add *.orig to .gitignore. (835b590ad)
- Update documents. (e932d64a1)
- Use MOZC_FLAG / Deprecate Python2 (6ac62d2e8)
- Update user configurations for IBus. (b356dfe4d)
- Introduce mozc::GetFlag|SetFlag as a preparation to migrate to absl::flags. (d53be8a4d)
- Update .gitignore (7f4b049ce)
- Use absl::make_unique, use mozc::flags. (6463e7160)
- Removed code for NaCl. (64d1fbd5f)
- Code refactoring of build system, debug logging, etc. (1459bab30)
- Update the copyright year to 2021. (0e5ac4142)
- Update documents and docker files. (1f4fa1737)
- Code refactoring (b8306c908)
- Tweak connection costs for number input (ebfca8c96)
- Add a workaround to get the local time zone on Windows. (27abb23f8)
- Enable to modify the iBus keyboard layout without the root permission. (9ba59b64d)
- Update from the upstream. (BUILD=4219) (ba7cbecb7)
- Update FileUtilMock and its tests. (e522ae8cd)
- Update from the upstream. (BUILD=4206) (91cc1e19e)
- Increased the BUILD number to 4200. (e769997e0)
- Update from the upstream. (BUILD=4200) (81edac6bb)
- Update from the upstream (BUILD 4190). (cfd05a090)
- Update third_party/abseil-cpp to 20200923.2 (4a0e5b49c)
- Update from the upstream. (caca91e0e)
- Update build_mozc_in_docker.md (42426e181)
- Update from the upstream. (4700ed5fb)
- Update build_mozc_in_docker.md. (08c834253)
- Update from the upstream. (6d4feed93)
- Update third_party/gtest to `release-1.10.0` (b75198845)
- Update from the upstream. (a5a4927c1)
- Fix a runtime error on Linux. (068a1f3d3)
- Update third_party/breakpad to 2020-01-28. (9735f446c)
- Update from the upstream. (262156b03)
- Update the submodule of third_party/gyp to support Python3 build. (667db549e)
- Update from the upstream repository. (bc9eab5b1)
- Tweak BUILD and related files. (a223fdc4c)
- Fix format error. (7a945845d)
- Remove no longer used third_party libraries. (eda3b9d9b)
- Update README.md and docs/build_mozc_in_docker.md (5979e5a84)
- Update .gitignore. (4d5a7da61)
- Add files for Bazel build. (c1bea70b6)
- Update Dockerfiles. (5a4af2fee)
- Add docker files for Ubuntu 20.04. (c268b2793)
- Update third_party/protobuf to v3.13.0 (988905854)
- Add third_party/abseil-cpp (20200225.2) as a submodule. (99fb908db)
- Update from the upstream repository. (a1dcadabd)

## Release 2.28.4880.102 (2022-10-22)
Commit: [804bd863d6008f92fc1cb6d01bb3f050d6698d3c](https://github.com/google/mozc/commit/804bd863d6008f92fc1cb6d01bb3f050d6698d3c)
Summary:
Summary of changes based on commits:
- Update BUILD_OSS to 4880. (665277215)
- Check the existence of candidates in CollocationRewriter::RewriteCollocation. (e70d0a0fa)
- Add evaluation entries. (3b8544927)
- Check the return value of some decoder calls. (f789b4d13)
- Remove u8 string literal prefixes. (2896a203a)
- Update minimum_os_version to macOS >= 10.13 (7970d8913)
- Reorganize SetConfig, SetRequest, and Reload methods in SessionHandler (efb331f41)
- [Tablet 12keys] Fix romaji table (1a68202fa)
- Fix a potential runtime error with a character of 16+ codepoints. (69d4b7031)
- Clear undo context on Session::SetConfig() (0081ccdda)
- Internal change. (0a8903627)
- Add more IVS words to candidates. (2d367e742)
- - For the internal versions of mozc, we build the a11y description data on demand - For the OSS version of mozc, we added minimum dataset (`a11y_description_data.tsv`) just for unit testing purpose    - GYP build rules also use `a11y_description_data.tsv` since they cannot depend on tamachiyomi BUILD rule (e31edb678)
- Change description to "環境依存(IVS)" (3d2ef5c91)
- Fix 1 ClangTidyReadability findings: * redundant call to strlen and std::string::c_str (23d4237b5)
- Add more detailed annotations for hieroglyphs. (d71f65cdb)
- Support additional description for IVS candidates (81124c517)
- Fix a build error on some build systems. (68bc84068)
- Correctly adjust the byte offsets of cached results when whitespaces are inserted. (50176a7f4)
- Edit environmental_filter_rewriter for addition of hieroglyphs. (e7ae4a070)
- Optimize CharacterGroupFinder::FindMatch. (7620757f6)
- Sort emoji_data.tsv (bfb5bd919)
- Stop looking up overlapping nodes for prediction (65dc17c6d)
- Add IvsVariantsRewriter (fbedec28f)
- #a11y-support-in-mozc Improves `Util::SplitStringToUtf8Graphemes()` to support combined emoji characters. (ae77375cd)
- Add methods to UnicodeRenderableChecker and SimpleJapaneseIme for Japanese IVS support (fa51f930a)
- Add boundary check for EnvironmentalFilterRewriter, to avoid Unicode Codepoints come the position. (b405a57ce)
- Add flag for EnvironmentalFilterRewriter. (51283eeb6)
- Fix GYP build break due to directory change of jsoncpp. (bc8d6e055)
- Fix 55 ClangTidyBuild findings: * missing #include <iterator> for 'std::size' * missing #include <istream> for 'std::istream' * missing #include <vector> for 'std::vector' * missing #include <ios> for 'std::ios' * missing #include <utility> for 'std::make_pair' * missing #include <utility> for 'std::pair' * missing #include <map> for 'std::map' * missing #include <ostream> for 'std::endl' * missing #include <ostream> for 'std::ostream' * missing #include <sstream> for 'std::ostringstream' * missing #include <memory> for 'std::unique_ptr' * missing #include <iterator> for 'std::back_insert_iterator' * missing #include <ios> for 'std::ios_base' * missing #include <list> for 'std::list' (bf9e74f87)
- Fix 65 ClangTidyBuild findings: * missing #include <vector> for 'std::vector' * missing #include <utility> for 'std::pair' * missing #include <iterator> for 'std::size' * missing #include <utility> for 'std::make_pair' * missing #include <ostream> for 'std::endl' * missing #include <ios> for 'std::ios' * missing #include <map> for 'std::map' * missing #include <iterator> for 'std::distance' * missing #include <memory> for 'std::unique_ptr' * missing #include <memory> for 'std::make_shared' * missing #include <memory> for 'std::make_unique' * missing #include <memory> for 'std::shared_ptr' * missing #include <ios> for 'std::ios_base' * missing #include <ios> for 'std::streampos' * missing #include <ios> for 'std::streamsize' * missing #include <iostream> for 'std::cin' * missing #include <iterator> for 'std::back_inserter' * missing #include <atomic> for 'std::atomic_load' * missing #include <cstring> for 'std::memcpy' * missing #include <ostream> for 'std::ostream' * missing #include <set> for 'std::set' (f3fb168ad)
- Fix 48 ClangTidyBuild findings: * missing #include <vector> for 'std::vector' * missing #include <iterator> for 'std::size' * missing #include <ostream> for 'std::endl' * missing #include <ostream> for 'std::ostream' * missing #include <ios> for 'std::ios' * missing #include <memory> for 'std::unique_ptr' * missing #include <utility> for 'std::pair' * missing #include <memory> for 'std::make_unique' * missing #include <limits> for 'std::numeric_limits' * missing #include <ios> for 'std::ios_base' * missing #include <iterator> for 'std::make_move_iterator' * missing #include <deque> for 'std::deque' * missing #include <utility> for 'std::make_pair' (158ba59db)
- Fix 3 ClangTidyBuild findings: * missing #include <iterator> for 'std::distance' * missing #include <iterator> for 'std::size' * missing #include <utility> for 'std::pair' (6e05a433e)
- Move Util::IsAndroidPuaEmoji to user_history_predictor.cc (0ba9a1061)
- Remove available_emoji_carrier field from commands.proto. (a2bf739ee)
- Unify superscript/subscript conversion into mixed conversion in SmallLetterRewriter (1b09de6c5)
- Add an entries into AdditonalRenderableCharacterGroup (701aa5960)
- Remove Android PUA and EmojiCarrierType declaration. (b3a56873f)
- Add src/renderer/qt/ to the directories we may accept pull requests. (2c65c32d3)
- Changed the prefix penalty calculation so that the prefix of a single entry will not be promoted. (e3ffaf18e)
- Update renderer/qt (c85c85312)
- Add hieroglyphs to symbol.tsv (0c75cbd12)
- Add days of the week with brackets (e.g., (水)). (b8b97152e)
- Replace char32 with char32_t (ffed4b83c)
- Add voiced Kana for っ and ッ (70bd432f7)
- Fix 3 ClangTidyBuild findings: * missing #include <istream> for 'std::istream' * missing #include <iterator> for 'std::size' * missing #include <vector> for 'std::vector' (85ae5d4f0)
- Update the spellchecker directory. (a9d0a4a3f)
- Add dakuten Kana into symbol.tsv (88605363d)
- Fix wrong tabs in some Hentaigana entries. (77c24b023)
- Fix GYP Linux build. (6c439e523)
- Update emoji_data.tsv to support Emoji 15.0 (9e2e37cb5)
- Remove Hentaigana Rewriter relating items, and add them in symbol.tsv. (3dc21e5d6)
- Use std::search instead of manually-written algorithms. (86dc3879e)
- Fix build on Windows. (d187902b0)
- Emoji candidate filtering based on introduction version (ca4988253)
- Add NO_MODIFICATION to Segment::Candidate::Attribute (bb9391fae)
- Use the default dataset magic value if the flag value is empty. (252a2356b)
- Fixed the rewriter insertion position to respect the given offset. The previous implementation can insert candidates before the default top candidate. (c64adb128)
- Clear candidates before generating realtime candidates. User history predictor may add candidates before dictioanr predictor and candidates can be duplicated in generating realtime candidates. (d86a35fd7)
- Fix a typo. (405b80b33)
- Use mozc::protobuf:: instead of proto2:: (1a669d0fc)
- Replace char32 with char32_t (17f13f86b)
- Fix 2 ClangTidyBuild findings: * missing #include <cstdlib> for 'std::getenv' * missing #include <vector> for 'std::vector' (44d085bcc)
- Automated visibility attribute cleanup. (436b8f55f)
- Introduce additioinal_character_group_capability into commands.proto, and enable/disable SingleHentaiganaRewriter based on the field. (75d5c6c2a)
- Disable zero query suggestion of Emoji, when key is only one non-Kanji character. (ea46324c8)
- Add unicode introduction version fields into emoji_data.tsv. (5878136a4)
- Remove data/emoji/emoji.tsv (311b41818)
- Update build rules of Ibus for linux. (ddf86d853)
- Delete no longer usable carrier emoji entries (19096b8d7)
- Remove unnecessary fields from emoji_data.tsv. (9c6d5c70a)
- Change suggest_after_zero_query scenario, in order to avoid failure caused by emoji addition. (b5d0054ee)
- Rename NormalizationRewriter to EnvironmentalFilterRewriter (dbb59fcb8)
- Remove char32 declaration from port.h (8662a69cb)
- Conduct IsValidUtf8 validation when Load. (bf5e3ce23)
- Add a decoder experiment param to cancel segment model penalty. (f5bb95b1a)
- - The new rewriter is not enabled unless `enable_a11y_description` is explicitly set to true by Mozc clients (372389fe5)
- Fix 1 ClangTidyBuild finding: * missing #include <vector> for 'std::vector' (806802899)
- Add several kanji to sorted_manual_data.tsv. (d2a74bbae)
- Fix a typo and build error. (8ec478f04)
- Update emoji_data.tsv to support Unicode 13.0 and 14.0 Emojis. (6d8591055)
- Replace hard-coded Hentaigana data with build-time generated inc file. (f5e177ca0)
- Fix memory leaks in gtk_candidate_window_handler.cc (d835c7815)
- SessionHandler::GetStoredConfig() to set *merged* Config (57409b7b7)
- Update the usage of testing libraries for the internal linux build. (8705e4726)
- Update BUILD_OSS to 4830. (490cffc7f)
- Use //testing:gunit_main (72f91f319)
- Add some symbols (6fb2c7a05)
- Fix unexpected nondeterministic behavior in session_handler_stress_test (92c099f5c)
- Clear up GenericStorageEntry (238354fad)
- Automated visibility attribute cleanup. (2d3728ae8)
- Fix the build failures caused by always true expression. (05237e0ea)
- Fix 2 ClangTidyBuild findings: * missing #include <iterator> for 'std::size' * missing #include <utility> for 'std::pair' (4aac4eb28)
- Fix 33 ClangTidyBuild findings: * missing #include <iterator> for 'std::size' * missing #include <ostream> for 'std::ostream' * missing #include <vector> for 'std::vector' * missing #include <memory> for 'std::unique_ptr' * missing #include <utility> for 'std::pair' * missing #include <ios> for 'std::ios' * missing #include <ostream> for 'std::endl' * missing #include <map> for 'std::map' * missing #include <ios> for 'std::ios_base' * missing #include <iterator> for 'std::distance' * missing #include <utility> for 'std::make_pair' (fe029a804)
- Fix 3 ClangTidyBuild findings: * missing #include <cstdlib> for 'std::strtod' * missing #include <cstring> for 'std::strerror' * missing #include <ctime> for 'std::localtime' (dd6b545f2)
- - Remove enable_strict_candidate_filter from DecoderExperimentParams - Relaxed a condition for typical candidates   - Before: Only one "自立語" + one "付属語" was allowed     After: "自立語" + multiple "付属語" is allowed (e.g. "読め|ない|よう")   - Without this modification, quality regression test does not pass (c64638695)
- Add SingleHentaiganaRewriter. (bbb070605)
- Replace char32 (internally declared, signed integer) into char32_t (unsigned integer), introduced in C++11. (04ceb46c0)
- Fix the build errors of dictionary_predictor_test with GYP. (1b97feefc)
- Add candidates from number decoder. (a557c3a33)
- Add more letters into small_letter_rewriter. (a77102992)
- Include googletest.h in gunit.h (14ce9719a)
- Use Android NDK 21 in GitHub Actions. (466be45e6)
- Add a candidate filter logic for multiple number nodes. (0ea29d6b9)
- PiperOrigin-RevId: 467583091 (fcc7d8df7)
- Add Character Filter into NomalizationRewriter. (52fb9e2c5)
- Unset the Android NDK setting to skip the unnecessary configuration. (ea60ef4b6)
- mozc: Use same parameter names in .h/.cc files (86691268d)
- Add more info to log. (634ebb9a0)
- Add a note to Util::IsAcceptableCharacterAsCandidate. (69700e8d9)
- Remove unused `keymap_setting`. (c2a3a5cc9)
- Include googletest.h to fix the build error. (4ce0ac9fb)
- Add bidirectional text controls validation into Util::IsAcceptableCharacterAsCandidate. (705c38091)
- Add number decoder (d9442a93f)
- Add validation before reconevrsion (255b9e68f)
- Add an overload of ConfigHandler::GetConfig() which returns std::unique_ptr (e137e2768)
- #codehealth Make SessionHandler's config_ and request_ const (ab3cbf80d)
- #codehealth Remove redundant config_ update (592040e86)
- Overwrite request type SUGGESTION in SuggestWithPreferences (7096decba)
- For enrich partial candidates feature: Stop filtering realtime candidates which consist of one segment. (5d366a6a3)
- Fix stack-use-after-scope introduced by cl/464505510 (26fe9aed3)
- Fix potential use-after-free against prev_context_.config_ (4a958397a)
- Do not reset segments_ when Converter::StartPartialPredictionForRequest returns false in SessionConverter::ExpandSuggestion(). We can simply use the previous suggestion candidates in this case. (46f1ded13)
- Add Superscript / Subscript conversion from prefixed number expressions The rewriter is named 'SmallLetterRewriter', but it is rather a temporal name. Better naming should be come up. (9240f09fe)
- Add includes and deps explicitly. (d1f5657f9)
- Add LongestMatch() to Trie. (564fbc307)
- #codehealth Export all the .tsv files from data/keymap/ (d7b807e83)
- * fix typo: be splitted -> be split (87842b0c1)
- #codehealth Get rid of one-shot keymap (d186231c2)
- Add includes explicitly. (5a2c4738b)
- Updated the documents about Bazel only features. (cebd5eb63)
- Update the BUILD_OSS to 4800. (9dc923ab8)
- Introduce the mechanism of dictionary filter to dictionary_oss. (20006e855)
- #codehealth Make keymap_ const (e26e6b8c0)
- Add InitRequestForSvsJapanese. (67b29ddf8)
- Add scenario test for experiment params #codehealth (29e52b092)
- Remove dictionary_config_data. (53a9e7f1e)
- Fix the typo. (854e2cf26)
- Possible fix for GYP build breakage caused by cl/460687543 (ed5cdc3c1)
- #codehealth Make slightly more readable (bdc50609d)
- Fix the build error of implicit conversion from absl::string_view to std::string. (1216e3a88)
- Add SVS variation option to SingleKanjiRewriter. (6f00f2bef)
- Support henkan, muhenkan, ro, and yen keys on Japanese 109A keyboard (249814b0a)
- Add TextNormalizer::NormalizeTextToSvs. (7000ba202)
- Add Utf8ToCodepoints and CodepointsToUtf8 to Util. (8f1e8341c)
- Add Util::SplitStringToUtf8Graphemes. (ca7bf4810)
- Fix 43 ClangTidyBuild findings: * missing #include <iterator> for 'std::size' * missing #include <ostream> for 'std::endl' * missing #include <ios> for 'std::ios_base' * missing #include <vector> for 'std::vector' * missing #include <ios> for 'std::streamsize' * missing #include <istream> for 'std::istream' * missing #include <ios> for 'std::ios' * missing #include <utility> for 'std::pair' * missing #include <fstream> for 'std::ifstream' * missing #include <system_error> for 'std::error_code' * missing #include <utility> for 'std::in_place' (9da52ff96)
- Fix 64 ClangTidyBuild findings: * missing #include <vector> for 'std::vector' * missing #include <ostream> for 'std::ostream' * missing #include <iterator> for 'std::size' * missing #include <ostream> for 'std::endl' * missing #include <map> for 'std::map' * missing #include <ios> for 'std::ios' * missing #include <istream> for 'std::istream' * missing #include <utility> for 'std::make_pair' * missing #include <sstream> for 'std::ostringstream' * missing #include <utility> for 'std::pair' * missing #include <iterator> for 'std::back_inserter' * missing #include <ios> for 'std::ios_base' * missing #include <ios> for 'std::hex' * missing #include <memory> for 'std::make_shared' * missing #include <memory> for 'std::shared_ptr' * missing #include <memory> for 'std::unique_ptr' * missing #include <set> for 'std::set' (9ea50cc88)
- Fix 57 ClangTidyBuild findings: * missing #include <vector> for 'std::vector' * missing #include <iterator> for 'std::size' * missing #include <memory> for 'std::unique_ptr' * missing #include <set> for 'std::set' * missing #include <ostream> for 'std::endl' * missing #include <utility> for 'std::pair' * missing #include <utility> for 'std::make_pair' * missing #include <ostream> for 'std::ostream' * missing #include <map> for 'std::map' * missing #include <istream> for 'std::istream' * missing #include <iterator> for 'std::distance' * missing #include <ios> for 'std::ios_base' (a66eee9ba)
- Fix the oss_macos build error. (5c56c0706)
- Use deps instead of sdk_frameworks for the macos build. (ac9a0464e)
- Fix the CI error for macOS. (9bea28bce)
- Automated g4 rollback of changelist 458325713. (13e524c85)
- Fix the candidate filtering condition for zero query. (1bf55f4ca)
- Introduce qt_mac_repository.bzl and support MOZC_QT_PATH env var to specify the path. (5dbde5ef6)
- Reorder single kanjis of べん and add 辦(べん) to single_kanji.tsv. (793e8c243)
- Use 波括弧 and 角括弧 instead of 中括弧 and 大括弧 for {} and []. (c3b1c19eb)
- Update comments. (ac4fe2f95)
- Update BUILD_OSS to 4780. (14b444564)
- Use pkg_config_repository for Qt on Linux. (0a595ee22)
- Introduce pkg_config_repository.bzl and removed BUILD files for gtk2 and ibus. (ea23a3886)
- Add android_repository.bzl (e05888b1e)
- Add tips to ignore modified configuration files in git. (48a99e7a5)
- LSC: Explicitly state apple framework dependencies rather than using `sdk_frameworks` (5d5e3aebe)
- - Stop returning zip_code entries for predictive look up. - Change candidate filtering for enrich partial candidates.  - Relaxed condition for unigram excepting predictive entries.    → More personal name entries will be showsn for the exact input key.  - Add filtering for typing corrected prefix entries    → Noisy TC entries will be reduced (123d091e7)
- Add words to aux_dictionary.tsv (5e3542b98)
- Support ImeOn/ImeOff keys. (80bc73f06)
- Add the --strict option to gen_aux_dictionary.py (03e3e4507)
- Stop using the actual segments for aggregating realtime predictions. ImmutableConverter can modify history segments to generate candidates and that can cause the user history entry corruption. (5bbcb6751)
- Move MozcJNI to starndard directory structure (b1826f0e2)
- Add README.md about aux_dictionary.tsv (a41e5d636)
- Add pragma to turn off compiler optimizations. (dc3f8b32f)
- Update BUILD_OSS to 4770. (381240365)
- Change the default Android NDK version for GitHub Actions. (6d223e2c7)
- Comment out 'OmitFramePointers' to address an unexpected behavior. (1dc58d434)
- Undo key bug on Japanese keyboards (d0efe11cc)
- Fix 46 ClangTidyBuild findings: * missing #include <string> for 'std::string' * missing #include <utility> for 'std::move' (ec247d069)
- Add 歯周(ししゅう) to aux_dictionary.tsv (60b40c82b)
- [50Keys] Fix undo key bug (aa95e3b2f)
- NO-OP: Replace testonly = 1 with testonly = True (c8c6487bb)
- Add あせ to 😅 (U+1F605) (10b4995d6)
- Add mozc_emacs_helper and icons to `pakcage` for linux. (aedbc8e8e)
- Add --use_gyp_for_ibus_build flag. (a28746d4f)
- Add the layout and fs options to hdiutil for KeyStone. (46aac5126)
- Add くるくる and ぐるぐる to the keys for 🌀 (f9cb81f2c)
- Update BUILD_OSS to 4750. (924e6e44e)
- Change the visibility. (d5db14bff)
- Reduces redundant character form annotation in candidate description. (c4277a678)
- Update the deps rule for init_mozc_buildtool. (73f289987)
- Cleanup PY2 future imports (LSC) (559e9dc62)
- Fix the error of arguments. (d18e59b7c)
- Introduce one-phase suggestion (doing away EXPAND_SUGGESTION) (e5a6aecc8)
- Use bazel-skylib for paths.join. (1783b4eeb)
- Update BUILD_OSS to 4740. (1e53a28a1)
- Fix an OSS build error. (2d03e7be8)
- Change the recommended Build system from GYP to Bazel. (6abac096d)
- Add a comment and format the code. (05429d640)
- Update QT_BASE_PATH for macOS. (77ae702b1)
- Change the build system of GitHub Actions from GYP to Bazel. (2f6728f1c)
- Support header files under framework directories. (f82159835)
- Add Objective-C tests to Bazel rule. (d58eecc8f)
- Clear segments before Suggest. Suggest can be called twice in series around the STOP_KEY_TOGGLING command. (59650652b)
- Add 不達 and 空炊き to aux_dictionary and regression test. (f2a0b3e5d)
- Add ぴえん for 🥺 (U+1F97A) (9ffac9583)
- Add README.md to data/single_kanji/ (cbdb7b492)
- Add 禍(まが) to single_kanji.tsv (00d239d3a)
- Added CLI tool to run spellchecker with the actual pre and postprocessing. (c41f8b387)
- Enrich partial candidates The feature is flag guarded. (6c2c468a4)
- Fill incognito candidate words for the TextConversion result. (895210045)
- Fix 44 ClangTidyBuild findings: * missing #include <string> for 'std::string' * missing #include <utility> for 'std::move' * missing #include <functional> for 'std::function' * missing #include <algorithm> for 'std::copy' * missing #include <algorithm> for 'std::max' * missing #include <algorithm> for 'std::min' * missing #include <algorithm> for 'std::sort' (cd5b4ec5d)
- [50keys] Add transliteration table for 50keys (93dfbac3b)
- Updated single_kanji.tsv (052bfd41a)
- Fix build errors under mac/ on macOS. (ce1801fc7)
- Introduce objc_test_mozc. (0b7dc376a)
- Add textual_hdrs to mozc_objc_library for protobuf. (716496121)
- Move the submodule URLs from Chromium to GitHub. (0466a6abe)
- Add missing dependencies. (a7b1d060a)
- Use plistlib's load and dump instead of readPlist and writePlist. (88448f4cd)
- Set proper attributes to expectedAttributes. (c880e937b)
- Add missing dependencies. (e92f3a221)
- Accept any characters as the reading of user dictionary entry. (4eba2e818)
- Update the test for UpdateCandidates. (d4bbc3028)
- Change the error handling behaviors from abort to warning. (89dbf06b7)
- Fix the build error of CI for macOS on GitHub. (c2c8c44fc)
- Refactoring of delayedUpdateCandidates. (0aadeab52)
- Use std::size instead of arraysize. (d448720d8)
- Update BUILD_OSS to 4730. (247db142f)
- Fix the build error of GitHub Actions for macOS. (a7649f4e2)
- Fix the build error of Bazel for macOS. (adff9300c)
- Fix 46 ClangTidyBuild findings: * missing #include <string> for 'std::string' * missing #include <utility> for 'std::move' * missing #include <algorithm> for 'std::min' * missing #include <functional> for 'std::function' (c0bd08f57)
- Use setMarkedText to update the composition instead of updateComposition. (bf14479a1)
- Update the document structure. (9597de372)
- Call flush() after writing a log message to a file. (ca09e3e93)
- Check invalid UTF8 characters. (76835d1e5)
- Fix a build failure on Linux with Bazel. (03a78470f)
- Refactoring and typo fixes. (289bf688a)
- Trim redundant Qt libraries in the install package for the Bazel build. (7f8a9e71f)
- Fix build errors for macOS. (280bde3d4)
- Add Cocoa to sdk_frameworks of mac_process. (3d34a6a84)
- Update gyp.patch to support macOS 12.3 (Monterey). (da0dc1e78)
- Add the std=c++17 option to Objective-C builds. (23093a6cf)
- Use the default format. (8e725dc1a)
- Support the Linux build config with Blaze. (518af48d4)
- Add 促音便 to は行四段動詞 (e.g. 笑ふ, 笑つた) (200dbdae4)
- - Added experimental_flags to experimentally change the behavior of Japanese spellchecker. - Added min_score(s) parameter. Suppress the suggestion of the score is less than min_score. - Deprecated disable_model_bias parameter. (bb508ab6f)
- Update BUILD_OSS to 4715. (4c5d516fd)
- Add suggest_after_zero_query.txt to the GYP file. (0ec24f7f0)
- Fix 1 ClangTidyBuild finding: * missing #include <string> for 'std::string' (d5f0f421f)
- Added the experimetal flag 'disable_model_bias' to stop adding per-token bias stored in the model. (ba6993ca9)
- Fill history segment key for zero query suggstion. Realtime conversion will be failed if a segment key is empty. (635ee328a)
- Add strerror.cc (c7e467fc4)
- Add 深圳 to aux_dictionary.tsv (847cae732)
- Add the supported version for `active_on_launch`. (f9bbf703e)
- Decode UCS4 to UTF8 string in a correct way (4f94327f9)
- Fixed the infinite loop issue for invalid input strings. (20c83d7de)
- Fix 3 ClangTidyBuild findings: * missing #include <string> for 'std::string' (8b0c689e9)
- Fix 2 ClangTidyBuild findings: * missing #include <string> for 'std::string' * missing #include <utility> for 'std::move' (8659d8acc)
- Fixed a format error (972b7e801)
- Fix 5 ClangTidyBuild findings: * missing #include <string> for 'std::string' * missing #include <utility> for 'std::move' (36f5acfc6)
- Use Qt candidate window on Wayland. (310529c03)
- Performs naive sentence splitting to use the contextual information accurately. (fda6b8388)
- Add comprehensive key combinations for Yen and Backslash symbols. (6285110b2)
- Fix 1 ClangTidyBuild finding: * missing #include <string> for 'std::string' (681baa83e)
- Add Ainu characters (6b7cf3e06)
- Add keys to upper and lower characters (e.g. ⁰ and ₀). (6cd93e615)
- Add currency symbols. (46dab74e1)
- Update MINOR and BUILD_OSS to 28 and 4702. (68c943e81)
- Update dictionary (71bc121a4)
- Fix 3 ClangTidyBuild findings: * missing #include <string> for 'std::string' (275272b83)
- Move the submodule URLs from Chromium to GitHub. (f8331d15a)
- Update the GYP version to 2022-04-01. (12784090d)
- Simplify the code around MOZC_ENABLE_X11_SELECTION_MONITOR. (2790678a0)
- Add 無謬　and 無謬性 to aux_dictionary. (243cc7a9d)
- Fix 2 ClangTidyBuild findings: (3508f8237)
- Add 隙 (すき) to regression.tsv (b36cd46e3)
- Add regression.tsv (d3b83e139)
- Enable quality_regression_main to take multiple test files. (24d003e77)
- mozc: simplify gyp.patch (ec4196958)
- Refactoring: Move request type from Segments to ConversionRequest. We want to move Converter's input parameters out from Segments. (18c04be4a)
- Fix typo. (73a997418)
- Code refactoring of symbol_rewriter with modern C++ and new functions of unique_ptr<Candidate>. (6f10fb7a9)
- Add a link to Dockerfile. (28ff27b0e)
- Remove underscore from test names. (01973b3a8)
- Add test cases of 無謬. (ee57b901f)
- Replace deprecated QFontMetrics.width() function. (5bcd50587)
- Remove g_type_init(); (381aee0aa)
- Remove an unused function. (8623df0a0)
- Update BUILD_OSS to 4695. (120fce6ef)
- mozc: Remove unused using declarations (c93efe544)
- Removed the code to load/store the spellchecker in MozcData. (41702c66d)
- mozc/gui: Add missing system includes (b841d0bbb)
- mozc/base: Add missing system includes (0783f5c73)
- Loads spellchecker model via Superpacks. (7a79cd48c)
- Moved LinkOrCopyFile from engine_builder to file_util. (1bb9c6158)
- Reflect gohenkan feedback (2d9224bc0)
- Add ⺮ (たけかんむり) to symbols. (3eb73f4f1)
- Fix 4 ClangTidyBuild findings: (c194c3538)
- Fix 1 ClangTidyBuild finding: (11e961d24)
- Support new filenames for protoc. (73ec4756b)
- mozc: build64: Build other .exe files as 64-bit too (9692d253c)
- Fix 2 ClangTidyBuild findings: (ae109e606)
- Fix 1 ClangTidyBuild finding: (38ed49521)
- Remove unused visibility specs (7eea3c43d)
- Move rules of `version_def` to the `version` target. (cb2d821de)
- Update aboud_branding.md (cc3dfb203)
- Code refactoring with modern C++ and new functions of Segment::Candidate. (8e7f047c5)
- Remove unused visibility specs (ad286c953)
- Deprecates Japanese util functions in Util class. (1adc1109e)
- Fix 3 ClangTidyBuild findings: (166ae2757)
- Add insert_candidate(int i, unique_ptr<Candidate> candidate). (3b112a904)
- Refactoring: Extract a method (20a8b1dfd)
- Delete Converter::FreeSegmentValue (b5ec7e040)
- Code refactoring with std::map. (bc0b48110)
- Code refactoring with std::map. (8cd777e88)
- Check if the socket is file or not before making directories. (1b950579e)
- Add the product icon in SVG format. (61dd343a1)
- Update BUILD_OSS to 4680. (917990735)
- Fix 8 ClangTidyBuild findings: (eecfdefe4)
- Add 役立たず, 無益 and 無役 to aux_dictionary.tsv (e8ea65d32)
- Fix an error of Linux CI. (97caef3c6)
- Added score_threshold parameter to control the precions/recall trade-off. We will find the optimal threshold with offline evaluations and verify them in LE. (d16630d58)
- Remove unnecessary deps. (086a9887d)
- Add include <string> (2e7bc51b4)
- Add an entry of 役立たず (f123b3f37)
- Add note for the patch to GYP. (140ccd7ed)
- Update the year to 2022. (be3cc40a3)
- Move user_history_enabled field from Segments. (89a1a2b28)
- Integrated spellchecker into spellchecker_service. (05b8c3caf)
- Update patches to GYP for MSVC 2019. (a74a23ed0)
- Update the Windows vm from 2016 to 2019. (6881dd97e)
- Update the MSVS version from 2017 to 2019. (c87c4e21d)
- Fix 2 ClangTidyBuild findings: (84749d97e)
- Add patch for macOS to gyp.patch. (650e8de7e)
- Reformat WORKSPACE.bazel. (967f7d9dd)
- Update the CI entries. (e1a479ed6)
- Update BUILD_OSS to 4666. (c0fdbf78f)
- - Adding spellchecker_service class. This class is going to perform caching and metric logging. (e8027c4cd)
- Removed simplified reranking. (8cdb878d5)
- Use Segment::insert_candidates. (2bf411d07)
- Remove no longer necessary packages from Dockerfile. (85d50840f)
- Support 'Version' for triggering version rewriter. (002b6476c)
- Update documents about GitHub Actions. (68c754153)
- Add GitHub Actions for CIs. (3aa19b0c6)
- Add insert_candidates(int i, vector<unique_ptr<Candidate>>&& candidates). (b1425cca2)
- Undefine __cpp_inline_variables on Windows build. (a973882eb)
- Add a patch to Abseil for MSVC 2017. (3c8f42dbe)
- Use std::vector for Segment::pool_ (695fb1e72)
- Fix typos. (5659b537d)
- Use apt-get instead of apt in Dockerfile (182fa2327)
- Merge pull request #550 from akihikodaki/fix-english-grammar-in-src-workspace-bazel (f4ed28f37)
- Fix English grammar in src/WORKSPACE.bazel (cf3a9de79)

## Release 2.28.5029.102 (2023-03-01)
Commit: [9a8423ca8473967bcb81d739185e5848133d120f](https://github.com/google/mozc/commit/9a8423ca8473967bcb81d739185e5848133d120f)
Summary:
Summary of changes based on commits:
- Update BUILD_OSS to 5029. (305e9a737)
- win32 renderer: Fix compile errors with clang (8a4625c11)
- Fix a bug where the size of log_font passed to ZeroMemory was the size of the pointer (45dd0436c)
- Add win32 library definitions for gdiplus, d2d1, dwrite. (eb33c2110)
- winmain: Force the Windows subsystem (90fb8f860)
- Add a new Skylark stub for internal use (325a0d300)
- Change the description of "#" and "♯ in mobile (3478c1cf3)
- Use ABSL_HAVE_ATTRIBUTE to pack PBGR32Bitmap where available (d20146073)
- Explicitly cast LONG offset values to int32_t. (c58cfc7ea)
- Suppress msan for recursive (562d07e55)
- Remove incomatible spellchecker libraries from win32 builds (480e3c6ff)
- Refactor CharChunk::AddInputInternal with string_view (801fc1284)
- Add strings::FrontChar (57b30dbb5)
- Refactor ExistenceFilter and BlockBitmap (34e7e4f6d)
- Migrate //base:cpu_stats_main to `mozc::Thread2`. (d03953ea5)
- Migrate //dictionary:suppression_dictionary_test to `mozc::Thread2`. (2e5ffcd5b)
- Migrate //config:config_handler_test to `mozc::Thread2`. (511d2031e)
- Fix include path for ScopedCOMInitializer (d6fb264b6)
- Reorder include order for Windows (05ed98af6)
- Fix a bug where temporary string object was assigned to string_view (a1d13e264)
- Remove deprecated and unused GetFrequency and GetTicks, make Stopwatch trivially constructible. (12293ed76)
- Refactor; Use = default for eligible constructors and destructors (55a716af3)
- prediction: const std::string& -> absl::string_view (4fe04486f)
- Refactor IndicatorVisibilityTracker (8ac1e5916)
- Fix include path for ScopedCOMInitializer. (c4298f443)
- composer: const std::string& -> absl::string_view (767fe1d7c)
- Use win32::Utf8ToWide and WideToUtf8 instead of Util (2e3938609)
- Change the test path from notepad.exe to kernel32.dll (dfae1dc27)
- Use string_view to compare TOKEN_SOURCE.SourceName. (42155015c)
- Fix build failures of testing. (4b66832ed)
- Migrate //base:singleton_test to `mozc::Thread2`. (5d37b2af3)
- Add a char version of OneCharLen to strings/unicode.h (0282a2d82)
- Add file::DeleteRecursively for tests and tools. (a73f7c7c6)
- Support '#' symbol of the data/symbol/ordering_rule.txt (74b307737)
- Move ScopedCOMInitializer to a separate header-only library. (7ef96e667)
- Add win32/wide_char for Win32 wide character functions. (ade2d8a1e)
- Rename ScopedHandle::take to release and make the class movable. (ff52a7205)
- Add BUILD rules for Windows for internal builds. (04ec4ae72)
- Remove extra ifdef/endifs because undef is a no-op when the macro is not defined. (96f8b590f)
- Rewrite googletest with TempDirectory, support win32. (6effec3a3)
- Add TempDirectory and TempFile. (e50b8be58)
- Change NodeSwitchingHandler::GetModeSwitchingRule to return value (9a1f010cb)
- Add Win32 library link targets to bazel/win32. (a114c35fa)
- Add return by value overloads to Utf8ToWide and WideToUtf8. (9488c4976)
- Change const to constexpr for the embedded path constant. (7d4832c1f)
- composer: const std::string & -> absl::string_view (67ca5f863)
- Undef GetMessage to avoid conflict with the Win32 SDK macro. (5b8d43293)
- table: std::string & -> absl::string_view (eba73d6ca)
- Add tag aliases for build filtering to build_defs.bzl. (4c4b8c522)
- Change const std::string& to absl::string_view (8eb5e17aa)
- Swap the arguments for EXPECT_EQ/EXPECT_NE/ASSERT_EQ/ASSERT_NE under mozc/win32 (d08723a7e)
- Replace OS_IOS with TARGET_OS_IPHONE and TARGET_OS_OSX (if negated). (84906f6a7)
- A fix for b/269631318#comment4. (f8b46126e)
- Migrate ipc_path_manager_test to mozc::Thread2. (372a8ab15)
- Migrate //ipc:named_event_test to `mozc::Thread2`. (035257cbc)
- Fix windows build. (a3c06aaf0)
- Refactor session_handler::EvalCommand and CreateNewSessionID (31f7452da)
- Disallow copy and move of `NamedEventListener`. (9c8671dd0)
- Use flat_hash_map instead of std::map, const string & -> string_view (c9314ff08)
- Refactor main and TestScenarioInterface::Run (1284226ba)
- Use absl::flat_hash_map instead of std::map in TableManager (50b08ba52)
- Use Stopwatch::GetElapsed and refactor GetBasicStats (fc91a34ef)
- Use absl::ascii_isalpha instead of isalpha. (b1384cfdc)
- Move Win32 dependencies and includes into conditionals. (0bfac8281)
- Fix a bug that the last element in each FreeList chunk is not used. (5bbb68495)
- encrypted_string_storage: const std::string& -> absl::string_view (8cdfaad5f)
- Change the test magic number to absl::string_view with explicit length. (1e15804ef)
- multifile: const std::string & -> absl::string_view (615f1ff49)
- Move ErrorToCanonicalCode and ErrorToCanonicalStatus to file_util to avoid cyclic dependency between file_util and win_util. (89161bcbf)
- Remove redundant __ANDROID__ ifdefs where applicable. (245bd2f50)
- Internal cleanup (ac4a45230)
- Remove Unihan.txt. (8ab733ad0)
- Swap the arguments for EXPECT_EQ under mozc/usage_stats (800d3153c)
- Use absl::string_view for bracket functions. (2c76aef5a)
- s/no_android/noandroid/ (152ada719)
- Use absl::string_view in UserSegmentHistoryRewriter. (613e59f34)
- #codehealth Clean up *Stored* config (90cddb15c)
- - Bugfix: Apply `seen` check after checking other conditions. - Refactoring: Split out the result filtering logic for readability. #codehealth (b4baf700f)
- Change the string constant to char[] from absl::string_view as std::string isn't assignable from absl::string_view in some clang versions. (b68370437)
- Undef STRICT as it conflicts with the Windows macro. (c5797b70d)
- Reimplement Stopwatch with Clock::GetAbslTime(). (ebbb369da)
- Merge duplicate PushInt and ReadInt functions to bit_stream. (c0d7e1e24)
- Move trie to base/container. (eca6f727e)
- Use Clock::GetAbslTime() instead of Clock::GetTicks(). (1b76c4500)
- Refactor: Replace own code with absl::popcount and has_single_bit. (2630b8bfc)
- Add --output option to quality_regression_main. (10d0ef9bd)
- Swap the arguments for EXPECT_EQ/ASSERT_EQ under mozc/unix (d6fe633c1)
- Remove breakpad from clang win32 build because breakpad doesn't build with clang. (ac3deccf3)
- Update the rules for macOS SDK Frameworks. (78703cb31)
- Move serialized_string_array to base/container. (b053c279c)
- Move freelist to base/container (20f88f0ed)
- Replace Util::IsLittleEndian with ABSL_IS_LITTLE_ENDIAN. (bc450716e)
- Removed an unused variable. (3e4fc03d9)
- Fix the location of InitMozcRenderer. (0191dad8d)
- Remove deprecated random functions in Util. (8efa1e79d)
- Deprecate obsolete Clock functions, prefer GetAbslTime. (d15dff8ec)
- Make BitArray array_size, size, and GetValue constexpr. (bd08311b1)
- Remove clock.h from clock_mock. Depend on :clock instead. (c3f48922e)
- Replace Util::Sleep with absl::SleepFor. (1151c8710)
- Update issue templates. (72c12b435)
- Update the include paths. (b9fe11b0d)
- Automated g4 rollback of changelist 508220348. (417b53fa2)
- Merge logics and data of Bracket functions. (a4443ba37)
- Add some bracket pairs to IsOpenBracket and IsCloseBracket. (ae665f403)
- Refactoring of IsOpenBracket and IsCloseBracket. (6276ff233)
- Remove reinterpret_cast, use sizeof(uint32_t) where applicable (61e1b6445)
- Change OS_ANDROID, OS_LINUX, OS_WIN, OS_WASM macros to standard macros. (794a85385)
- Move bitarray to base/container. (1b3f44c0b)
- Change the `package` target for macOS. (bef3c7064)
- Split mozc_renderer_main.cc to each platform. (6b7a542ce)
- Swap the arguments for EXPECT_EQ under mozc/transliteration (cc45f8e79)
- Move windows renderer resource and manifest files to renderer/win32. (c7db14db5)
- Remove unused IsLowerOrUpperAscii and IsUpperOrCapitalizedAscii (c3582dea2)
- Move MacOS base files into base/mac. (3095ee052)
- Fix the test failure for macOS. (04da5a838)
- Add 速乾(そっかん) and 監理銘柄(かんりめいがら) (f396cdec2)
- Change OS_ANDROID, OS_LINUX, OS_WIN, OS_WASM macros to standard macros. (e5c8d2fff)
- Change OS_ANDROID, OS_LINUX, OS_WIN, OS_WASM macros to standard macros. (f7e17c061)
- Change OS_ANDROID, OS_LINUX, OS_WIN, OS_WASM macros to standard macros. (47498539a)
- Change OS_ANDROID, OS_LINUX, OS_WIN, OS_WASM macros to standard macros. (0c440d882)
- Change OS_ANDROID, OS_LINUX, OS_WIN, OS_WASM macros to standard macros. (12d86a5eb)
- Change OS_ANDROID, OS_LINUX, OS_WIN, OS_WASM macros to standard macros. (ae9e8e3d0)
- gen_quality_regression_test_data accepts --output to use in run_binary. (1c24b4981)
- Lowercase windows header files. (d541cfacb)
- Change WTL path to third_party_dir/wtl. (d632801c9)
- Add macro definitions for win32 build. (f0af06431)
- Lowercase windows header files. (4c575aeef)
- Lowercase windows header files. (d4db68285)
- Move Win32 code in base/ to base/win32. (31871d7c0)
- Lowercase windows header files. (3fcd0743f)
- Change Bazel rule names from _mozc to mozc_. (b3434b143)
- Fix 1 ClangTidyBuild findings: * missing #include <iosfwd> for 'std::streampos' (e4e6c944f)
- Update the BUILD_OSS to 5017. (1ba20ed7e)
- Remove the `base` collection target and depend on individual targets instead. (8c5fc9d4f)
- Fix the build error for the OSS Linux build. (aacf315db)
- Clean up includes and deps (22dd26a7a)
- Add localized titles to InstallerPane components. (2895e2740)
- Suppress redundant storage access of SetConfig (a7432fde1)
- Fix build failures for the OSS macOS. (a35241c76)
- Fix build failures for the OSS Windows. (41fdb75b2)
- Refactor `url`, remove `Util::AppendCgiParams` (80f28f45a)
- Skip PrepareAsync operation when the same model is passed. (2d56a8e32)
- mac: const std::string& -> absl::string_view (9f10716bf)
- Replace Util::Random with absl/random and mozc::random. (b713979c8)
- Migrate Util::GetRandomSequence to Random and absl/random. (35d884b8b)
- Swap the arguments for EXPECT_EQ/ASSERT_EQ under mozc/storage (c8fa35cf3)
- Fix a build failure for the OSS Linux. (fc16b8ff5)
- Fix a build failure for the OSS Windows. (d7d840bec)
- Fix build failures for OSS. (7fc752f78)
- Fix issues of the package created by pkgbuild and productbuild. (9b2dca1a7)
- Fix builder error for mac_util_main. (4204f23a0)
- Use macos_unit_test to run objc/mac unit tests. (2c3f5e484)
- #codehealth Get rid of unused bool return value (e2545866f)
- Remove target_compatible_with in base as it breaks Builder. (aeb86365f)
- client: const std::string& -> absl::string_view (d5a2d5bac)
- Replace util::Random with absl/random (090702679)
- Migrate //ipc:ipc_main to `mozc::Thread2`. (5b4da6a14)
-  clean up objc frameworks (cccf0fdf1)
- net: const std::string& -> absl::string_view; iwyu; cleanup (853e26cda)
- Swap the arguments for EXPECT_EQ/EXPECT_NE/ASSERT_EQ under mozc/session (6d0a572f1)
- Replace NumberUtil::SafeStrTo{,Hex}{Int,UInt}{16,32} with absl::Simple{,Hex}Atoi (b65493277)
- config: const std::string& -> absl::string_view (dc43a97b2)
- Add build_test. (e98577381)
- [Refactoring] Split out the candidate aggregator module from dictionary predictor. (661810018)
- engine: const std::string& -> absl::string_view (3e3ad10f0)
- Refactor SafeStrTo{UInt,Int,Double} functions. (d4a77eedf)
- Replace Util::StripWhiteSpaces with absl::StripAsciiWhitespace. (5e9d79697)
- Swap the arguments for EXPECT_EQ/EXPECT_NE/ASSERT_EQ under mozc/rewriter (ad857658f)
- Refactor segmenter. Segmenter::CreateFromDataManager returns unique_ptr. (b4665ad84)
- util, url, trie_test: const std::string& -> absl::string_view (8b17defa8)
- Create .pkg file with pkgbuild and productbuild. (4a514295c)
- Add --noqt and --oss options to tweak_installer_files.py (f5db4bcf5)
- Add the `productbuild_files` rule. (5ae04d459)
- Add "Use Henkan/Muhenkan keys as IME ON/OFF" preference for Japanese PK (97609fec8)
- Remove proto_deps from mozc_objc_library. (8b2f4c597)
- usage_stats: const std::string& -> absl::string_view; iwyu (837a16383)
- Delete unused proxy_manager.{cc.h} (b4ebc6eb4)
- Remove unused export_files targets. (01c7afcaa)
- Remove unused Util::GetRandomAsciiSequence (bbe72b91b)
- Swap the arguments for EXPECT_EQ/ASSERT_EQ under mozc/renderer (08e77c6b0)
- Remove a dependency to `composer`. (9c2e042e9)
- Change Is{Lower,Upper}Ascii to use absl::ascii_is{lower,upper}. (bbce135dd)
- Automated g4 rollback of changelist 504481677. (8f5519ca0)
- Add --base and --notest options to glob_files.py (3b029cf53)
- Remove unnecessary files from GYP build rules. (63858af59)
- Add -Wno-error to cflags. (f41727501)
- Remove ime_switch_util files. (13f2c2dba)
- Update the visibilities of the protocols. (25072b8c5)
- Swap the arguments for EXPECT_EQ/ASSERT_EQ/ASSERT_NE under mozc/prediction (8bb4b317f)
- Support overlay SessionKeymap (93ba2474d)
- Update BUILD_OSS to 5008 (913bb5b96)
- Set a public visibility to renderer libraries for OSS. (a982cda70)
- Use Client::IsDirectModeCommand instead of ImeSwitchUtil. (1a170b339)
- Add IsDirectModeCommand to ClientInterface. (715f46e40)
- Remove unused dependency of renderer/unix/const.h. (6e651d8c1)
- Rollback of changelist 507897203. (3919be6fe)
- Swap the arguments for EXPECT_EQ/ASSERT_NE under mozc/mac (f6056c52b)
- Swap the arguments for EXPECT_EQ/ASSERT_NE under mozc/net (abff6615f)
- Set a public visibility to client libraries. (2e3e7bbb7)
- Remove port.h from client/ (f611e88f4)
- Fix windows test again by setting the initial mode to PRECOMPOSITION (5ef07069c)
- Config data on the storage should be respected even without SET_CONFIG commmand (04ff66252)
- Get rid of imposed config (67b587bc0)
- Update the condition of noisy number candidates. (15cd8287e)
- Fix windows test (dca253c67)
- Add logs for IPC on macOS. (c5feaba7e)
- Swap the arguments for EXPECT_EQ under mozc/gui (802304096)
- Swap the arguments for EXPECT_EQ under mozc/ipc (e60f3c040)
- Swap the arguments for EXPECT_EQ/ASSERT_EQ under mozc/engine (aa8248865)
- Update the build instructions for macOS. (786c5d22b)
- Set KeyMapManager to Session always even when no config change is detected (54ce3e1f1)
- Swap the arguments for EXPECT_EQ/ASSERT_EQ/EXPECT_NE/ASSERT_NE under mozc/dictionary (ab7501f90)
- Update the year to 2023. (623c12799)
- Add more test cases for HiraganaToRomaji. (e34201a04)
- Swap the arguments for EXPECT_EQ/ASSERT_EQ/EXPECT_NE/ASSERT_NE under mozc/data_manager (f0b73edf8)
- Swap the arguments for EXPECT_EQ/ASSERT_EQ/EXPECT_NE/ASSERT_NE under mozc/converter (5b6f21a3b)
- Update build rules around macos_application. (0da4c6430)
- Swap the arguments for EXPECT_EQ under mozc/config (ace5577cb)
- Add words reported from GitHub. (ebd1ce24b)
- [Refactoring] Add single kanji dictionary so that we can look up single kanji entries from other modules. (0b6afe02e)
- Swap the arguments for EXPECT_EQ under mozc/composer (2719251a9)
- Swap the arguments for EXPECT_EQ under mozc/client (bc1cafab1)
- Cleanup: Change non-standard uint to NSInteger. (7e291492b)
- Swap the arguments for EXPECT_EQ under mozc/base (5469c515f)
- Fix format errors of `composition_mode`. (4fb1fc9df)
- Fix keycap digit emoji sequences. (35310992b)
- Migrate to starlark rules_android_ndk to support NDK r25 and update the actions to run with ndk r25. (c12497801)
- #codehealth Fix a typo (73d7c0b61)
- Update OSS_BUILD to 5000. (e18a3a72c)
- Upgrade actions/checkout to v3. (44d558d17)
- Add test cases for simultaneous input. (5fa355831)
- Enable to use special keys (e.g. Henkan) for composing text. (a74fea18d)
- Add 〝〟 (爪括弧, ダブルミニュート) to symbol.tsv and bracket pairs. (4610acaa4)
- Use CRect, CPoint, CSize defined in atltypes.h (dff261d64)
- Get rid of KeyMapFactory and make KeyMapManager immutable (7668dacc0)
- Remove `bool use_typing_correction` from CompositionInput::Init. (48452d763)
- Update GYP build rule for Abseil 20220623.1 (d36a7e6c2)
- Refactoring proto_library (67e81669d)
- Build android_cc_test only for linux or android. Set the visibility of the android_cc_test target to private. (d38cf9f73)
- Add ipc test programs back to BUILD. Fix compile errors in ipc_main.cc. (31d99c24e)
- Update the Abseil verstion to 20220623.1 (0ab19566e)
- Add "std::thread" compatible `mozc::Thread2`. (bbab42c34)
- Code refactoring to files under composer/ (1f4129f50)
- Replace util::Sleep with absl::SleepFor in base/. (64bea0d32)
- Replace util::Sleep with absl::SleepFor in prediction, renderer, session, unix. (ce474a720)
- Replace util::Sleep with absl::SleepFor in mac/. (41bfcc0ff)
- Replace util::Sleep with absl::SleepFor in client, config, dictionary. (c15b12eaf)
- Replace util::Sleep with absl::SleepFor in ipc/. (a9ee4d723)
- Automated g4 rollback of changelist 504139909. (487d92ce9)
- Add a decoder experiment param for use_actual_converter_for_realtime_conversion (6996c109a)
- Support capslock key for Japanese 109A (5bae523bb)
- Clean up enable_environmental_filter_rewriter flag (6c7ddf5e9)
- Replace Util::ErrnoToCanonicalCode with absl::ErrnoToStatus. (31d91177a)
- Make macro generated targets private and manual. Register objc rules with register_extension_info to enable go/build-cleaner. (2fbdbecd7)
- Specify test_size = "small" for bzl_library targets. (ff1732855)
- Use absl/random in Util::GetRandomSequence and GetRandomAsciiSequence and add an overload with absl::Span. (9bcba470e)
- Refactor evaluation.bzl and quality_regression_test.bzl. (83d304f85)
- Refactor random_keyevents_generator with absl/random (07312d2a8)
- Update BUILD files with the new mozc_ prefix rules. (a76d11bab)
- Update BUILD files with the new mozc_ prefix rules. (908d72f35)
- Refactoring of TypingCorrector (cff747c13)
- Update BUILD files with the new mozc_ prefix rules. (64af88321)
- Add GetSpecialKeyString (6f2be66e7)
- Support CharChunks with command keys only. (de91cd68f)
- Refactoring of composition_test.cc (f96581662)
- Trim a special key if it is not used for both of the current chunk and the next chunk. (5b15a39cd)
- Use Unicode PUA characters for special keys. (512b9b601)
- Change ParseSpecialKey to a member function instead of a class function. (a352c5a0f)
- Clean up base/util.{cc,h} includes. (e8e4b403c)
- Replace `mozc::UnnamedEvent` with `absl::Notification`. (298fb9f18)
- Change AddInputAndConvertedChar to a private function. (bcf356c18)
- Remove unused //base:scheduler. (a22865a76)
- Deprecate Util::Random, SetRandomSeed, and Sleep and prefer absl alternatives. (d2414a6b6)
- Remove int and uint{8,16,32,64} typedefs. (33c7206be)
- Replace uint{8,16,32,64} and int{8,16,32,64} with uint{8,16,32,64}_t and int{8,16,32,64}_t respectively. (4c2361733)
- Update BUILD_OSS to 4990. (811cb8c76)
- Include crtdbg.h for _CrtSetReportMode (8571b4b43)
- Replace DISALLOW_COPY_AND_ASSIGN with C++ standard descriptions. (810e63a41)
- Remove AS_STRING macro from base/port.h (7f3544150)
- Add 排他処理(はいたしょり) (7fd98633a)
- Add リネーム(りねーむ) to aux_dictionary.tsv (06a506bd2)
- Fix win32 build error: std::size isn't compile time in msvc 2017, use ABSL_ARRAYSIZE for now. (527a76f1a)
- Use mozc_ as a prefix for all mozc build rules. (cf4d779a9)
- Replace int and uint{8,16,32,64} with int and uint{8,16,32,64}_t respectively. (c8f8e92c9)
- Enable parse tests for bzl_library targets. (746bb2da3)
- Replace int and uint{8,16,32,64} with int and uint{8,16,32,64}_t respectively. (14a66edb9)
- Move _mozc build rule suffix to prefix. (055c72625)
- Replace int and uint{8,16,32,64} with int and uint{8,16,32,64}_t respectively to be consistent with https://google.github.io/styleguide/cppguide.html#Integer_Types (175191481)
- Migrate `exec_tools` back to `tools`. (12ad922bc)
- Replace int and uint{8,16,32,64} with int and uint{8,16,32,64}_t respectively. (cca0ac9fd)
- Replace int and uint{8,16,32,64} with int and uint{8,16,32,64}_t respectively. (b03812371)
- Replace int and uint{8,16,32,64} with int and uint{8,16,32,64}_t respectively. (483d68db6)
- Replace int and uint{8,16,32,64} with int and uint{8,16,32,64}_t respectively. (02e0cb651)
- Rename cc_{test,binary,library}_mozc etc to cc_mozc_{test,binary,library} and move  other _mozc suffix to prefix for consistency. Keep the old names for compatibility. (d16c067f7)
- Replace int and uint{8,16,32,64} with int and uint{8,16,32,64}_t respectively. (e28292209)
- Remove DISALLOW_COPY_AND_ASSIGN and DISALLOW_IMPLICIT_CONSTRUCTORS (5612f55cc)
- Replace ARRAYSIZE, arraysize, ABSL_ARRAYSIZE macros with std::size. (3327fb9b5)
- Support multiple Undo (de21c2de5)
- Add unit test for HiraganaToRomanji(). (40a2ea3b8)
- Replace deprecated DISALLOW_ macros with standard C++ constructs. (54937dfa0)
- Replace deprecated DISALLOW_ macros with standard C++ constructs. (2f08fea98)
- Remove noisy symbol entries (adca4aa34)
- Simplify the directory structure for testing. (b2e0803e9)
- Merge anonymous namespace in mozc_engine.cc (49582129a)
- Replace deprecated DISALLOW_ macros with standard C++ constructs. (a458f5fb5)
- Replace deprecated DISALLOW_ macros with standard C++ constructs. (a797c7b2b)
- Replace deprecated DISALLOW_ macros with standard C++ constructs. (2dfa8f3e0)
- Replace deprecated DISALLOW_ macros with standard C++ constructs. (ca278cdce)
- Replace deprecated DISALLOW_ macros with standard C++ constructs. (04436b7f9)
- Replace deprecated DISALLOW_ macros with standard C++ constructs. (5fc238363)
- Replace deprecated DISALLOW_ macros with standard C++ constructs. (c9b9c5a65)
- Replace deprecated DISALLOW_ macros with standard C++ constructs. (aa6d378f7)
- Add corresponding comments to #ifdef/#else/#endif (5254823b1)
- Automated g4 rollback of changelist 498517006. (fe35675d7)
- Add 堆雪(たいせつ) to aux_dictionary.tsv (9bcc6dd63)
- Support Undo also on Composition and Conversion state with a PK (7349acc2d)
- Fix build and test errors on some environment. (251138329)
- Support undo for partial commit (735bbbed2)
- Add a comment for anonymous namespace. (7050ee297)
- Fix lint warnings. (1af174060)
- Refactoring of IbusCandidateWindow. (7a902136b)
- Refactoring around main.cc (fb7492bff)
- Create GsettingsWrapper (498298bdb)
- Refactoring of CandidateWindowHandler. (7212d7fbd)
- Use string_view. (bf45cf6b5)
- Refactoring of KeyTranslator. (b232cba6a)
- Add mozc::ibus namespace to main.cc and IbusWrapper. (bcf3aed64)
- Add README.md files. (8f417ad9d)
- Add the glob feature to the GYP build. (757451988)
- Move GObject class definitions from MozcEngine to EngineRegistrar. (a4010690d)
- Use standard c++ types. (c360a38b5)
- Refactoring of ibus/main.cc (c3196afe2)
- Use wrapper functions in PreeditHandler. (54307fdf1)
- Refactoring of PreeditHandler (eca452b88)
- Change arguments of CandidateWindowHandler classes to IbusEngineWrapper. (4fd80625c)
- Change arguments of IbusEngineWrapper's RegisterProperties and UpdateProperty. (68e881304)
- Fix the default path for mozc.xml and make it configurable. (6764de06d)
- Create ibus_wrapper.cc and .h files. (cfde4cc97)
- Replace deprecated DISALLOW_ macros with standard C++ constructs. (c6d174b0d)
- Replace deprecated DISALLOW_ macros with standard C++ constructs. (70af2aaff)
- Replace deprecated DISALLOW_ macros with standard C++ constructs. (8088ce118)
- Add a note for `--msvs_version` to the Windows build. (9f4c39694)
- Fix windows build caused by cl/495769240. (49b77b2b4)
- Refactoring of DeleteAt and MaybeSplitChunkAt. (cf2653a09)
- Explicitly stream individual wide characters formatted as numbers. (a4b49855f)
- Fix the build error of protobuf. (6b9ace7dd)
- LSC: Clean up references to the legacy protobuf compat library (7f781f9c8)
- Add issue templates. (803a4190a)
- Archive the section of "GYP Build configurations". (6bc554c15)
- Remove the description "部分" for partial_suggestion #codehealth (03aa3adb6)
- Explicitly cast individual un-processable wide characters to integer types before logging them. (b2d2acf0d)
- Move files for Bazel from tools/ to bazel/ (6aaf1909c)
- Updated the filtering logic for short query. We want to suppress over-trigerring as the short query does not have enough contextual information. (93474eeb8)
- Set use_actual_converter_for_realtime_conversion false for mobile environment for testing. (ed9125120)
- Introduce `IbusPropList`. (5d6928c04)
- Introduce `IbusEngineWrapper` to PropertyHandler. (af38bbb08)
- Add test cases to composer_test.cc (dca12f565)
- Remove mozc_engine_proerty.cc and .h files. (caac5ec5b)
- Refactoring of PropertyHandler. (e7edba1bd)
- Introduce IbusEngineWrapper. (b82ed7e3a)
- Refactoring of EngineInterface. (17c941bfe)
- Refactoring of ibus_header.h and main.cc (f32e02ed8)
- Add README.md to gui/ (6f58a82c0)
- Swap the arguments of EXPECT_EQ to (actual, expected). (24e76ccc8)
- Rename GtkCandidateWindow to CandidateWindow. (dba1de7f6)
- Simplified the build configurations for Ibus. (69f8387cc)
- Add build dependencies to the GYP build. (65185f4bf)
- Fix 1 ClangTidyReadability findings: * redundant string conversion (5ee18bfbf)
- Do not run spellchecker on composition strings. (ec5847461)
- Add IfThisThenThat Lint to KeyEvent. (eb2fc704f)
- Refactoring of key_parser.h (ea66213fe)
- Make ParsekeyVector return false when it takes multiple keys or special keys. (4866060e5)
- Add the Transliterations section to README.md (7ec82c935)
- Refactoring of key_parser.cc (93e2e9a2f)
- Add README.md to composer/ (340ae3972)
- Refactoring of table_test.cc. (482088496)
- Add comments to `raw_`, `conversion_`, `pending_`, and `ambiguous_`. (4dd3b5795)
- Trim a special key if there is no rule. (fe61216b7)
- Refactoring of CharChunk::AddInputInternal. (b67806607)
- Fix a logic of `attributes_`. (759bbdd98)
- Fix a logic of `ambiguous_`. (ad1eb37f5)
- Fix an update logic of raw_. (360d2ee46)
- Update Bazel rules for macOS. (34b31eb67)
- Use typing.List for type annotation. (564303bd1)
- Update DeletionRange comment (280cd0330)
- Add a header to .def files. (92f9b9360)
- Update BUILD_OSS to 4960. (d50a8b9ae)
- Use "@platforms//os:osx" for config_setting of "apple". (e0038bf07)
- Fix an incorrect testcase for undo (0334f4199)
- Update build_mozc_in_docker.md. (6b95e8a41)
- Enable build_package.py to add icons to mozc.zip. (ac168c1ea)
- Add Emacs files to build_package.py (62f1c0e6f)
- Create build_package.py and a build rule for mozc.zip. (1f9d3e68e)
- Fix a typo in tweak_installer_file.py (3423cd837)
- Update build instructions for Linux, Android and macOS. (c71d9ff2f)
- Make SessionTest parameterized test (9e30ae718)
- Simplify the GitHub action rules for Windows. (3d42a015b)
- Support multiple level request/configuration setting (14462d46d)
- Clean up the experimental flags. - enrich_partial_candidates - cancel_segment_model_penalty_for_prediction (6ed94be0d)
- Add next word prediction entries. (e02406a22)
- Clean up the experiment flag, enable_number_decoder (d3a121da0)
- Comment out some tests taking long time (~100sec in total). (5c2ca43fe)
- Set enable_gtk_renderer=0 to GYP build by default. (999abaaf8)
- Remove unused functions from build_tools/util.py (ef7caade4)
- Update build_mozc_in_windows.md (4cfdcf17f)
- Fix a missing field on cloning (1442f3269)
- Update build_mozc.py (a77577f7c)
- Delete DictionaryMock. (7f9abda9c)
- PiperOrigin-RevId: 495772351 (0c8c43398)
- Migrate DictionaryMock to gMock-based one in dictionary_predictor_test. (0aab4b7f8)
- Remove mozc_renderer from the `package` alias in mozc_build.py (ae89dcfd0)
- Suppress a verbose log by changing log level to VLOG(2). (cd9ed4da4)
- Update TestLookuPredictiveHelper to check EXPECT_TRUE in each test. (7f1f9c745)
- Update BUILD_OSS to 4950. (db37db71b)
- Add MOZC_IBUS_CANDIDATE_WINDOW environment variable. (4a77c6a7a)
- Fix build failures for OSS with GYP. (8dcc2bb96)
- Migrate to MockDictionary in converter_test and predictor_test. (926437566)
- Add README.md to prediction/ (df7b26cd8)
- (mozc.el) Fix warnings due to cl library deprecation (#643) (cebb883f5)
- Update third_party/gtest to `release-1.12.1`. (ce854c640)
- Migrate DictionaryMock to gmock-based one in user_history_predictor_test. (33f86275e)
- Remove LOG as it is not a real error (9b3183658)
- Replace DictionaryMock by MockDictionary in date_rewriter_test. (7c9f4e60c)
- Code refactoring around CandidateWindowHandlers. (286807faf)
- Add a section for "Fixed composition mode per engine". (6c3232671)
- Simplify the logic around the initialization of the Mozc candidate window. (76d203128)
- Update Windows product icons for OSS. (58a6e12e4)
- Update Windows mode icons for OSS. (31a36c431)
- Add missing command to SESSION_INDEPENDENT_COMMAND_TYPE_SET. (a824c3db2)
- PiperOrigin-RevId: 494053115 (e8cf4194d)
- Introduce gMock-based MockDictionary and use it in language_aware_rewriter_test. (a8d84caf6)
- Add option to output zero_query_data.tsv for debugging. (ed98ea208)
- Add a missing scenario file to fix GYP build break. (06268568d)
- Add a log message. (018ca3ca6)
- Add a session handler scenario test to ensure that the REVERT command is working with BACKSPACE key in mobile suggestion (prediction in mozc command). (2949b053a)
- Add SVG icons for Windows. (ca9a20c26)
- Update product icons in SVG. (13bf0df98)
- Added rulebased filter to suppress Japanese specific corrections. (ec8f3893d)
- Remove ConverterMock and MockConverterEngine. (f2118e54c)
- Update for Mozc spellchecker (185761ca1)
- Fix build break on Kokoro Linux. (eaa40ff35)
- Clean up `mozc_one_phase_suggestion` flag (91b14108a)
- Make Japanese spellchecker available for DEV flavor (030e38653)
- Remove set_composer() and set_converter() taking raw pointers. (fbe83eebe)
- Replace ConverterMock by gMock-based MockConverter in session_test.cc. (efab15381)
- Add scenario files to fix build break. (cbe8999b3)
- Fix 12 ClangTidyReadability findings: * redundant string conversion (02a4dc13c)
- Fix 3 ClangTidyReadability findings: * redundant string conversion (ee02bf7ff)
- Fix 3 ClangTidyReadability findings: * redundant string conversion (0826160dd)
- Fix 4 ClangTidyReadability findings: * redundant string conversion (e6ddbffc5)
- Enable to keep the original config imported from the file including unconfigurable options with the GUI (e.g. composing_timeout_threshold_msec) (446c5ba9a)
- Split twelvekeys_toggle_hiragana_preedit_scenario into smaller ones (d432ef1cc)
- Enable building gen_mozc_ime_resource_header on Linux build env. (c1a8f37c9)
- Change the character encoding from UTF-16 to UTF-8. (7fadd0d61)
- Add NormalizeLayout to IbusConfig. (26eef64f4)
- Embed contents of .rc files instead of including them. (4fc1882dd)
- Add icon_base.svg for the product icon without the front character "あ". (022cd9a73)
- Replace ConverterMock by MockConverter in dictionary_predictor_test.cc. (081641ad9)
- Use MockConverter in session_converter_test.cc. (ce1dc1226)
- Use MockConverter in ime_context_test.cc. (751560693)
- Add ibus_config_test (86c0b1a07)
- Modify AsyncExecCommand to take string_view instead of string*. (faa7acdd4)
- Change Process(const string&, string*) to Process(string_view, string*). (37950b437)
- Modify IPCClient::Call to use std::string instead of char* and size_t. (9cf1a78f2)
- Modify SendMessage and RecvMessage to use std::string instead of char*. (eb4ff229f)
- Use MockConverter in dictionary_predictor_test.cc. (61b662193)
- Fix 4 ClangTidyReadability findings: * redundant string conversion (0f3d580fb)
- Fix 1 ClangTidyReadability findings: * redundant string conversion (815cc5a37)
- Fix 17 ClangTidyReadability findings: * redundant string conversion (00f2b554f)
- Fix 1 ClangTidyReadability findings: * redundant string conversion (f64da6f0a)
- Fix 2 ClangTidyReadability findings: * redundant string conversion (29aff3cfc)
- Fix 1 ClangTidyReadability findings: * redundant string conversion (99c0b6667)
- Fix 7 ClangTidyReadability findings: * redundant string conversion (3d7254959)
- Fix 1 ClangTidyReadability findings: * redundant string conversion (e07457bb0)
- Fix 3 ClangTidyReadability findings: * redundant string conversion (5462d55d5)
- Fix 1 ClangTidyReadability findings: * redundant string conversion (a82208a13)
- Fix 1 ClangTidyReadability findings: * redundant string conversion (5098d93ee)
- Fix 5 ClangTidyReadability findings: * redundant string conversion (e3d7eed37)
- Replace ConverterMock in rewriter_test.cc by MockConverter. (da0cb3354)
- Rewrite UserDataManagerMock by using gMock. (68034fb27)
- Use MockConverter in calculator_rewriter_test.cc. (513343f7f)
- Code refactoring. (62bea8034)
- Replace MockConverterEngine by MockConverter in ime_context_test.cc. (fd07f8c92)
- Replace subclasses of ConverterMock by MockConverter. (945d8c566)
- Fix windows build cased by cl/487742608. (5df7fa999)
- Remove IPCServer::Process(const char*, size_t, char*, size_t) (b6b0b0b78)
- Introduce IPCServer::Process(str, str) (2774e6e2a)
- Add a field for the composition mode to ibus_config. (96e8c8782)
- Replace ConverterMockForXXX in session_converter_test.cc by MockConverter. (132433ad3)
- Fix misaligned memory access in //storage/... (ab81d39b3)
- Add candidate extractor (348b7f890)
- Check the candidate index before access. (2173ab776)
- Disable typing corrector if InputStyle::AS_IS or InputStyle::DIRECT. (7db8b9d62)
- Fix the logging location. (263b35b7d)
- Fix the pre-allocation of Segments::pool_ in copy constructor. (75eda7bd2)
- Extend the session handler stress test to call ExpandSuggestion(). (cdb64df1f)
- Add `ibus_mozc` to `package` for the linux config. (8e8d1d9ae)
- Change IPC_RESPONSESIZE from 16*8192 to 16*16384. (aec78acc6)
- Remove intuitive romanji table and use non-intuitive one even on tablet. (2c1cde3a8)
- Promote T13N entries for Latin characters (4cfe25dd3)
- Switch KeyboardSpecification when "あa" key of 12keys tablet layout is tapped. (01f153816)
- Remove the unused GetCandidates() method. (8a8fdf8ce)
- Add ABSL_MUST_USE_RESULT to CommitXXX methods. (5dc99d398)
- Add ABSL_MUST_USE_RESULT to FocusSegmentValue. (c5bc8d4c5)
- Add ABSL_MUST_USE_RESULT annotation to ReconstructHistory. (23161e270)
- Disable toggleable state on 12keys tablet layout if flick-only option is set. (f0557870f)
- Change the return type of ConverterInterface::XXXConversion() from bool to void. (cd9db0671)
- Add ABSL_MUST_USE_RESULT annotation to StartPartialXXX methods. (9c2f146f2)
- Add ABSL_MUST_USE_RESULT annotation to StartSuggestion*. (e4d91a0d4)
- Add ABSL_MUST_USE_RESULT annotation to StartPrediction. (5162bf2eb)
- Add ABSL_MUST_USE_RESULT annotation to StartPredictionForRequest. (2edc55a1b)
- Add ABSL_MUST_USE_RESULT to StartReverseConversion. (ebeb84842)
- Stop showing noisy candidates that start with numbers for number key input. (a5be0d43a)
- [12keys tablet] Support 12keys preferences (2a732eef4)
- Add ABSL_MUST_USE_RESULT annotation to StartConversion. (a855b79ce)
- Add ABSL_MUST_USE_RESULT annotation to StartConversionForRequest. (d9631279f)
- Add entries reported from GitHub issues. (3d54b1826)
- Add more instructions about Docker build. (f3252df87)
- Add apt-get update --fix-missing to Dockerfile. (3ab1bec51)
- Add a new separeted BUILD package for quality regression test (05ec1326a)
- Add test for ResizeSegment() failure for SessionConverter. (9fa4e446d)
- Add words reported from the GitHub issues. (da6905039)
- Relaxed the condition of Segment::Candidate::IsValid(). We cannot compose segment's content key / value directly from inner segment boundary information in the current implementation. (a2a88e2a9)
- Handle ResizeSegment() failure SymbolRewriter. (29dd45757)
- Set content_key and content_value in inner segments to key and value, they are empty. (44d273272)
- Use absl::Span for ConverterInterface::ResizeSegment(). (e88550138)
- - Enable kana_modifier_insensitive_conversion for MOBILE test - Merge MOBILE_AMBIGUOUS with MOBILE (2de697665)
- Enable kana modifier insensitive conversion for mobile engine. The feature is enabled by default in the actual mozc in Gboard. (b3ba4b40e)
- Add the missing dependency on gMock for GYP build. (2a497606b)
- Fix the crash of ConverterTest.PredictSetKey in GYP debug build. (6439917f8)
- [Tablet 12keys] Branch romaji table for tablet 12Keys (9e60e0b1a)
- Add test for the case where ResizeSegment() fails. (a7c600e70)
- Don't consume the Undo key event when it's no-op (2b561450c)

## Release 2.29.5160.102 (2023-07-28)
Commit: [9cc27f51ea33f4765d0ce7580d0c93e2a8e64e1a](https://github.com/google/mozc/commit/9cc27f51ea33f4765d0ce7580d0c93e2a8e64e1a)
Summary:
Summary of changes based on commits:
- Update BUILD_OSS to 5160. (f14a3f49c)
- Add a flag to disable zero query suffix prediction. (fb51c3f51)
- HResultOr: fix compile errors with MSVC 2022 and C++20 (part 2) (475f153a8)
- Avoid allocating new std::string objects with strings::Assign and std::string::replace (32fa0a889)
- Make `win32_window_util.cc` compatible with `/std:c++20` (f07ae1bbd)
- Remove support for older Windows than Windows 10 (5c1802875)
- Fix use after std::move (a237a4d09)
- Add a reading, if missing, for prediction at commit event. (0870193dd)
- Integrate the N-gram predictor in dictionary predictor. (8de7baf13)
- renderer_interface: Remove unused StartRendererLoop and SetReceiverLoopFunction (40ba8fda2)
- Update a reference in `CONTRIBUTING.md` (feb1e18af)
- Make `win_util.cc` compatible with `/std:c++20` (0ac493769)
- HResultOr: fix compile errors with MSVC 2022 and C++20 (d922b1c38)
- internal-only change (d2e7b1a1f)
- Migrate user_history_predictor to mozc::Thread2. (c9ee06c8e)
- Migrate spellchecker_service to mozc::Thread2. (13e3394e4)
- Remove unused visibility specs (last referenced in codebase over 100 days ago) (2ba50512b)
- Also specify `ABSL_CONST_INIT` in `com_implements.cc` (90fc75fd1)
- Remove workarounds for VC++2017 (6f7574b89)
- Add `BackgroundFuture<R>`. (0b04491ef)
- Small bug fixes and improvements: - Always popualtes the corrected key to result.key. - Improves the description of typing correction. - Relax the conditions to run homonym spellchecker. (d9d04f85b)
- Make user dictionary reload synchronous for inputlogic. (696ffa13d)
- Add more comments about `use_history_suggest` and `use_dictionary_suggest`. (9937a7a3f)
- Wait for syncer for user data manager in SyncData (d8cd7757e)
- Set SelectionShortcut.SHORTCUT_123456789 always for Gboard client (bfc024e40)
- Use std::string::replace to replace strings, remove bare new, cleanup (d2fa6e4e9)
- Remove unused Util::AppendStringWithDelimiter (a564f19fe)
- Fix clang-tidy warnings: remove unreachable codes (fee8bf618)
- Cleanup: remove converter_util, move strings where possible, Segment::set_key perfect forwards the new value (f86d8b6d3)
- DictionaryPredictor: use `absl::string_view` instead of `std::string` (93219c86d)
- Cleanup; use strings::Assign, remove empty destructor (d26d7ce97)
- Refactor DictionaryGenerator (6e9f45a95)
- Update rules for data/preedit (b8ac38aff)
- Uses Segments::history_key and Segments::history_value (6759a6f4c)
- Added methods to get the history key and value. Useful to get the history information in the decoder. (414d1c1cc)
- Runs homonym spellchecker in dictionary predictor. Basic steps. - Aggregates top values grouped by the same key. (scans top 5 candidates) - Runs homonym spellchecker for each top value. - Moves or replace the corrected candidate. (22888f19a)
- Update rules for data/a11y_description. (d0a408cf3)
- Add 対象外(たいしょうがい) to the dictionary. (932ee4324)
- Automated g4 rollback of changelist 544095304. (d8d284f36)
- Move the ownership of N-gram model to the engine. (5700b545b)
- Stops homyonm spellchecker when - input is too short - the remaining part doesn't have enough contextual information. (ae78a8986)
- Change nargs of input files from "+" to "*". (c53ce8645)
- Uses all history key in composition spellchecker. (b6a92757c)
- Fix a build failure of unix_server_test.cc (873a888cd)
- Process superscripts and subscripts in number_rewriter, instead of symbol_rewriter (b5e746ecf)
- Automated g4 rollback of changelist 544017740. (10e2feb03)
- Update rules for data/emoticon. (1cebc9432)
- Update `CONTRIBUTING.md` to comply with our OSS policy (6bc017c10)
- Explicitly stream a wide character formatted as a number. (74a21b470)
- Add a debug feature to show ranking change by rescoring. (08e58a661)
- Improve performance of N-best generation in dictionary predictor. (be0992026)
- Update rules for data/symbol. (d55a6a063)
- Refactor character_form_manager.cc with the new UTF-8 classes (680189891)
- Cleanup: use constexpr string_view for string constants (8ce7f63ea)
- Cleanup: Drop python 2, use argparse, process without reading entire input, remove nested anonymous namespace. (a8b01d636)
- Added new CheckHomonymSpelling methods that peforms homonym only spellchecker. Homonym-based spelling correction can directly be used during decoding, as it is guranteed that the reading part is unchanged. (bf361004a)
- Fix clang-tidy warning; change const static -> static const (6f1535bb0)
- Cleanup: Use TestWithTempUserProfile as a base fixture for tests that needs a temporary user profile directory. Replaces manual SetUserProfileDirectory calls. (267fb2551)
- Shard slow session tests (5edd6923e)
- To learn the number candidate with the right style: - Stop expanding number candidates in user_segment_history_rewriter - Update the candidate style in variants_rewriter - Add NO_VARIANTS_EXPANSION to the candidate when number_rewriter reranked the candidate (059620e9d)
- Update build rules for data/emoji. (33d0d5026)
- Remove Android-related stuff from `common.gypi` (e8f20fa6f)
- Remove `converter_main.gyp` (1f25c388e)
- Check in `connection_single_column.txt` instead of `connection.deflate` (21af209d4)
- Bug fix: NumberUtil::NormalizeNumbersWithSuffix() treated separated numbers as number + suffix. e.x. "2,000" was treated as "2" + ",000". (af7f2304b)
- Add TestWithTempUserProfile base fixture class (29707553b)
- zstring_view: Add members to satisfy C++ Container requirement, add constructor with explicit size (a64e4306d)
- Update build rules for data/unicode. (5429c8e57)
- Update build rules for data/keymap. (2e26265b6)
- Quick fix for `SystemDictionaryTest` in GYP build (d6b00ff54)
- Add おーばーらいん, あんだーらいん, あんだーすこあ, あんだーばー into symbols.tsv (18c9710cd)
- Use ABSL_ANNOTATE_MEMORY_IS_INITIALIZED to explicitly annotate the fts buffer to avoid false positives with msan. (eff5b2758)
- Fix a TODO in `tip_text_service.cc` (73c7160d5)
- Migrate from genrule to mozc_run_build_tool to support Windows as build environment (adac32950)
- Remove `installer.gyp:mozc_installers_win_versioning` (0fa755012)
- Migrate from WRL to WIL (c595a1bb0)
- Cleanup,  ScopedHandle -> WIL, Optional -> std::optional (3b6185f4f)
- Clean up: switch to mozc_run_build_tool (02190a450)
- Rename Segment::Candidate::Init to Clear. (5cd2d51ff)
- - Demote language aware candidates on mobile. - Remove the "did you mean" annotation on mobile. (495fd15fd)
- Use the new git repository URL for `protobuf` (87f29e64a)
- Add no msan attributes to internal functions (f28fb09ed)
- Replace optparse with argparse, produce C++ source with constexpr (509ba9b87)
- Clean up: Change const to constexpr, use argparse, use mozc_run_build_tool (d40238f06)
- Add substring functions to unicode.h (b7a6d5a2b)
- Add mozc_run_build_tool Bazel rule and embed_file macro, clean up build scripts (ae2d566b7)
- Automated g4 rollback of changelist 528611092. (c5f48c143)
- Change CharChunk, Composition, CompositionInput to movable and copyable (f4b962d13)
- Use flat_hash_map for seen_tc_keys_. (2dd3c123e)
- Update code for dictionary directories. (47e88eca0)
- Remove redundant entries. (5d0db4841)
- Move PredictorInterface and derived classes to the mozc::prediction namespace (e64162854)
- Support AbslStringify in Mozc Logging (d73ecddaa)
- Update the Linux GitHub Action to use Ubuntu 22.04 and clang 14 (bb52df243)
- Use wil for Windows, change path parameter to zstring_view, move nomsan annotation to the DeleteRecursively function (9f42aa441)
- Fix use after std::move() (bbbc33244)
- Fix heap-use-after-free in CalculatePrefixPenalty (dde767d22)
- Change SerializedStringArray::difference_type to int32_t. (fdaaf4586)
- FreeList: Use `std::allocator` instead of `operator new`. (b2388119e)
- Replace SplitIterator with absl::StrSplit (36ac0fb37)
- Rename usage_stats_list.h to .inc, use run_binary to generate the header, use constexpr absl::string_view (80169bdcb)
- Refactor `NumderDecoder`, move internal classes into an internal namespace, return by value (bc73c0673)
- Add 姤(こう) to single_kanji.tsv (73f53327a)
- Implement number style learning. - The feature is guarded with enable_number_style_learning - character form manager stores number style (8d3a99ebc)
- Gyp: Fix missing dep in `user_dictionary` (e00553d35)
- Change TryInsert to take absl::string_view instead of perfect forwarding (186dbe903)
- Remove no-op `postbuilds_win.py` (813577568)
- Fix a build error for the OSS build. (cb3150e6d)
- Update BUILD_OSS to 5135. (74e06a4db)
- Add test case for values with trailing white space. (658f369f8)
- Enables multiple spellchecker backends. - Rulebased spellchecker - Old Gboard spellchecker. - SentenceExplorer (The current backend). (b4275dcd8)
- Add strings::Assign as a wrapper to assign `absl::string_view` to `std::string` (46bd69f78)
- utf8_internal: Add a comment to explain why DecodeSequence uses a template parameter (96f51f123)
- Bugfix: Stop calling actual converter for partial prediction / suggestion. (65a8e7a2b)
- Let `build_mozc.py` require VS2022 (and higher) (f6f1c30c7)
- gyp: Add conversion_request to engine_builder dependencies to fix build errors (a27a9c24d)
- Refactor CodeGenByteArrayStream, use char array instead of string literal (de44ac850)
- Add Utf8Chars and Utf8Chars32 iterators, new UTF-8 encoder and decoder (56cd67fe8)
- Let ConversionRequest be trivially copyable/destructible, inline accessors. (6d1dcee07)
- freelist: Delay object constructions until actually needed (990c53088)
- Switch to Visual Studio 2022 for Windows builds (878915a3b)
- Bug fix: Store preprocessed entry (8a295232e)
- Use unconditional noexcept for simplicity (d3ac823dc)
- Change SegmentsForLearning to struct, remove empty virtual destructors. (e897802e7)
- Change absl::btree_set to to absl::flat_hash_set as order is irrelevant, cleanup (9c8db3204)
- Move Result comparators to the header file. Remove ValueCmp as utf-8 strings can be compared in dictionary order by operator<. (0db42b3cc)
- Added rule-based spellchecker. This is an experimental spellchecker based on string-to-string replacement. We will investigate the spellchecker's quality (e.g., CTR/CT) when the corrections are highly confident enough. (057adb8c8)
- Clean up the feature flag for `use_actual_converter_for_realtime_conversion`. (a39bd9c34)
- Switch from gcc to clang to use decltype (#758) (2030eb4a9)
- Use absl::flat_hash_map for OnMemoryFileMap, Refactor ConfigFileStream (5384c8cf9)
- Migrates uses of associative containers to more performant types. (7bbbe337d)
- Preserve the key expansion penalty in N-gram rescoring. (1af2663cf)
- Add a flag to limit the number of candidates to show. (b923c39bd)
- Fix 2 IncludeCleaner findings: * Included header "third_party/absl/algorithm/container.h" is not used directly * Included header "third_party/absl/strings/str_cat.h" is not used directly (db0c4769d)
- Simplify `installer_*.wxs` a bit for Windows (ad89a8766)
- Use the actual DLL name for binary ID name (6abbd8db0)
- Fix build break caused by cl/538711643 (e408fe25d)
- Add more control parameters for N-gram rescoring. (4ac4b2168)
- Cleanup; remove redundant c_str(), use absl::StrAppendFormat and StreamFormat, remove extra string copies. (2af5eb3b7)
- Migrates uses of associative containers to more performant types. (06b3da938)
- Migrates uses of associative containers to more performant types. (a13d56d89)
- Migrates uses of associative containers to more performant types. (501bb74cc)
- Migrates uses of associative containers to more performant types. (8ee8669ab)
- Migrates uses of associative containers to more performant types. (28fd64032)
- Fix 2 IncludeCleaner findings: * Included header "third_party/absl/strings/str_split.h" is not used directly (2 times) (a6d61d2bc)
- Included header "third_party/absl/algorithm/container.h" is not used directly (4dacdd808)
- Included header "third_party/absl/flags/flag.h" is not used directly (e23c834f0)
- Change std::map to absl::flat_hash_map, use absl ascii_isxxx and StrAppend. (60aee5834)
- Omit `_ja_` infix from TIP filenames (9fb39d5f2)
- Included header "third_party/absl/random/distributions.h" is not used directly (864d82d58)
- Fix 4 IncludeCleaner findings: * Included header "third_party/absl/algorithm/container.h" is not used directly * Included header "third_party/absl/random/random.h" is not used directly * Included header "third_party/absl/strings/str_join.h" is not used directly * Included header "third_party/absl/strings/str_split.h" is not used directly (88cfe7828)
- Included header "third_party/absl/flags/flag.h" is not used directly (2debef316)
- Included header "third_party/absl/strings/match.h" is not used directly (58af303f2)
- Assume Qt is available when building the installer for Windows (62b8d9fab)
- SuppressionDictionary: avoid string constructions and separate table to key/value/both (4ca446554)
- Use unescaped values for ibus_mozc output. (5ca52be64)
- Stop setting `/ALLOWBIND:NO` and `/RELEASE` bits with `editbin.exe` (d56492af6)
- Add the `--build_tag_filters` option to .bazelrc (5ceb7a62c)
- Included header "third_party/absl/flags/flag.h" is not used directly (0cc0a1d88)
- Speed up `build_qt.py` (#722) (d0b810346)
- Add missing test entries for sort result (f85b87c46)
- Remove `--pdbpath` option from `postbuilds_win.py` (ab1ae0f20)
- Added Alignment function of Japanese transliterator. Aliment function allows to extract per-character conversion rules. (f7b03c855)
- Use MOZC_LOG_PROTOBUF to log a protobuf. (b07106573)
- Inline `custom_action.gypi` (6351222e8)
- Remove unnecessary ref to `<(mozc_ca32_path)` (#755) (fb983dbd7)
- Move macOS design docs to docs/design_doc/ (19e6e2f37)
- Remove suffix "64" from the filename of 64-bit custom action DLL (aa3b42479)
- Stop building 32-bit custom action DLL (3f75297ce)
- Added rulebased language model. (297eb2ea1)
- Add 空集合(くうしゅうごう) to the dictionary. (2e3a44544)
- Replace the remaining ref to `UnregisterTIP32` (#755) (2907a9033)
- Make PosGroup copyable and annotate it with ABSL_ATTRIBUTE_LIFETIME_BOUND. (0151273ac)
- Remove dependency on 32-bit custom action DLL (470a97433)
- Stop redundant invocation of `RegisterTIP` custom action (#755) (9e11c60dd)
- Update `credits_en.html` (#754) (e3f6b5a53)
- Inline `wix.gypi` (#752) (3d73affeb)
- Test against 64-bit binaries on Windows (#753) (526313408)
- Add `/bigobj` compiler option for MSVC (#753) (367c7aa14)
- Add N-gram rescorer. (0af837caf)
- Add a rescoring extension point to the dictionary predictor. (ac5913fcf)
- Stop building 32-bit installer for Windows (dfd09b6ae)
- Set the data tag for Canary as "canary". (bdd4d8733)
- Automated visibility attribute cleanup. (e6c172cd2)
- Stop uploading `Mozc32.msi` (#752) (5e92aa9b2)
- Update the ios/ path. (af4ce8f46)
- Display log of candidates in converter_main. (83446f930)
- Added flag to enable 'move_literal_candidate_to_top'. When this flag is enabled, the literal candidate is always placed at top when typing correction is triggered. (10f7fc160)
- Fix compilation error in Linux (5818a11df)
- Fix warning messages in GitHub Actions for Win (c81712f7e)
- Cleanup: use string_view, pass pos_matcher by value, move strings, avoid repetitive string appends. (70538bac3)
- Add missing include files for size_t and std::swap (3df82ca16)
- Cleanup: replace memcpy and memset with type-safe alternatives (a80bb9e55)
- Add 最頻値(さいひんち) to the dictionary. (45f667774)
- Fix comment typos in `{macos,windows}.yaml` (#749) (395ebe3b3)
- Fixes issue that UNDO button doesn't work properly after committing bracket pair. (c2a0f009c)
- Cleanup: use constexpr string_view for string constants, move strings (2a99f0c94)
- version_rewriter: refactor, embed VersionDataImpl into VersionRewriter (4945e14e5)
- Clean up the use of swap, use ADL by using std::swap. Add member swap() where appropriate. (a0ba96df0)
- Enable GitHub cache action for mac/win (#749) (e8d211e9f)
- Add file name accessor to the data manager. (e7cb5c1f2)
- Support local cache in `updade_deps.py` (8233b4067)
- Use default member initialization for prediction::Result. (e96e99b8b)
- Make prediction::Result printable by AbslStringify(). (f7de47522)
- Let the data manager load an N-gram model if present. (2c3c2ce9d)
- Refactor: Split `ExistenceFilter` into immutable view and mutable builder (72d9a1165)
- lattice: Change GetCommon not to create copies of the strings (ac210179e)
- Automated visibility attribute cleanup. (285bc07f1)
- Fix #748: Enable IPC peer check for ARM devices again (03832fced)
- Make DecoderExperimentParams configurable in converter_main. (335653a9a)
- Make `IPCTest` deterministic (77d4643ba)
- Fix #747: Quick fix for `ipc_test` in Linux (31540229f)
- Rename `IPC_REQUESTSIZE` to `IPC_INITIAL_READ_BUFFER_SIZE` (8576dca4c)
- Deprecate `IPC_REQUESTSIZE` (6bda3a04a)
- Support large IPC payload in Windows (9acf4674a)
- Update entries for 粟 (a552b9c2c)
- Update entries of dictionary_oss/reading_correction.tsv (1c920dab1)
- Add an evaluation case of こういんしょう → 好印象 (ed746c13d)
- Update build_mozc_in_docker.md (#746) (eb8f5dfc2)
- Remove unused mozc_py_library targets. (ac1daeb35)
- Remove unused `android_ipc.cc` (66ce0ee0c)
- Remove unused `IPCServer::{request,response}_` (3418f68e9)
- Fix a build error of mozc_engine_test.cc (f4eb41d81)
- Make `ipc_test` more deterministic (6da3e29fb)
- Automated g4 rollback of changelist 534035024. (3e680f962)
- Add the extra_data to mozc.data. (f7cd59af2)
- Add return by value overloads to mozc::japanese conversion functions. (1c121adb3)
- Refactor ClientMock with gmock (428e72480)
- Add ^ to the keys for ∧ (2891e45a0)
- Update the visibilities. (ce96ad94c)
- Remove flaky tests. probable_key_event can be empty. (27b44566f)
- Refactor; Pass Connector by value / reference (5c37edb58)
- Support larger alignment size. (9bf43431f)
- Add MakeTempDirectoryOrDie, Let ScopedTempUserProfileDirectory use it (7e8feba61)
- ClientFactory: return std::unique_ptr instead of raw pointer (04dc198f4)
- Remove duplicated white spaces. (312adadc5)
- Fix improper use of std::forward. (016c46020)
- Optimize and refactor `SerializedStringArray` (0f8c0a103)
- LruStorage: Move small accessors to the header file, make it movable (65b49a875)
- Use implicit call of AbslStringify() by protobuf, except for the Windows build. (205f05a03)
- Add 靑 to single_kanji.tsv and updated the description. (048792032)
- Update the trunk version to 2.29. (9a2f53ad3)
- Add a description for 瓣 as 旧字体 of 弁. (d6491aeae)
- Add unix/ibus/key_translator.cc to the LINT.ThenChange rule again. (ce73df16e)
- Add evaluation test cases. (65da90cac)
- Add BUILD for custom_action.dll to build it with Bazel (1b9820cb4)
- Fix build errors after cl/533343353 (c4185cd20)
- Make `BitArray` and `Trie` copyable and movable (07ca3f571)
- Create a GYP rule for absl_hash_testing. (841dde764)
- Introduced configurable parameters to control the ranking and positions of type corrected candidates. (36e4325dc)
- Move ClientFactory to client.h as it's implemented in client.cc (7f50fe952)
- Refactor ipc; pass unique_ptr with ownership, use unique_process_handle, add a fixture for renderer_client_test. (ff75eb259)
- Clean up `mozc_undo_partial_commit` flag (408197324)
- Update BUILD_OSS to 5105. (d50b3d59f)
- Add a check if NSEvent is NSNull or not. (1d19e7a10)
- Refactor number_util, use string_view and span (4e885f7f4)
- Refactor: make FreeList and ObjectPool movable, use unique_ptr in FreeList instead of raw pointers. (a4fcba086)
- Refactor with LoadUnaligned/StoreUnaligned and remove dependency to absl/base/internal/endian.h (d48df5d0b)
- Add Endian, HostToNet, NetToHost, HostToLittle, LittleToHost (1ac3bf88f)
- Automatic clean-up of unused code. (492ac1bc7)
- Fix overlay (#744) (381e5c332)
- Enable the candidate window to show on a secondary and later display. (3a47795f8)
- Update pull_request_template.md to ask checking CONTRIBUTING.md (bcb5f5518)
- Refactor SessionList, remove object pool for Candidate (7ea860f0c)
- Allow to deploy the zip model file that does not include spellchecker model. (dbbb3df78)
- Make number decoder result NO_SUGGEST_LEARNING. (5dfd07f71)
- Add word entries reported from GitHub issues. (8646bf990)
- Add place names of Hokkaido reported reported from GitHub issues. (6e2edec32)
- Add src/bazel to the directories that we accept PRs. (cdcb04a6c)
- Move files for Bazel to the bazel/ directory. (ca69af2d6)
- Update files for bazel. (b68e7e5b9)
- Remove "-- -session:session_watch_dog_test" and run all tests on GitHub Actions for macOS. (a847b0da3)
- Add bits.h and add byteswap, LoadUnaligned, and StoreUnaligned functions. (6816c8149)
- Use local_repository for googletest instead of new_local_repository. (a2416f52b)
- Update third_party/abseil-cpp to 20230125.3 (ec697dda8)
- Update third_party/protobuf to v3.22.5 (3015c0653)
- Automated g4 rollback of changelist 531506258. (5eb82f74a)
- Fix unit tests for macOS OSS version (6355cb051)
- Add "manual" to mozc_objc_test.macos_unit_test. (e85d8cbc0)
- Fix 1 ClangTidyReadability findings: * redundant string conversion (efa18ab7a)
- Fix 1 ClangTidyReadability findings: * redundant string conversion (e5d3a217e)
- Fix 1 ClangTidyReadability findings: * redundant string conversion (01421b72c)
- Fix 1 ClangTidyReadability findings: * redundant string conversion (4368ea5a8)
- Inline small accessors / one-line functions, make Segment and Segments movable (2a38c1530)
- Change set -> flat_hash_set and const string& to string_view (ca55d5ca3)
- - Populates keyboad layout from client to composition spellchecker to make layout-aware correction - Suppress the descriptions if the correction is kana-modifier-insensitive. (b5aa93fd3)
- Check if event of handleEvent:client: is nullptr or not. (9b0019d84)
- Include cstdint explicitly for uint32_t. (8dbe1ff97)
- Take string_view instead of const string&, embed InternalData to Key (497c0899f)
- Fix 2 IncludeCleaner findings: * Included header "third_party/absl/strings/str_cat.h" is not used directly * Included header "third_party/absl/strings/string_view.h" is not used directly (595eb29cf)
- Add noandroid tags to tests that don't pass on Android. Delete separate android test targets. Internal cleanup. (9f36155e6)
- Calls the new composition spellchecker in the dictionary predictor. (7f19a3c0c)
- Replace own implementation with absl::rotl (1df8fa59e)
- Reorganize japanse_util and its internal dependencies (f7bd7d2f7)
- Remove deprecated and unused _lib targets (82c229993)
- Remove noop constructor/destructors, make empty constructors = default (7c4e64daa)
- Refactor: replace INSERT_FEATURE and FETCH_FEATURE macros with functions (b88346e89)
- Add tags to limit presubmit builds to Android, Add METADATA file for Builder and Cider to use the android_arm64_v8a config (b1acebfff)
- Bump the minimum macOS version to 10.13. (6a2f5950b)
- Add predefined special keys. (e506bed7c)
- Use DLOG instead of LOG. (76d3b29c8)
- Add logics for key input with KeyEvent::AS_IS. (4fa90d2be)
- Migrate from ScopedHandle and WRL to WIL (a005be52b)
- Fix build error in clang where sizeof(HKEY) != sizeof(int) (b184083cf)
- Refactor the tests with test suites, write Unicode strings directly as we no longer support VC++ 2008. (e149d39b5)
- Refactor imm_reconvert_string (387ff08c7)
- Refactor; take string_view for ctor and LockAndWrite, use wil::unique_hfile (64ffb4bf1)
- Change SystemEqualString to take std::wstring_view and ignore nul characters (2b4ad9aec)
- Remove explicit constructors as old VC++ workarounds (1f6f8858b)
- Add platform tags to BUILD targets (build for Windows only). (de2ad537d)
- Enable to run Bazel with empty ANDROID_NDK_HOME. (684bbce45)
- LSC: Add `load()` statements for Python rules. (48ec9bd5d)
- Update third_party/protobuf to v3.22.4 (0ae426387)
- Exclude android for SpawnProcess. Sort includes. (8067b0502)
- Update the visibility for android/jni:mozcjni (33887d3a3)
- Update the GYP rules of Protobuf to update the version to 3.22.4. (4d3c99262)
- Update the version of rules_android_ndk and build options. (cd90e139b)
- Update rule names for Android build. (232d47845)
- Integrated new composition spellchecker into Mozc. (539be4d08)
- Make KeyCorrector non-virtual final and movable. Move small constructors to the header file. (68c0e481c)
- Exclude codegen_bytearray_stream from android builds (bd1416d60)
- Move unit_main_objc to closer to the end of the build file as gunit_main is the primary target. Add "avoid_deps" tag for build_cleaner. (5e07fdcad)
- Automated visibility attribute cleanup. (4d1ee3352)
- Automated visibility attribute cleanup. (4dd043598)
- Cleanup; make StatsConfigUtilInterface non-movable or copyable so derived classes inherit that. (51d6425d8)
- Remove redundant const in function declarations, remove empty constructors (930aff93e)
- Fix tests for win32_renderer_util: error: C++ exception with description "bad_optional_access" thrown in the test body. (2e34ec38b)
- Add direct-initializing HResultOk<T>(), cleanup (f980e5789)
- Merge InternalState into TipThreadContext (1d52a3e48)
- Refactor: Win32 Deleter (0ff78c5e8)
- Cleanup: Replace Optional with std::optional, pass std::unique_ptr and use make_unique, remove noop destructors (8f408466b)
- Cleanup; move default variables into header files, remove empty destructors (1fa1589bd)
- Remove and replace Util::StringReplace with absl::StringReplaceAll (853a9bc56)
- Add HResult::Succeeded() and HResultOr<T>::error() and has_value() (83ea6bc11)
- Cleanup: remove empty destructors, = default empty constructors, reorder declarations (b6e977bf8)
- Refactor: use unique_ptr to store UndoCommand, move UndoCommand definition to the header file (a1c59b969)
- Make TipInputNodeManager movable to embed directly into TipThreadContext (0cd9122fb)
- Explicitly call unique_variant::reset_and_addressof() when getting a varian as &data is ambiguous. (ebb399bf2)
- Clean up includes, use constexpr to define constants (1e3def375)
- Fix UpdatePreeditAndComposition where it returned `E_FAIL` when `!output.has_result() && !composition` (b194ede80)
- TipCompartmentUtil: Return HResult instead of HRESULT to prevent accidental casts from HRESULT to bool (d98164507)
- Fix a bug where TipCompartmentUtil::Get() never returns a stored value (5130cce72)
- Fix a bug where ProcessWatchDog doesn't create an event in Windows (db8f04aa3)
- Use inline constexpr for constants in header file to avoid ODR violations (e1d8c7702)
- TipLangBarToggle Button: Explicitly cast `this` in `QueryInterface` (6e680a0ca)
- Add [[nodiscard]], error() and operator <<() to HResultOr<T> (471e72cdd)
- HResult redesign: disallow dangerous conversions, add ToString() and operator <<() (b57d10bbe)
- Split hresult.h and hresultor.h as a preparation to extend HResult (adea0f08e)
- Fix a bug in `EnsurePrivateContextExists` where it never registers the `context` (09f6ed710)
- Migrate to WIL from ATL/WRL, refactor LangBar (17ef6df13)
- Update Com{PtrMake,Query,Copy} to use WIL (760193275)
- Migrate from ATL/WRL to wil::com_ptr_nothrow (c13b178b7)
- Migrate from ATL/WRL to wil::com_ptr_nothrow (0e9861730)
- Partially revert cl/528158034, add back ComCopy (6fd3cc442)
- Replace ATL/WRL with WIL (4e4bd62e0)
- Update rules of GYP to build protobuf. (57d185681)
- Update the Xcode version and the mac_sdk version. (7461faa6c)
- Revise the section about why there is a limitation of PRs (6fa16c406)
- Remove the `btree` dependency from `environmental_filter_rewriter.*` (003969ce7)
- Rename macro internal variable name to avoid name conflict (f8abce700)
- lru_storage: const std::string & -> absl::string_view for keys, return std::unique_ptr from Create(). (bea9b79ac)
- Add `operator==` for VC++ 2017 debug CRT (f3edd5ef5)
- Use absl::StrJoin to join strings with tabs (c8379bb26)
- std::map -> absl::flat_hash_map, use constexpr to define constants (0ed5a1479)
- Fix assertion errors in `std::set_intersection` (bbb07fdb5)
- Use absl::flat_hash_{map,set}, clean up = default destructors (e402e2a1f)
- Explain how the target CPU architecture is determined for macOS build (c34201d59)
- Rename internal macro (3862fa59a)
- ipc: refactor with WIL, migrate to absl::flat_hash_map (b96c8d55a)
- Add WIN_ONLY and platfom constraints to hresultor_internal (12e5e749a)
- Use Acquire/Release semantics for reference counter, add safety checks, refactor tests (c13a5b1f6)
- Update the section of the GYP build. (106335836)
- Build Qt from the source code by default for macOS build (d89814ec1)
- HResultOr<T>: use a custom base class instead of std::optional (d4dc32756)
- Change the semantics of `HResult<T>` to the same as `absl::StatusOr<T>` (29f387fb2)
- Update Bazel Skylib to 1.4.1. (953591d01)
- Reorder the modules in WORKSPACE.bazel. (e22e20174)
- Stop swallowing build messages in `build_qt.py` (2975edbce)
- Migrate from ATL/WRL to WIL, use MakeComPtr to create COM objects (32a8db5df)
- Use absl::flat_hash_map instead of std::map and absl::btree_map (6738394a2)
- Include absl/random/random.h in key_event_handler_test.cc (63f81dde6)
- Make sure to initialize `ComImplements::ref_count_` (37e9f1f6e)
- Fix WiX scheme validation error (88f84f73d)
- Remove unused `TsfRegistrar::{Get,Set}ProfileEnabled` (7768f86f2)
- Limit supported types in `ComQuery` for now (3ad605e8b)
- Delete `TsfRegistrar::{Register,Unregister}COMServer()` (e4679076b)
- Update rules of Abseil the GYP build. (99d08ae13)
- Add state_proto to build rules. (d81b2f133)
- Fix the name of prelauncher registry name (50f38d754)
- Stop exporting `DllRegisterServer` and `DllUnregisterServer` (4e1219125)
- Fix #736: Enable Mozc TIP Profile during the initial installation (ea80aea9c)
- Add TargetIs... constexpr functions to refactor platform-specific code (622dd1964)
- Fix test error in ComTest. (7e12b3605)
- Stop learning the trailing space from alphanumeric input. (8ba617bf2)
- Update collocation.txt based on the GitHub issues. (ca75f3d87)
- Add test cases based on the GitHub issues. (d23536be6)
- Rename Utf8ToCodepoints and CodepointsToUtf8 to Utf8ToUtf32 and Utf32ToUtf8 respectively. (a7413da8d)
- Refactor with the new COM helpers and WIL (3e4b08bff)
- Fixes crash bug when sending bracket pair key event multiple times. (2a84a8601)
- Replace genrule with run_binary, remove unused Python library targets (f0b92fa55)
- Add license credit for Windows Implementation Library (0a6f03f1f)
- Use ComImplements and wil::com_ptr in com_test (0c064efdf)
- Add MakeUniqueBSTR as a wrapper for wil::unique_bstr. (434e25b35)
- Remove ComRawPtr<T>() and use wil::com_raw_ptr<T>() (fdf0a4960)
- Use absl::flat_hash_{set,map} as set/map. (3abffd4b6)
- Use std::u32string to store a sequence of codepoints. (cdf75079b)
- Use `ComImplements` to TIP COM interfaces, remove `TipRefCount` (c7f8edc07)
- Allow customizations of ComImplements with overrides and traits (062d2191a)
- ComImplements: disallow copies and moves (57a48dde5)
- Add `--build_tests_only` to `bazel test` (f3a8cf4e1)
- Add src/unix/ibus/ to the paths that we accept pull requests. (f133df0fd)
- Fix the syntax error in linux.yaml. (d452b5fb8)
- Update BUILD_OSS to 5085. (4df261a9e)
- Include what you use, use = default for default constructors and destructors (6d1a429df)
- Treat the same version installation as upgrading (47a4da76b)
- Stop relying on `mozc_version_template.wxi` (f85b1b16c)
- Fix TIP filename in 32-bit installer (be6bcce2e)
- Delete unused `ime_switcher.*` (dfa6b5df9)
- Remove unused `migration_util.*` (23f9adb3f)
- Cleanup; include what you use, use = default (f56ff7100)
- Add ComImplements as a base class for COM implementations (2d4b215c2)
- Include what you use, use = default for default constructors and destructors (8871894d0)
- Use constexpr for compile-time constants (9e164fef3)
- Add missing deps to `prelauncher.cc` (4e7d75f4d)
- Move common logic to pos_matcher.h from py (793956ba4)
- Use constexpr for compile-time constants (1f09582a5)
- Include absl/log/check.h (6d7de35f3)
- Remove unused `gui/set_default_dialog/` (afc457518)
- Migrate the ibus location. (4cd976448)
- Cleanup; Include what you use (bbbafee27)
- Register qt Skylark macros for build_cleaner to use build_cleaner with Qt build targets (d23f5df2d)
- Remove the Ibus build from build_mozc.py. (59cdfc191)
- Refactor PosIdPrinter: Use absl::flat_hash_map, pass id_def by value, allow moves. (cde233966)
- Remove unused MemoryStorage class (follow up to cl/527056582) (95c9860ec)
- Remove compiler_specific.h (5d295fd6a)
- Fix the condition to aggregate single kanji prediction results. Single kanji results should be aggregated only when mixed_conversion() is true. (4b0dee5bd)
- Fix compile error for Windows (59283b584)
- Use [[maybe_unused]] for unused fields instead of disabling a compiler warning (9ad97c50e)
- Change std::map to absl::flat_hash_map (b7e76583b)
- Automated g4 rollback of changelist 525629097. (39a26090c)
- Cleanup; Include what you use, modernize with = default (f89f1ebdc)
- Refactor ExistenceFilter to return results by value (3d54c5af6)
- Cleanup; no longer need to suppress compiler warnings (c964b1d78)
- Change kPosMap to constexpr, update ifdef guard, remove shebang (cd75f3ad1)
- Remove deprecated macros with the _mozc prefix; Use mozc_ instead. (4fd3b0bcb)
- Run more tests in macOS GitHub Actions workflow (c04a115f9)
- Run build and tests in parallel for linux/mac workflows (035a4039e)
- Add StrCatW and StrAppendW for wide character strings (5e8b91001)
- Mention GitHub actions in mac/win build instructions (63e12e3a1)
- Fix #730: Upload artifacts from GitHub Actions (bb50663d5)
- Remove deprecated macros with _mozc suffix; Use mozc_ prefix instead (dcd42995f)
- Adding a disclaimer to `README.md` (d85631565)
- Remove special condition to trigger GitHub Actions (4c85ed6d0)
- Clean up build instructions for Windows (272747f82)
- Fix improper use of std::forward<T>() in the Random constructor (f15618767)
- Skip adding probable keys from the first composition event. (272612fc7)
- Add Bazel workspace and build definition for WIL (96fb9b1e6)
- Add WIL configurations to the gyp build script (426ac5ec5)
- Add Windows Implementation Library (WIL) submodule (#727) (0ce1f9b78)
- Remove unused deps from `tip_core` GYP target (250d159e7)
- Fix #728: Support building installers for Windows (c7265ec50)
- Fix #729: Avoid redundant CI executions for forked repositories (3b3d3bcfa)
- Make `build_qt.py` compatible with Python 3.9 (90d397684)
- Fix the remaining error in `update_deps.py` for macOS (801230e78)
- Set up VC envs when running `postbuilds_win.py` in `build_qt.py` (a6653c5e4)
- Fix build failure in `omaha_util.cc` (a95799696)
- Import WTL 10.0.10320 with Chromium patch (#725) (7925e776f)
- Update BUILD_OSS to 5080. (0696b153e)
- Fix a typo in the comment header of `build_qt.py` (5ea788332)
- Automated g4 rollback of changelist 525611256. (27bdf62e5)
- Add AbslStringify to use zstring_view with absl string functions. (02c5af98f)
- Change absl::string_view to zstring_view to eliminate the temporary std::string object. (2ab239adc)
- Fix several issues in `update_deps.py` (a67b4b9db)
- Add `build_qt.py` for OSS Mozc (baf418832)
- Add `update_deps.py` for OSS Mozc (6efc6490d)
- Remove extra std::string::c_str(), use win32/wide_char.h (instead of Util). (e8fd9e291)
- Assume Windows 10+ in `text_renderer.cc` (6a6591114)
- Extract out `CaseAwareAbsPath` (ab3c9e42b)
- Move constructors / destructors to the top of the class, use = default (9d16bce9c)
- Use const std::string & as filename in Input/OutputFileStream (ae3448099)
- Inline `TipUiHandler::CreateUI` (faed7e193)
- Add const lvalue ref overloads for to_pfstring and to_string (b6c6cfdb1)
- Fix a bug where zstring_view was incorrectly convertible to std::string_view (should be absl::string_view). (48c1fcf64)
- Remove no-op `TipUiHandler::OnDestroyElement` (0464b0607)
- Migrate //unix/ibux:selection_monitor to mozc::Thread2. (ebdefb356)
- Migrate to `absl::flat_hash_map` in `tip_text_service.cc` (2d38e8716)
- Stop using linked text in `pull_request_template.md` (35bc303cc)
- Use `*.postbuild` file as a trigger to rebuild `*.msi` files (505c1bf8d)
- Stop using merge-module to redistribute VC runtime (c2d040c28)
- Build `mozc_custom_action{32,64}` for OSS Mozc as well (4397a038f)
- Add build rule for `omaha_util.cc` for OSS Mozc (222e1af6b)
- Inline `mozc_broker.gypi` (fe4b6b0db)
- Add missing tests to `win32_base_all_test` (6733ff556)
- Support paths that contain space in `--wix_dir=` (f6b79b1d6)
- Include `mozc_installers_win` to `package` meta target (8a87393ae)
- Correct `kMozcTIP32` and `kMozcTIP64`. (ddcee48c8)
- Simplify `TipTextServiceImpl::RemovePrivateContextIfExists` (1fd57f36f)
- Assume `TipTextService::IsImmersiveUI()` is always `false` (0a0de694c)
- Bump minimum Windows Installer version to 5.0 (0ee447e2f)
- Rename PlatformStringView to zpfstring_view, add pfchar and pfstring (e28e8365d)
- Migrate ATL::ComPtr to WRL::ComPtr, pass unique_ptr instead of raw pointer (7863f7146)
- Avoid access violation in `TipTextServiceImpl::RemovePrivateContextIfExists` (551ac0763)
- Add MakeComPtr (make_unique for ComPtr), move ComRawPtr outside of internal namespace (ec5ab6bf3)
- Remove constexpr from HResultOr::swap to fix build failures. (1157fe618)
- mozc: Delete unused timezone_offset. (dc73474b1)
- Migrate ATL::CComPtr to WRL::ComPtr, refactor (3ab9b7508)
- Add ComQueryHR that returns HResultOr<ComPtr>> (7d1512f9c)
- Add ASSIGN_OR_RETURN_HRESULT and RETURN_IF_FAILED_HRESULT macros and HResult class. (8bfd36613)
- Add value_or to HResultOr<T>. (e6e2603c3)
- Remove unnecessary header. (49011bff9)
- Add COM helper functions: ComCreateInstance, ComQuery, ComCopy (068e68f2b)
- Make the small cost encoding condition conservative. (fc42b9934)
- Update BUILD.bazel (fa4cdd042)
- This is a revert of 590e7185cb72adee732e03a61f99abddd657ddd3 with manual conflict resolution (ad69b227d)
- Require Windows 10+ to install and run Mozc (98bc193f5)
- Normalize current working directory in `build_mozc.py` on Windows (de0c78c86)
- Changed Command.output from `required` to `optional`. (3dd781374)
- Update our `pull_request_template.md` (b370e8d5d)
- Add HResultOr<T> for Windows COM. (1a703db45)
- Move pull request template to `.github/pull_request_template.md` (b47aeb023)
- Refactor cache_service_manager (185f372dd)
- Support move construction for LoudsTrieBuilder. (4bb45f940)
- Migrate ATL::CComPtr to WRL::ComPtr; refactor (72c4a4ee9)
- Migrate ATL::CComPtr to WRL::ComPtr; refactor (c97114cd5)
- Refactor tip_input_mode_manager; merge InternalState into TipInputModeManager (6153a5ce6)
- Rename `GoogleIMEJaBroker{32,64}.exe` to `GoogleIMEJaBroker.exe` (4241a5179)
- Run `postbuild.py` for 64-bit cache_service/converter/renderer (ffa7a2b7e)
- LSC: Add `load()` statements for Bazel-builtin Python rules/providers. (cb8ebd48d)
- Automatic clean-up of unused code by go/sensenmann. (b4368ab86)
- Migrate ATL::CComPtr to WRL::ComPtr; refactor (c99e7ddf3)
- NULL -> nullptr, delete private constructor, clean up includes (0f5ef6569)
- tip_{class_factory, ui_handler}: Migrate ATL::CComPtr to WRL::ComPtr (24e53453c)
- Refactor imm_util, tsf_registrar, uninstall_helper (5e518d85f)
- Refactor tip_candidate_list (05ac954be)
- Also use Visual Studio 2022 on Windows CI (c34fd2962)
- Use Visual Studio 2022 Community Edition for build instruction (077f0c237)
- Add BUILD files for win32/tip (4866fdb44)
- Officially support Visual Studio 2022 in `build_mozc.py` (90dcebbfe)
- Change the arguments of Engine::Init. (0ef436fb5)
- Refactoring of SessionServer. (1d3ff5213)
- Remove jsoncpp from .gitmodules. (0f0889360)
- Remove IE specific elevation policy support (6bb00af72)
- Change include paths to relative paths from google3 to support Bazel. (a2c2f4033)
- Add "keep_dep" tag to win32 library targets (3e33ccc3b)
- Move `server/*cache_service*` to `win32/cache_service/` (c700dd570)
- Stop installing `GoogleIMEJaBroker32.exe` into 64-bit environment (858636355)
- Fix #712: `nullptr` access in `tip_edit_session_impl.cc` (497a6ae6f)
- Introduce `.clang-format` (dca648257)
- Add `/.vs/` to `.gitignore` (52cb89ebe)
- - Limit the maximum number of Typing Correction results for the same TC query - Apply predictive cost penalty to Bigram and TypingCorrection entries. (65d8d67a8)
- Install 64-bit cache_service/converter/renderer for 64-bit Windows (cc4e161ae)
- Add `.vscode/` to `.gitignore` (0f0f860ac)
- Use `%USERPROFILE%\source\repos` as the repository root for Windows (b5600b8eb)
- Use VS2019 for build instructions (aacb4c97b)
- Run `build` and `runtests` in parallel for Windows CI (3324df1d5)
- Simplify `WindowPositionEmulator` a bit (3608f8fa3)
- Remove unused `GetWindowClassName()` (775106b8b)
- Assume `initialized() == has_exclude_region()` (f9cd87a5f)
- Split DLL main entry point and routines to mozc_tip_main.cc (25692df7f)
- Migrate to WRL::ComPtr and add final to implementation classes (b861ff249)
- Merge `CandidateWindowLayout::has_exclude_region_` into `initialized_` (7a202d7f7)
- Move WM_MOZC_IMMERSIVE_WINDOW_UPDATE to tip_ui_renderer_immersive.h to avoid cyclic dependency. (e254877d2)
- Mark COM implementation classes final (6dbc12ad6)
- Include what you use (df2fa645c)
- Use constexpr to declare constants, use {} to default initialize struct fields (c3460146a)
- Compare with the same enum type for TipInputModeManager::Action (f56d9fe2f)
- Remove unused `CandidateWindowLayout::InitializeWithPosition()` (761c86e62)
- Change static DCHECKs to static_assert, use constexpr to define constants (5a3766201)
- Make `GetWorkingAreaFromPoint()` a flat function (7209a0259)
- Assume `LayoutManager::GetDefaultGuiFont()` is no longer used (1bd5ae946)
- Remove `LayoutManager::GetCompatibilityMode()`, which is unused (8aaded7fa)
- Unify `LayoutManager::LayoutCandidateWindowFor*()` (1e9a3bc7c)
- Remove unused params from `LayoutCandidateWindowByCompositionTarget` (6d0797118)
- Update BUILD_OSS to 5065. (d16b263af)
- Assume `default_gui_font` is always empty (dc0976e98)
- Update data/dictionary_oss (815305ba2)
- Assume `composition_font` is always empty (81625a5af)
- Assume `composition_form_topleft` is always empty (09095c0ac)
- Set `VSLANG=1033` for Windows GYP build (64d2c2860)
- Refactor `build_mozc.py` a bit (be61d41fc)
- Add 圃場(ほじょう) to evaluations. (debb828e6)
- LSC: Add heterogeneous lookup to std::string-keyed ordered containers. (0285f3dca)
- Let Mozc IPC rely on `PIPE_REJECT_REMOTE_CLIENTS` (9a3401459)
- Fix 3 ClangTidyBuild findings: * missing #include <iterator> for 'std::size' * missing #include <utility> for 'std::swap' (08b16e935)
- Stop promoting TC entries when the query cost is negative in use_typing_correction_diff_cost. (2e4c2ea55)
- Add a feature to cancel suffix penalty for content node. (bf965814c)
- Run also `runtests` in CI for Windows (25435fc75)
- Reduce console messages from `build_mozc.py gyp` (cb779d544)
- Assume `composition_form_topleft` is always empty (13164e784)
- Fix a build failure for the OSS version. (419cd9872)
- Remove the unused method. (b39b2d4a9)
- Migrate Mmap::Open() to Map(). (e73ed7db8)
- Fix the format specifier on Windows. (3e770b6ef)
- Update the document and workflow as the net/ directory was removed. (a41d0677d)
- Support partial mmap. (1f90ce56a)
- Set prefix penalty when the converter returns the dummy candidate. (255f4f4d8)
- Remove third_party/jsoncpp. (64e256086)
- Update the Abseil version to 20230125.2 (37371d089)
- Fix OOS GYP build (79858489c)
- Update Linux CI config to reflect the removal of `src/net` (23afdb864)
- Add 圃場(ほじょう) (#703) (9c5e909ff)
- Enrich the CL description for auto submitted data packages from the periodical generation pipeline (249ed6a45)
- This is a partial rollback of changelist 520936906. (2fb10f7fc)
- Format; internal change (1cfc76972)
- Refactor; include complete class declarations in header files, iwyu (00e0c2360)
- Remove unused IMM32 stuff from `renderer_command.proto` (6f475eb7c)
- Delete unused `win32_font_util` (17d4d415c)
- Assume `ApplicationInfo::composition_font` is always `null` (f4a8bdf9c)
- Assume `ApplicationInfo::candidate_form` is always `null` (8abb04b0a)
- Assume `ApplicationInfo::composition_form` is always `null` (ddff4442f)
- Mozc no longer depends on `JsonCpp` (558b07953)
- Use `glob` in protobuf/protobuf.gyp (5fded8578)
- Use `*.textproto` instead of `*.json` for `win32_image_util_test` (9df5f5744)
- Prepare for `*.textproto` file (86581b020)
- Style cleanup of `win32_image_util_test.cc` (82322b572)
- Introduce `data/test/renderer/win32/test_data.gyp` (47d79739b)
- - Support deploying the mozc.data from the given path. - Use the tag number defined in the gen_data_version library (8b5012383)
- Fix the internal version. (5713fc9c6)
- Delete unused `WorkingAreaFactory::CreateMock` (64fa673fa)
- Deprecate `ApplicationInfo::caret_info` (ca1ec15e1)
- Delete `LayoutIndicatorWindowByCaretInfo`, which should be unused (3190db241)
- Delete `LayoutCandidateWindowByCaretInfo`, which should be unused (f76e0a79d)
- Delete `LayoutCandidateWindowByCompositionForm`, which should be unused (e55faea16)
- Delete `LayoutCandidateWindowByClientRect`, which should be unused (85ae1c81f)
- Explicitly initialize mozc::EngineBuilder::model_path_fp_. (0b1ec6bdf)
- Delete unused `LayoutManager::LayoutCompositionWindow` (e20c55a58)
- Assume `ApplicationInfo::ShowCompositionWindow` is no longer used (de6df10a1)
- Remove IMM32 layout tests from `Win32RendererUtilTest` (eb314c993)
- Use `glob` in base/absl.gyp. (d9ae608c3)
- Add TSF layout tests for `LayoutManager` (a35a0debc)
- Remove `USE_LOCAL_COORD_FOR_CANDIDATE_FORM` workaround (1b21ee570)
- Remove `IGNORE_DEFAULT_COMPOSITION_FORM` workaround (f08aae9bc)
- Fix 1 ClangTidyReadability findings: * redundant string conversion (90556d722)
- Remove `SHOW_INFOLIST_IMMEDIATELY` workaround (2c1f34f65)
- Fix out-of-bounds iterator access in `Util::IsBracketPairText` (6392d0e96)
- Unsupport IMM32-based renderer command (9119d8c2f)
- [mozc] Use `absl::Duration` and `absl::Time` throughout instead of weakly-typed integer durations and times (1a508940f)
- Update MOZC_LOG_PROTOBUF. (f55c2d0be)
- LSC: C++ DebugString to absl::Stringify (7a54cb9a5)
- Rely on `.gitattributes` for line ending settings for Windows (a5e7e460b)
- Delete unused CI files (35593f3ec)
- Change all `*.rc` file type to `text` (70a051220)
- Add explicit dependency to `base_core` in base.gyp. (163af2ec0)
- Use MOZC_LOG_PROTOBUF as a temporary solution to deprecate DebugString() for the OSS build. (13afaba7b)
- Fix missing file deps in `gen_win32_resource_header.gypi` (54aeb538a)
- Use `NiceMock<T>` for `MockConverter` (07f9065da)
- Update BUILD_OSS to 5050. (ce638dc45)
- Fix potential `mozc_renderer` launch failures (7a54d14ba)
- Run test sequentially in `build_mozc.py runtests` by default (d7ac4cc9b)
- Set `PYTHONUTF8=1` for Windows GYP build (187c9f7af)
- Replace reinterpret_cast by memcpy. (559e8108b)
- LSC: C++ DebugString to AbslStringify (b79bb8578)
- Refactoring of NBestGenerator (859876233)
- Update a comment. (8782b5ae1)
- Deprecate IMM32 stuff from `renderer_command.proto` (ae14d9498)
- Update filtering rules for redundant candidates. (3c4d4844b)
- Migrate //engine:engine_builder to `mozc::Thread2`. (06417c624)
- Use fallback offset cost for single kanji entries. (f7ad86745)
- Fix 2 ClangTidyReadability findings: * redundant string conversion (832d55b5c)
- Fix 2 ClangTidyReadability findings: * redundant string conversion (344331e6a)
- Fix 3 ClangTidyReadability findings: * redundant string conversion (bea782560)
- Refactoring of QualityRegressionUtil (fb007d83d)
- Remove expanded chars for the intended modifier key from type corrected queries. (4afa27051)
- Fix 2 ClangTidyReadability findings: * redundant string conversion (8baccbfce)
- Fix 2 ClangTidyReadability findings: * redundant string conversion (b20d75365)
- Include what you use in `win32/base/uninstall_helper.h` (d69f5f7af)
- Remove unused stuff from `win32/base/uninstall_helper.cc` (5fee24fa7)
- Delete `win32/base/immdev.h` (32f19e3fd)
- Delete unused `ImmRegistrar` (b8e63d231)
- LSC: Sort additional lists with strings and labels (d89e8dcef)
- Assume `SystemUtil::IsWindows8OrLater()` is always `true` in `imm_util.cc` (1aa495b28)
- Assume `SystemUtil::IsWindows8OrLater()` is always `true` in `migration_util.cc` (8b0f34726)
- Remove noisy single kanji entries (b29e6f76a)
- Add 一本(いっぽん) of the same POS IDs with 一個(いっこ). (cf3e496e3)
- Accept absl::string_view for Mmap::Open(). (a76205ee7)
- - Make ResultCostLess() consistent with the function name. - Add length comparison for value string.   - The default operator `<` does not compare strings in UTF-8. (ba6c4aaba)
- Remove unused `MigrationUtil::RestorePreload()`. (76ec18450)
- Remove unused `ImeUtil::IsDefault()`. (8f875f2df)
- Delete unused `FocusHierarchyObserver` and its related classes. (e7c4247ec)
- Refactor and fix concurrency issues in //renderer::renderer_client. (c51876ab8)
- Remove dependency on `FocusHierarchyObserver` from `win32/tip/` (4e237315e)
- Stop supporting IMM32 Mozc in `UninstallHelper::GetNewEnabledProfileForVista()`. (c777afc87)
- Bug fix: Check `seen_` map before checking other conditions not to increment counters. (97ad827d9)
- Remove `UninstallHelper::RemoveHotKeyForVista()`. (94b635598)
- Amend `UninstallHelperTest::BasicCaseForWin8` (101700df1)
- Delete `DisableLegacyMozcForCurrentUserOnWin8()` (795bcd579)
- Assume `SystemUtil::IsWindows8OrLater()` is always `true` in `ime_switcher.cc` (d097ec8c4)
- Assume `SystemUtil::IsWindows8OrLater()` is always `true` in `prelauncher.cc` (e0bbc0337)
- Skip filtering candidates of user dictionary. (2340b22b3)
- Let Mozc binaries require Windows 8 or later. (814606b5f)
- Implement PlatformString and PlatformStringView (8b69a84db)
- Remove OutputUtil (82beec68c)
- Add a experimental feature for the new Typing Correction Scoring. (c9c94eb42)
- Fix a build error of symbol_rewriter.cc (44da94553)
- multifile: Pass the string to InputMultiFile (7a915faa3)
- Add a POSIX fallback implementation for DeleteRecursively. (a36c42a34)
- Make TempDirectory/TempFile move constructors noexcept (da6c973aa)
- Change the GoogleTest workspace name to com_google_googletest (c02d44c8a)
- Take std::string instead of absl::string_view when owned string is needed. (a4615f4a3)
- Change the margin for CompatibilityTest to 100 us. (8e020738d)
- Delete `win32/ime` (bc72121c8)
- Remove KeyMapInterface, Merge keymap{_interface,-inl}.h to keymap.h (08ef9a0c6)
- Unsupport `--mode={,un}register_ime` in `mozc_broker` (d8c4d2efe)
- Drop IMM32 support from `win32/custom_action/` (7a8498869)
- Add BUILD rules for win32/broker (340c3188b)
- Remove unused json_util (57add9569)
- Let Mozc Installer require Windows 8+ (a895a5559)
- Fix 1 ClangTidyReadability findings: * redundant string conversion (b52fbbfda)
- Fix a build failure on macOS. (7e1562b57)
- Simplify the logic of LoadIconFromResource. (d2a1d0f02)
- Remove deprecated and unused Util::Sleep (415684171)
- base: Add BUILD rules for update_util (c4ef6015e)
- Migrate //ipc:ipc_test to `mozc::Thread2`. (8b236e234)
- Move broker library function declarations to header files from .cc (06a35a77f)
- Reorder declarations in //renderer:renderer_client. (e7f823f23)
- date_rewriter: const std::string& -> absl::string_view (69ccfeb50)
- rewriter: const std::string& -> absl::string_view (680a4eb32)
- NumberString: const std::string& -> absl::string_view (61c241b75)
- calculator: const std::string& -> absl::string_view (ee95e1578)
- Add nomsan to temp_dir due to a false positive with fts. (d025aa1e3)
- Refactor //client:client_quality_test_main. (73d50a0c6)
- Add logs about removed candidate in NBestGenerator. (5c8bdb385)
- Refactoring of NBestGenerator. (6a1e33323)
- segment: move implicit constructors/destructors to the header file (9c78c48aa)
- Use absl::Time-based interface (77e7b4b62)
- dictionary: const std::string& -> absl::string_view Move implicit destructors to header files. (2451a52dd)
- - Changed the condition for single kanji cost offset so that single kanjis will not be added before the prefix entries - Add the cost offset for the single kanji entries with shorter key (5a73970a0)
- Add BUILD rules for win32/base (86b5d702b)
- Fix compile errors with clang (68e39f923)
- Add user32.lib target (for win32/base) (e1830f972)
- client_interface: Include ipc.h (iwyu) (c46c5d5b2)
- Remove ext_third_party_dir from gyp (677055c3d)
- Add a stub for lexan.cc_windows_dll (532bf85df)
- mmap: Use absl::Span and absl::Cleanup, mark trivial methods constexpr (1cbd19e79)
- Supports more bracket pairs in IsBracketPairText(). (dd3dfc5b2)
- Add BUILD files for Windows renderer (7363ef97f)
- TempDirectory: delete files recursively in the destructor (b215e72db)
- recursive: fix a bug where it wasn't actually deleting files in Linux and MacOS (4d10900db)
- Add --text option to gen_counter_suffix_array.py for debugging. (381539270)
- [Refactoring] Split the penalty for prefix candidates (10417583a)
- Move = default functions to the header file to make Thread2 trivially constructible/destructible (73c012d76)
- refactor: use absl::Cleanup instead of unique_ptr (28c7092be)
- Move = default constructors/destructors to header file to make the eligible classes trivially constructible/destructible. (56a625e46)
- Show multiple candidates by SHOW_LOG_BY_VALUE (031d1755a)
- Add server/BUILD targets for Windows (557eddfc2)
- Refactor clock and clock_mock with absl::Time (a7afde813)
- Fix 1 ClangTidyReadability findings: * redundant string conversion (9624db9e6)
- Fix a bug where win32::Utf8ToWide and WideToUtf allocated an extra character when converting strings. (3e7b5963e)
- Add single kanji prediction aggregator (664d0c51a)
- - Refactor the condition for predictive penalty. - Update the comment. (30cab1275)
- Refactor Table; Make Entry and Table classes non-virtual (968f857b6)
- Add HwndToUint32 function to cast HWND to uint32_t in 64-bit environments (70ab7ac04)
- Move SpecialKeyMap and related functions to special_key.cc (0dc1550e7)
- Use GetSourceFileOrDie to load font files. Change the paths to the same place as what Bazel data attribute uses. (dc71b3693)
- Add copts_wtl and features_gdi macros (83ce48657)
- Update BUILD_OSS to 5029. (961949a15)

## Release 2.29.5268.102 (2023-11-08)
Commit: [7a4bd278a86b6e0c48254ab7442d9fe1b4d8d145](https://github.com/google/mozc/commit/7a4bd278a86b6e0c48254ab7442d9fe1b4d8d145)
Summary:
2.29.5268.102

Typing quality
* Added  鵼(ぬえ) and 喃(のう) to the word dictionary.

Linux
* Fixed the crash issue of the candidate window UI (#820)
* Use WAYLAND_DISPLAY instead of nonstandard XDG_SESSION_TYPE (#797)
* Let Qt mozc_renderer always use X11 protocol (#794)

Windows
* Enabled the candidate window to respect the vertical writing mode (#362)
* Updated InputScope mapping to be compatible with MS-IME as of Windows 11 22H2 (#818, #826)
* Addressed the issue of no response on MS-Word (#819)
* Enabled the candidate window to consider per-monitor DPI settings (#832)

Build
* Enabled C++20 (#783)
* Switched to Qt 6.6.0 for Windows and macOS (#833)
* Reduced Qt6 binary size (#822)
* macOS: Fixed the non executable error of GUI tools with GYP
* Windows: Stopped specifying /BASE option (#834)
* Windows: Enabled Hardware Enforced Stack Protection (#835)
* Windows: Set default dependent load flags to Mozc executables for Windows (#836)
* Windows: Removed the dependency on CoCreateInpustance from mozc_tip dlls (#837)

## Release 2.29.5374.102 (2024-03-13)
Commit: [9114a34323c96b4af6ea9c0e0ed0e208ee01c55f](https://github.com/google/mozc/commit/9114a34323c96b4af6ea9c0e0ed0e208ee01c55f)
Summary:
2.29.5374.102

Features
* Updated the year to 2024
* Updated the word dictionary
* Updated the Emoji version to 15.1
* Added 歲 (U+6B72) as a 旧字体 of 歳 (U+6B73) (#860)
* Adjusted the conversion with suffix numbers (e.g. 後に vs あと2)
* Windows: Supported to prelaunch processes from the installer (#845)

Bug fix
* Changed to use noun (名詞) as the default part-of-speech instead of no-pos (品詞なし)

Build
* Supported Bazel 7.0.0
* Updated the Protobuf version: v24.2 → v25.0 (#841)
* Updated the Abseil version: 20230125.3 → 20230802.1 (#841)
* Supported to follow updates of external environmental dependencies (#843, #844)
* Removed `third_party/ipa_font` and introduced our own testing font  (#842)
* Android: Fixed the linkage error of Android library build (#840)
* macOS, Windows: Switched to Qt 6.6.1 (#846)
* macOS: Updated the rule_apple version to 3.1.1
* macOS: Updated the default mac_sdk for GYP from 13.0 to 13.3
* macOS: Switched to macos-14 for GitHub Actions runner
* Windows: Supported the GYP build with 64 or more cores
* Windows: Stopped using WTL

Code
* Removed the file path limitation for PRs
* Performed code refactoring
* Added UPDATE_COMPOSITION to the session commands

## Release 2.30.5544.102 (2024-08-04)
Commit: [225996e67fa694a005a108a425a4186f618784a8](https://github.com/google/mozc/commit/225996e67fa694a005a108a425a4186f618784a8)
Summary:
2.29.5374.102 → 2.30.5544.102

Features
* Updated the word dictionary (6af6a25)
* Added words based on the GitHub issues (f518d3d, d0d1bc8, 2ea9504, d6a55d2, 4f03239, #928)
* Updated the reading correction rules (3a665b1)
* Added more symbol characters (#933)
* Updated Emoji entries (68c3985)
* Fixed voiced Katakana conversion from ゑ (ヸ → ヹ)
* Supported the conversion from "なう" to date/time (i.e. 2024/12/31 23:59)
* Improved the AD to Era conversion: "2024ねん" → "令和6年" (6ceada3)
* Improved the usability of era-to-ad conversion (れいわ６ねん→2024年)
* Supported loading user dictionary files exported from Gboard
* Improved the about dialog with the dark mode (#897)
* Linux: Improved the candidate UI with HiDPI displays (#823)

Bug fix
* Fixed the crash issue on saving the user dictionary. (42cbb3f)
* Fixed the crash issue on the debug build caused by converting negative numbers (#878)
* Fixed the issue that Bazel build did not included entries in dictionary_manual/ (47eb877)
* Linux: Prevent executing multiple candidate windows (#912)
* macOS: Fixed jaggy icons for the GUI tools (#964)
* macOS: Replaced "Google Japanese Input" with Mozc in UI messages. (caeb9ce)
* macOS: Fixed the crash issue of mozc_emacs_helper (#900)
* macOS (Apple Silicon): Fixed the crash issue of GUI tools (#791)

Build
* Updated the Abseil version: 20230802.1 → 20240116.1
* Updated the Protobuf version: v25.0 → v27.0 (#937, #913)
* Updated the Qt version: 6.6.1 → 6.7.2 (#963, #934, #911, #877)
* Rebase Mozc onto Abseil logging library. (c77285e)
* Supported dictionary_manual/words.tsv as additional dictionary entries (8d3a297)
* Set proper release/debug build options for GitHub Actions (07c5f89)
* Linux: Added Dockerfile for Ubuntu 24.04 (#924)
* Linux: Deprecated the GYP build
* Windows: Added CI of Bazel for the converter and GUI tools (#948)
* Windows: Simplified the build process by reducing manual execution of the vcvars .bat file. (#923)
* Windows: Update the WiX version: v3.14 → v4.0.5 (#894)

Code
* Performed a number of code refactorings
* Applied Clang's build cleaner
* Completed the migration from base/logging.h to Abseil log.
* macOS: Applied suggestions from code scanning alerts (b955086)

## Release 2.31.5712.102 (2025-01-17)
Commit: [be37e5bad672c78a6d2cb89da9fd3cd53c43afb5](https://github.com/google/mozc/commit/be37e5bad672c78a6d2cb89da9fd3cd53c43afb5)
Summary:
2.30.5544 → 2.31.5712

Conversion
* updated the LM dictionary
* updated symbols (#1074, #1100)
* updated emoji data to CLDR 46 (Emoji 16.0)
* updated zip code entries (#1063).
* updated word entries (#1068, #1069)
* fixed conversion errors reported by users.

Features
* updated the copyright year to 2025.
* added words based on the reports from contributors (b0b37db, 9c53503, ad8a2be)
* updated the collocation data based on the reports from contributors (456284e)
* Windows: bundle debug symbol for Mozc TIP DLL (#1081)
* Windows: shutdown existing Mozc processes on upgrading the version (#1093)

Bug fix
* Linux: enabled switching to the DIRECT mode from the menu (#1061)
* Linux: enabled switching modes with Super+Space in Wayland (#853, #1059)
* macOS: addressed crash issues on macOS 15 (Sequoia)
* macOS: fixed the limitation of mouse clicking on the renderer on macOS 15 (120bd93)
* Windows: fixed the freeze issue with some applications like the searchhost.exe (#1077, #856)
* Windows: fixed the UI language issue of the GUI tools (#1110)
* Windows: fixed the setting of Omaha updater for the GoogleJapaneseInput build (#1072)

Build
* supported Bazel 8.0.0 (#1118)
* supported MODULE and removed WORKSPACE for Bazel (#1002, #1115)
* updated the Abseil version:  20240116.1 → 20240722.0
* updated the Protobuf version: v27.0 → v29.1
* updated the GoogleTest version: v1.12.1 → v1.15.2
* supported the `–config=release_build` Bazel option (9fd8739).
* supported Python 3.14 (#1084)
* Android: Updated the Docker build environment
* Linux: updated the build environment: Ubuntu 22.04 → 24.04 (#924)
* Linux: supported gcc-14.1.1 without additional build flags (#927)
* macOS: Supported building .dmg file.
* macOS / Windows: Updated Qt version: 6.7.2 → 6.8.0 (#1065, #1105, #1110, #1121)
* Windows: Supported Bazel build (#948)
* Windows: Updated the Wix version: 4.0.5 → 5.0.2 (#1070)

Code
* added a lint checker for BUILD.bazel and *bzl files (#1089)
* renamed the protobuf field from Candidates to CandidateWindow
* refactoring of ConversionRequest making it as immutable object
* refactoring of the Converter implementation
* refactoring of Engine and SessionConverter to make each module pluggable
* removed cyclic dependency between Converter and Rewriter.
* performed various code refactoring



2.19.2644.102 - 2.20.2673.102 / *2016-10-20* - *2016-12-08*

--------------------------------------------------

You can check out Mozc [2.20.2673.102](https://github.com/google/mozc/commit/280e38fe3d9db4df52f0713acf2ca65898cd697a) as follows.



```

git clone https://github.com/google/mozc.git -b master --single-branch

cd mozc

git checkout 280e38fe3d9db4df52f0713acf2ca65898cd697a

git submodule update --init --recursive

```



Summary of changes between [2.19.2644.102](https://github.com/google/mozc/commit/c19cc87a399bae0863b76daece950b8bb1be8175) and [2.20.2673.102](https://github.com/google/mozc/commit/280e38fe3d9db4df52f0713acf2ca65898cd697a) as follows.



  * Third party libraries:

    * None.

  * Build related changes:

    * `--qtver` GYP build option was removed ([280e38f](https://github.com/google/mozc/commit/280e38fe3d9db4df52f0713acf2ca65898cd697a)).

    * Mozc for macOS now uses macOS 10.11 SDK by default ([b2a74bb](https://github.com/google/mozc/commit/b2a74bb1bab6cc3de8611b7679b4c79f45d8ddb3)).

  * Major changes:

    * `src/data/installer/credits_ja.html` was removed ([2ec6c8f](https://github.com/google/mozc/commit/2ec6c8f9dc1478f4d47739ee2d017d02b954b75a)).

    * Mozc for macOS now generates 64-bit executables.  32-bit machine is no longer supported on macOS.

    * Mozc for Android now has more translations ([d914458](https://github.com/google/mozc/commit/d91445866b2b574a35ce1f79894403e26f4b5ae2)).

  * Fixed issues:

    * [#187](https://github.com/google/mozc/issues/187): build_mozc.py always generates 32 bit binaries on 64 bit OSX

    * [#327](https://github.com/google/mozc/issues/327): Switch to Qt5 from Qt4

    * [#348](https://github.com/google/mozc/issues/348): DirectWrite may fail to render text in certain enviromnents

    * [#391](https://github.com/google/mozc/issues/391): ImportError: gen_zip_code_seed.py

    * [#399](https://github.com/google/mozc/issues/399): OK/Cancel buttons on Mozc key binding editor dialog cannot be clicked on Windows

    * [#400](https://github.com/google/mozc/issues/400): Close icon on GUI dialogs do not work on Windows

  * Total commits:

    * [30 commits](https://github.com/google/mozc/compare/c19cc87a399bae0863b76daece950b8bb1be8175%5E...280e38fe3d9db4df52f0713acf2ca65898cd697a).





2.18.2613.102 - 2.19.2643.102 / *2016-09-15* - *2016-10-18*

--------------------------------------------------

You can check out Mozc [2.19.2643.102](https://github.com/google/mozc/commit/f5dcadf0dee0382612398965adc2c110ef027d9c) as follows.



```

git clone https://github.com/google/mozc.git -b master --single-branch

cd mozc

git checkout f5dcadf0dee0382612398965adc2c110ef027d9c

git submodule update --init --recursive

```



Summary of changes between [2.18.2613.102](https://github.com/google/mozc/commit/f76c304164e54414b5310010bc26e27b37764822) and [2.19.2643.102](https://github.com/google/mozc/commit/f5dcadf0dee0382612398965adc2c110ef027d9c) as follows.



  * Third party libraries:

    * protobuf: [e8ae137 -> c44ca26](https://github.com/google/protobuf/compare/e8ae137c96444ea313485ed1118c5e43b2099cf1...c44ca26fe89ed8a81d3ee475a2ccc1797141dbce)

    * Dropped dependency on [fonttools](https://github.com/googlei18n/fonttools)

  * Build related changes:

    * `--qtver=5` GYP build option is implicitly assumed on macOS and Linux builds ([f76c304](https://github.com/google/mozc/commit/f76c304164e54414b5310010bc26e27b37764822)). On Windows, `--qtver=4` is still the default.

  * Major changes:

    * Mozc for macOS now supports 10.12 as a runtime environment.

    * Mozc for Android now uses on-device font to render keytop icons ([f5dcad](https://github.com/google/mozc/commit/f5dcadf0dee0382612398965adc2c110ef027d9c)).

  * Fixed issues:

    * [#263](https://github.com/google/mozc/issues/263): Incorrect position in voiced sound marks on the key pad in Android

    * [#384](https://github.com/google/mozc/issues/384): HUAWEI P9 lite does not show MozcView.

    * [#388](https://github.com/google/mozc/issues/388): Having multiple abbreviation user dictionary entries with the same reading should be supported

    * [#389](https://github.com/google/mozc/issues/389): Emoticon user dictionary entry should not be treated a content word

  * Total commits:

    * [39 commits](https://github.com/google/mozc/compare/f76c304164e54414b5310010bc26e27b37764822%5E...f5dcadf0dee0382612398965adc2c110ef027d9c).





2.17.2532.102 - 2.18.2612.102 / *2016-03-15* - *2016-09-13*

--------------------------------------------------

You can check out Mozc [2.18.2612.102](https://github.com/google/mozc/commit/2315f957d1785130c2ed196e141a330b0857b065) as follows.



```

git clone https://github.com/google/mozc.git -b master --single-branch

cd mozc

git checkout 2315f957d1785130c2ed196e141a330b0857b065

git submodule update --init --recursive

```



Summary of changes between [2.17.2532.102](https://github.com/google/mozc/commit/09b47c3b5a6418e745a809cc393a267e8a637740) and [2.18.2612.102](https://github.com/google/mozc/commit/2315f957d1785130c2ed196e141a330b0857b065) as follows.



  * Third party libraries:

    * protobuf: [d5fb408 -> e8ae137](https://github.com/google/protobuf/compare/d5fb408ddc281ffcadeb08699e65bb694656d0bd...e8ae137c96444ea313485ed1118c5e43b2099cf1)

    * GYP: [e2e928b -> 4ec6c4e](https://chromium.googlesource.com/external/gyp/+log/e2e928bacd07fead99a18cb08d64cb24e131d3e5..4ec6c4e3a94bd04a6da2858163d40b2429b8aad1)

    * breakpad: [d2904bb -> 85b27e4](https://chromium.googlesource.com/breakpad/breakpad/+log/d2904bb42181bc32c17b26ac4a0604c0e57473cc..85b27e4a692b803dcd493ea0a9ce3828af6b82bd)

    * Dropped dependency on [zlib](https://github.com/madler/zlib)

  * Build related changes:

    * Renamed `src/mozc_version_template.txt` to `src/data/version/mozc_version_template.bzl`

    * Reference build environment now uses Ubuntu 14.04.5 ([a7cbf72](https://github.com/google/mozc/commit/a7cbf72341f5dc5d7181fecd10cb48838d64ef4c))

    * Reference build environment now uses Ninja 1.7.1 ([d2bc62b](https://github.com/google/mozc/commit/d2bc62b4de0a583355d594f66e312022e3c3deec))

    * Removed `--android_compiler` GYP option ([5ce7fa6](https://github.com/google/mozc/commit/5ce7fa6214a00c95edb2b4ce0bbd980b219b18c7))

    * Android build requires Android NDK r12b ([5ce7fa6](https://github.com/google/mozc/commit/5ce7fa6214a00c95edb2b4ce0bbd980b219b18c7))

  * Major changes:

    * Improved Store Apps compatibility on Windows ([0488082](https://github.com/google/mozc/commit/048808221cae6180c7a6ae6623e13c58490f30ed))

  * Fixed issues:

    * `NPE` in `UserDictionaryToolActivity.onPostResume` on Android ([09b47c3](https://github.com/google/mozc/commit/09b47c3b5a6418e745a809cc393a267e8a637740))

    * [#273](https://github.com/google/mozc/issues/273): Compilation errors in Android arm64 and mips64 build

    * [#373](https://github.com/google/mozc/issues/373): Unexpected size bloat of the APK

    * [#374](https://github.com/google/mozc/issues/374): Duplicate candidates after Undo

    * [#375](https://github.com/google/mozc/issues/375): `90-` is suggested from `090-`

    * [#376](https://github.com/google/mozc/issues/376): Suggestion-only user dictionary entry may not work

    * [#377](https://github.com/google/mozc/issues/377): Abbreviation user dictionary entry may not work

    * [#378](https://github.com/google/mozc/issues/378): Suppression word may not work

    * [#379](https://github.com/google/mozc/issues/379): Single character noun user dictionary entry may not work

    * [#380](https://github.com/google/mozc/issues/380): Dependency on `dictionary/pos_matcher.h` from `session/session_server.cc` is missing in GYP rules

    * [#382](https://github.com/google/mozc/issues/382): Fix typo

  * Total commits:

    * [84 commits](https://github.com/google/mozc/compare/09b47c3b5a6418e745a809cc393a267e8a637740%5E...2315f957d1785130c2ed196e141a330b0857b065).





2.17.2405.102 - 2.17.2531.102

--------------------------------------------------

You can check out Mozc [2.17.2531.102](https://github.com/google/mozc/commit/120d6a1ba6d9bad10842c6531728fc1dd8bbf731) as follows.



```

git clone https://github.com/google/mozc.git -b master --single-branch

cd mozc

git checkout 120d6a1ba6d9bad10842c6531728fc1dd8bbf731

git submodule update --init --recursive

```



Summary of changes between [2.17.2405.102](https://github.com/google/mozc/commit/b0259d5b1dd92f5c3bc4cc9e2793649424acda87) and [2.17.2531.102](https://github.com/google/mozc/commit/120d6a1ba6d9bad10842c6531728fc1dd8bbf731) as follows.



  * Third party libraries:

    * protobuf: [1a59a71 -> d5fb408](https://github.com/google/protobuf/compare/1a59a715dc5fa584340197aac0811ba3de9850b5...d5fb408ddc281ffcadeb08699e65bb694656d0bd)

  * Build related changes:

    * Building Mozc for Windows requires Visual Studio 2015 update 3.

    * `--qtdir` option is no longer supported in Linux desktop build ([d003076](https://github.com/google/mozc/commit/d00307617d5922769462ba066d891a72f8ff82ea)).

  * Major changes:

    * Updated system dictionary.

    * Removed several Shift-JIS-based normalizations on Windows ([26241b0](https://github.com/google/mozc/commit/26241b046c1f8fe55c4994d664ea10e749cff62c)).

    * Mozc for Windows requires SSE2 even on 32-bit environment.

    * Mozc for Windows supports Windows 7 SP1 and later only.

    * Mozc for macOS supports macOS 10.9 and later only.

    * Mozc for desktop platforms (Windows, macOS, desktop Linux) supports Qt5 behind `--qtver=5` GYP option.

  * Fixed issues:

    * Fix OOM when importing too large dictionary file on Android ([5c859ae](https://github.com/google/mozc/commit/5c859ae8a7b1854e78af2c81330b75bac0e9532a))

    * [#298](https://github.com/google/mozc/issues/298): Fix NPE on Samsung devices on showing toast

    * [#315](https://github.com/google/mozc/issues/315): Switch to Visual C++ 2015

    * [#372](https://github.com/google/mozc/issues/372): Discontinue the support of Windows Vista

  * Total commits:

    * [128 commits](https://github.com/google/mozc/compare/b0259d5b1dd92f5c3bc4cc9e2793649424acda87%5E...120d6a1ba6d9bad10842c6531728fc1dd8bbf731).





2.17.2355.102 - 2.17.2404.102

--------------------------------------------------

You can check out Mozc [2.17.2404.102](https://github.com/google/mozc/commit/73a8154b79b0b8db6cf8e11d6f1e750709c17518) as follows.



```

git clone https://github.com/google/mozc.git -b master --single-branch

cd mozc

git checkout 73a8154b79b0b8db6cf8e11d6f1e750709c17518

git submodule update --init --recursive

```



Summary of changes between [2.17.2355.102](https://github.com/google/mozc/commit/f1d68857831cc05a435184c375d5ab64438ed14a) and [2.17.2404.102](https://github.com/google/mozc/commit/73a8154b79b0b8db6cf8e11d6f1e750709c17518) as follows.



  * Third party libraries:

    * protobuf: [172019c -> 1a59a71](https://github.com/google/protobuf/compare/172019c40bf548908ab09bfd276074c929d48415...1a59a715dc5fa584340197aac0811ba3de9850b5)

  * Build related changes:

    * Building Mozc requires [protobuf](https://github.com/google/protobuf) 3.0 or later.

    * `--android_stl` GYP option is removed in Android build. You cannot use GNU STL to build Mozc for Android anymore.

  * Major changes:

    * None.

  * Fixed issues:

    * [#369](https://github.com/google/mozc/issues/369): Unexpected software keyboard layout can be chosen

    * [#370](https://github.com/google/mozc/issues/370): Mozc keeps crashing on Android N Developer Preview 5

    * [#371](https://github.com/google/mozc/issues/371): Shortcut word in personal dictionary should not be used for multi segment conversion

  * Total commits:

    * [50 commits](https://github.com/google/mozc/compare/f1d68857831cc05a435184c375d5ab64438ed14a%5E...73a8154b79b0b8db6cf8e11d6f1e750709c17518).





2.17.2323.102 - 2.17.2354.102

--------------------------------------------------

You can check out Mozc [2.17.2354.102](https://github.com/google/mozc/commit/02d3afb5bdfda3dde75d3c196960ee96c9ba918a) as follows.



```

git clone https://github.com/google/mozc.git -b master --single-branch

cd mozc

git checkout 02d3afb5bdfda3dde75d3c196960ee96c9ba918a

git submodule update --init --recursive

```



Summary of changes between [2.17.2323.102](https://github.com/google/mozc/commit/bf51ad0a8dbe895f4c2daf9c27b6262ecff46855) and [2.17.2354.102](https://github.com/google/mozc/commit/02d3afb5bdfda3dde75d3c196960ee96c9ba918a) as follows.



  * Third party libraries:

    * None.

  * Build related changes:

    * None.

  * Major changes:

    * [2.17.2323.102](https://github.com/google/mozc/commit/bf51ad0a8dbe895f4c2daf9c27b6262ecff46855) and later commits in OSS repository preserve the original CL commit date in Google internal repository.

      * Consider to specify `--topo-order` option to `git log` to see commits in the actual commit order.

    * Multiple performance improvements in Android.

  * Fixed issues:

    * None.

  * Total commits:

    * [32 commits](https://github.com/google/mozc/compare/bf51ad0a8dbe895f4c2daf9c27b6262ecff46855%5E...02d3afb5bdfda3dde75d3c196960ee96c9ba918a).





2.17.2314.102 - 2.17.2322.102 / *2016-01-10* - *2016-03-12*

--------------------------------------------------

You can check out Mozc [2.17.2322.102](https://github.com/google/mozc/commit/9b4c9e0e6764cca0e52b8d076165a4f1278effd4) as follows.



```

git clone https://github.com/google/mozc.git -b master --single-branch

cd mozc

git checkout 2628af6995dbbbb9ccdb52d1160db1dbd5ed3bae

git submodule update --init --recursive

```



Summary of changes between [2.17.2314.102](https://github.com/google/mozc/commit/d938fbb58c62f7bd86fce28267fbabffd1f55f66) and [2.17.2322.102](https://github.com/google/mozc/commit/9b4c9e0e6764cca0e52b8d076165a4f1278effd4) as follows.



  * Third party libraries:

    * googletest: [1d53731 -> 82b11b8](https://github.com/google/googletest/compare/1d53731f2c210557caab5660dbe2c578dce6114f...82b11b8cfcca464c2ac74b623d04e74452e74f32)

    * WTL: 9.0.4140 -> 9.1.5321

  * Build related changes:

    * Building macOS binaries now requires [Ninja](https://github.com/ninja-build/ninja) instead of `xcodebuild`.

  * Major changes:

    * None.

  * Fixed issues:

    * [#247](https://github.com/google/mozc/issues/247): Use ninja to build Mac binaries

    * [#355](https://github.com/google/mozc/issues/355): Native resource leak due to the `missing pthread_detach` call in `mozc::Thread::Detach`

    * [#361](https://github.com/google/mozc/issues/361): `ImmSetCandidateWindow()` with `CFS_EXCLUDE` isn't supported on Win Vista and Win7

  * Total commits:

    * [15 commits](https://github.com/google/mozc/compare/d938fbb58c62f7bd86fce28267fbabffd1f55f66%5E...9b4c9e0e6764cca0e52b8d076165a4f1278effd4).





2.17.2288.102 - 2.17.2313.102 / *2016-01-03* - *2016-01-10*

--------------------------------------------------

You can check out Mozc [2.17.2313.102](https://github.com/google/mozc/commit/2628af6995dbbbb9ccdb52d1160db1dbd5ed3bae) as follows.



```

git clone https://github.com/google/mozc.git -b master --single-branch

cd mozc

git checkout 2628af6995dbbbb9ccdb52d1160db1dbd5ed3bae

git submodule update --init --recursive

```



Summary of changes between [2.17.2288.102](https://github.com/google/mozc/commit/a86c7d014ac7bf36e06c5567c92ef515b3780783) and [2.17.2313.102](https://github.com/google/mozc/commit/2628af6995dbbbb9ccdb52d1160db1dbd5ed3bae) as follows.



  * Third party libraries:

    * None.

  * Build related changes:

    * None.

  * Major changes:

    * Update system dictionary.

    * Status icons for OS X are updated with Noto font.

  * Fixed issues:

    * [#344](https://github.com/google/mozc/issues/344): Support ```icon_prop_key``` entry in ibus-mozc

    * [#345](https://github.com/google/mozc/issues/345): Mozc for Android keeps crashing

    * [#347](https://github.com/google/mozc/issues/347): Software keyboard is not rendered correctly on Android 6 if non-material theme is selected

    * [#350](https://github.com/google/mozc/issues/350): Status icon is not updated when using Windows Store Apps in desktop mode on Windows 10

    * [#351](https://github.com/google/mozc/issues/351): Mozc cannot be activated in the search box on the task bar when configured to be the default IME on Windows 10

    * Following issues are not completely fixed yet, but at least worked around.

      * [#348](https://github.com/google/mozc/issues/348): DirectWrite may fail to render text in certain enviromnents

      * [#349](https://github.com/google/mozc/issues/349): Word suggestion can be unexpectedly suppressed on Chromium

  * Total commits:

    * [29 commits](https://github.com/google/mozc/compare/a86c7d014ac7bf36e06c5567c92ef515b3780783%5E...2628af6995dbbbb9ccdb52d1160db1dbd5ed3bae).





2.17.2285.102 - 2.17.2287.102 / *2016-01-01* - *2016-01-02*

--------------------------------------------------

You can check out Mozc [2.17.2287.102](https://github.com/google/mozc/commit/ab4569e73bca8d2375262d243f362c7b848646da) as follows.



```

git clone https://github.com/google/mozc.git -b master --single-branch

cd mozc

git checkout ab4569e73bca8d2375262d243f362c7b848646da

git submodule update --init --recursive

```



Summary of changes between [2.17.2285.102](https://github.com/google/mozc/commit/4a370c6ea6f003be99e7837713a939a68b75aeae) and [2.17.2287.102](https://github.com/google/mozc/commit/ab4569e73bca8d2375262d243f362c7b848646da) as follows.



  * Third party libraries:

    * None.

  * Build related changes:

    * None.

  * Major changes:

    * None.

  * Fixed issues:

    * None.

  * Total commits:

    * [4 commits](https://github.com/google/mozc/compare/4a370c6ea6f003be99e7837713a939a68b75aeae%5E...ab4569e73bca8d2375262d243f362c7b848646da).





2.17.2241.102 - 2.17.2284.102 / *2015-11-15* - *2015-12-31*

--------------------------------------------------

You can check out Mozc [2.17.2284.102](https://github.com/google/mozc/commit/be24638ab360c39995ab2c10e34ab9b269e39dac) as follows.



```

git clone https://github.com/google/mozc.git -b master --single-branch

cd mozc

git checkout be24638ab360c39995ab2c10e34ab9b269e39dac

git submodule update --init --recursive

```



Summary of changes between [2.17.2241.102](https://github.com/google/mozc/commit/a54fee0095ccc618e6aeb07822fa744f9fcb4fc1) and [2.17.2284.102](https://github.com/google/mozc/commit/be24638ab360c39995ab2c10e34ab9b269e39dac) as follows.



  * Third party libraries:

    * fontTools: [5ba7d98 -> 8724513](https://github.com/googlei18n/fonttools/compare/5ba7d98a4153fad57258fca23b0bcb238717aec3...8724513a67f954eac56eeb77ced12e27d7c02b6b)

  * Build related changes:

    * Reference Dockerfile for Fedora now uses Fedora 23 base image.

    * Default ```SDKROOT``` for OS X build is switched from ```macosx10.8``` to ```macosx10.9```.

  * Major changes:

    * ```CalculatorRewriter``` is now triggered not only by inputs end with ```=``` but also by inputs start with ```=```.  For instance, now ```=1+1``` triggers ```CalculatorRewriter```.  See the commit message of [5d423b0b](https://github.com/google/mozc/commit/5d423b0ba6989481ad2474c0eaf8c387a2bdfcc9) and its unittests as for how it works.

    * Performance improvements in LOUDS.  See commits [3591f5e7](https://github.com/google/mozc/commit/3591f5e77d8bfb0ba6f1ac839b69eb9e7aa265c9) and [cac14650](https://github.com/google/mozc/commit/cac146508d32fcce1ecfec8d038f63f588ed13c4) for details.

  * Fixed issues:

    * [#317](https://github.com/google/mozc/issues/317): session_handler_scenario_test is flaky in Linux build on Travis-CI

    * [#341](https://github.com/google/mozc/issues/341): ```1d*=``` should not trigger language-aware rewriter

  * Total commits:

    * [48 commits](https://github.com/google/mozc/compare/a54fee0095ccc618e6aeb07822fa744f9fcb4fc1%5E...be24638ab360c39995ab2c10e34ab9b269e39dac).





2.17.2124.102 - 2.17.2240.102 / *2015-09-20* - *2015-11-15*

--------------------------------------------------

You can check out Mozc [2.17.2240.102](https://github.com/google/mozc/commit/95de40fa884d693172605e7283ec82233a908b29) as follows.



```

git clone https://github.com/google/mozc.git -b master --single-branch

cd mozc

git checkout 95de40fa884d693172605e7283ec82233a908b29

git submodule update --init --recursive

```



Summary of changes between [2.17.2124.102](https://github.com/google/mozc/commit/0943e518ebff9ddd9390d0ec29509cb0096ac240) and [2.17.2240.102](https://github.com/google/mozc/commit/95de40fa884d693172605e7283ec82233a908b29) as follows.



  * Third party libraries:

    * gyp: [cdf037c1 -> e2e928ba](https://chromium.googlesource.com/external/gyp/+log/cdf037c1edc0ba3b5d25f8e3973661efe00980cc..e2e928bacd07fead99a18cb08d64cb24e131d3e5)

    * zinnia: [44dddcf9 -> 814a49b0](https://github.com/taku910/zinnia/compare/44dddcf96c0970a806d666030295706f45cbd045...814a49b031709b34d23898bce47f08dc1b554ec8)

    * zlib: [50893291](https://github.com/madler/zlib/commit/50893291621658f355bc5b4d450a8d06a563053d) was added to submodules for NaCl build.

  * Build related changes:

    * Linux-only build option ```-j```/```--jobs``` was deprecated by [b393fbdc](https://github.com/google/mozc/commit/b393fbdc346a5243ad35eb559d4468a274f2d2d2).  See its commit log on how to work around it.

    * Pepper 45 SDK is required to build Mozc for NaCl.

    * Docker directory id moved from ```mozc/src/docker/``` to ```mozc/docker/``` by [cfe9a2a5](https://github.com/google/mozc/commit/cfe9a2a5c7576a01fdbbadca43760496a9405ece).

    * Enabled continuous build for Android, NaCl, and Linux-desktop on [Travis CI](https://travis-ci.org).

    * Enabled continuous test for OS X and Linux-desktop on [Travis CI](https://travis-ci.org).

    * ```REGISTER_MODULE_INITIALIZER```, ```REGISTER_MODULE_RELOADER```, ```REGISTER_MODULE_SHUTDOWN_HANDLER```, and ```REGISTER_MODULE_FINALIZER``` were deprecated since they are known as bug-prone.  Deprecating them allows us to reduce the number of use of ```Singleton<T>```, which is also known as bug-prone.

    * [#320](https://github.com/google/mozc/pull/320): ```InitGoogle``` was renamed to ```mozc::InitMozc``` and now declared in ```base/init_mozc.h```.  If you have relied on ```InitGoogle```, then you need to 1) include ```base/init_mozc.h``` and 2) replace ```InitGoogle``` with ```mozc::InitMozc```.

  * Major changes:

    * ```DateRewriter``` is now able to handle 3-digit.  For instance, when converting ```123``` you will see additional candidates such as ```1:23``` and ```01/23```.  See the commit message of [f2cc056f](https://github.com/google/mozc/commit/f2cc056fd289bb498703a451b163eb73de217c91) and its unittests for details.

  * Known issues:

    * [#263](https://github.com/google/mozc/issues/263): Voiced sound marks on the key pad is not placed at correct position in Android

    * [#273](https://github.com/google/mozc/issues/273): Compilation errors in Android arm64 and mips64 build

    * [#317](https://github.com/google/mozc/issues/317): session_handler_scenario_test is flaky in Linux build on Travis-CI

  * Fixed issues:

    * [#27](https://github.com/google/mozc/issues/27): build fail of ```base/iconv.cc```, FreeBSD

    * [#219](https://github.com/google/mozc/issues/219): Deprecate ```base/scoped_ptr.h```

    * [#252](https://github.com/google/mozc/issues/252): Remove dependency on iconv

    * [#328](https://github.com/google/mozc/issues/328): Partial commit clears remaining composing text in some cases

    * [#331](https://github.com/google/mozc/issues/331): Predictions on mobile can be too different from conversion result

    * [#332](https://github.com/google/mozc/issues/332): Clearing user dictionary on the preference app will not take effect immediately

  * Total commits:

    * [154 commits](https://github.com/google/mozc/compare/0943e518ebff9ddd9390d0ec29509cb0096ac240%5E...95de40fa884d693172605e7283ec82233a908b29).





2.17.2112.102 - 2.17.2123.102 / *2015-09-05* - *2015-09-19*

--------------------------------------------------

You can check out Mozc [2.17.2123.102](https://github.com/google/mozc/commit/e398317a086a78c0cf0004505eb8f56586e925b2) as follows.



```

git clone https://github.com/google/mozc.git -b master --single-branch

cd mozc

git checkout e398317a086a78c0cf0004505eb8f56586e925b2

git submodule update --init --recursive

```



Summary of changes between [2.17.2112.102](https://github.com/google/mozc/commit/25ae18a0ed595e5fee4bf546f21fbde2386a3da8) and [2.17.2123.102](https://github.com/google/mozc/commit/e398317a086a78c0cf0004505eb8f56586e925b2) as follows.



  * Third party libraries:

    * breakpad: [962f1b0e (r1391) -> d2904bb4 (r1419)](https://chromium.googlesource.com/breakpad/breakpad/+log/962f1b0e60eca939232dc0d46780da4fdbbcfd85%5E..d2904bb42181bc32c17b26ac4a0604c0e57473cc/)

    * gtest: [102b5048 (r700) -> 1d53731f (r707)](https://github.com/google/googletest/compare/102b50483a4b515a94a5b1c75db468eb071cf172%5E...1d53731f2c210557caab5660dbe2c578dce6114f)

    * gmock: [61adbcc5 (r501) -> d478a1f4 (r513)](https://github.com/google/googlemock/compare/61adbcc5c6b8e0385e3e2bf4262771d20a375002%5E...d478a1f46d51ac2baa3f3b3896139897f24dc2d1)

    * zinnia: [b84ad858 (0.0.4) -> 44dddcf9 (0.0.6)](https://github.com/taku910/zinnia/compare/7bdc645d7212c51d4bba234acea9ae0c6da2bbb8...44dddcf96c0970a806d666030295706f45cbd045)

    * Repository URL changes:

      * [GoogleCode] googlemock -> [GitHub] google/googlemock

      * [GoogleCode] googletest -> [GitHub] google/googletest

      * [GoogleCode] google-breakpad -> chromium.googlesource.com/breakpad/breakpad

      * [GoogleCode] japanese-usage-dictionary -> [GitHub] hiroyuki-komatsu/japanese-usage-dictionary

      * [SourceForge] zinnia -> [GitHub] taku910/zinnia

    * `src/DEPS` was deprecated and removed.  We use `git submodule` to track and check out dependent third party source code.

    * WTL is directly imported under `src/third_party` so as not to depend on subversion.

  * Build related changes:

    * Zinnia is now built from source and linked statically by default.  To link to system-installed Zinnia, specify `GYP_DEFINES="use_libzinnia=1"`.  Note that `build_mozc.py gyp --use_zinnia` is also deprecated.

  * Major changes:

    * Windows build now supports hand-writing with Zinnia.

  * Known issues:

    * [#263](https://github.com/google/mozc/issues/263): Voiced sound marks on the key pad is not placed at correct position in Android

    * [#273](https://github.com/google/mozc/issues/273): Compilation errors in Android arm64 and mips64 build

  * Fixed issues:

    * [#299](https://github.com/google/mozc/issues/299): Stop depending on subversion repositories in DEPS file

    * [#300](https://github.com/google/mozc/pull/300): Replace gclient/DEPS with git sub-modules

  * Total commits:

    * [16 commits](https://github.com/google/mozc/compare/25ae18a0ed595e5fee4bf546f21fbde2386a3da8%5E...e398317a086a78c0cf0004505eb8f56586e925b2).





2.17.2094.102 - 2.17.2111.102 / *2015-05-10* - *2015-08-15*

--------------------------------------------------

You can check out Mozc [2.17.2111.102](https://github.com/google/mozc/commit/d7b6196aeac52dd908ca051ba65e97b389f4503a) as follows.



```

gclient sync --revision=d7b6196aeac52dd908ca051ba65e97b389f4503a

```



Summary of changes between [2.17.2094.102](https://github.com/google/mozc/commit/c57a78e2b84880718f2621b9e8e4791419bee923) and [2.17.2111.102](https://github.com/google/mozc/commit/d7b6196aeac52dd908ca051ba65e97b389f4503a).



  * DEPS changes:

    * none

  * Build related changes:

    * Android build requires NDK r10e.

    * `*.proto` files are moved to `src/protocol/` to simplify build dependency.  Downstream projects may need to update include path and/or `.gyp` file accordingly.

    * Commit hashes between 2.17.2098.102 and 2.17.2106.102 were once changed [#292](https://github.com/google/mozc/issues/292).

    * Possible build failures in releases from 2.17.2099.102 (dbe800583e5676896ce603494ef3b306f38f7b85) to 2.17.2106.102 (3648b9bf06d5d9b36bed2425640bfd18ae05b588) due to [#295](https://github.com/google/mozc/issues/295).

  * Major changes:

    * ibus-mozc no longer enables `undo-commit` unless `IBUS_CAP_SURROUNDING_TEXT` is specified (0796f5143400e2beb3d18156ae426f8ce06b0c0d).

    * ibus-mozc no longer tries to align suggestion window to the left edge of the composing text (9fbcdd5e27cf26ff16d72bd2d92f269334912ede).

  * Known issues:

    * [#263](https://github.com/google/mozc/issues/263): Voiced sound marks on the key pad is not placed at correct position in Android

    * [#273](https://github.com/google/mozc/issues/273): Compilation errors in Android arm64 and mips64 build

  * Fixed issues:

    * [#243](https://github.com/google/mozc/issues/243): ibus predict window is shown at the previous cursor position

      * [Mozilla Bug 1120851](https://bugzilla.mozilla.org/show_bug.cgi?id=1120851): Candidate window sometimes doesn't set correct position with ibus + mozc when starting composition

    * [#254](https://github.com/google/mozc/issues/254): Preedit and candidate changes buffer modification flag

    * [#291](https://github.com/google/mozc/issues/291): Fix a typo

    * [#295](https://github.com/google/mozc/issues/295): Possible build failure due to missing dependency on `commands_proto` from `key_info_util`

    * [#296](https://github.com/google/mozc/issues/296): ibus-mozc should enable undo-commit if and only if `IBUS_CAP_SURROUNDING_TEXT` is set

  * Total commits:

    * [24 commits](https://github.com/google/mozc/compare/c57a78e2b84880718f2621b9e8e4791419bee923...d7b6196aeac52dd908ca051ba65e97b389f4503a).





2.17.2073.102 - 2.17.2095.102 / *2015-04-11* - *2015-05-10*

--------------------------------------------------

You can check out Mozc [2.17.2095.102](https://github.com/google/mozc/commit/321e0656b0f2e233ab1c164bd86c58568c9e92f2) as follows.



```

gclient sync --revision=321e0656b0f2e233ab1c164bd86c58568c9e92f2

```



Summary of changes between [2.17.2073.102](https://github.com/google/mozc/commit/0556a8bd57014f05583bc001d57b4b64aac00a47) and [2.17.2095.102](https://github.com/google/mozc/commit/321e0656b0f2e233ab1c164bd86c58568c9e92f2).



  * DEPS changes:

    * GYP repository is switched from code.google.com to chromium.googlesource.com.

    * ZLib repository is switched from src.chromium.org to github.com/madler/zlib.

  * Build related changes:

    * Reference build Docker image is switched from Ubuntu 14.04.1 to Ubuntu 14.04.2.

    * Fix build breakage in Android since [2.16.2072.102](https://github.com/google/mozc/commit/20c1c08d7d4e89530e3e42db3476d682981c2b68).

    * Add Dockerfile based on Fedora 21 to build Mozc for Android, NaCl, and Linux desktop.

    * Continuous build is available for OS X and Windows.

      * OS X: [Travis CI](https://travis-ci.org/google/mozc/)

      * Windows: [AppVeyor](https://ci.appveyor.com/project/google/mozc)

  * Major changes:

    * Update system dictionary.

    * Support rule-based zero query suggestion in [2.16.2080.102](https://github.com/google/mozc/commit/988392a0c821494fee2d90090cdca4c3c98bcf83).

  * Known issues:

    * [#263](https://github.com/google/mozc/issues/263): Voiced sound marks on the key pad is not placed at correct position in Android

    * [#273](https://github.com/google/mozc/issues/273): Compilation errors in Android arm64 and mips64 build

  * Fixed issues:

    * none

  * Total commits:

    * [28 commits](https://github.com/google/mozc/compare/20c1c08d7d4e89530e3e42db3476d682981c2b68...321e0656b0f2e233ab1c164bd86c58568c9e92f2).





2.16.2038.102 - 2.16.2072.102 / *2015-01-31* - *2015-03-15*

--------------------------------------------------

You can check out Mozc [2.16.2072.102](https://github.com/google/mozc/commit/20c1c08d7d4e89530e3e42db3476d682981c2b68) as follows.



```

gclient sync --revision=20c1c08d7d4e89530e3e42db3476d682981c2b68

```



Summary of changes between [2.16.2038.102](https://github.com/google/mozc/commit/6895df10f02dafb86150da8a3cc65f051f70e054) and [2.16.2072.102](https://github.com/google/mozc/commit/20c1c08d7d4e89530e3e42db3476d682981c2b68).



  * DEPS changes:

    * none

  * Build related changes:

    * [#286](https://github.com/google/mozc/issues/286): Clang 3.4 on Ubuntu 14.04 is used when building host binaries Mozc in Android, NaCl, and Linux desktop builds.  See [#286](https://github.com/google/mozc/issues/286) about why we have switched back to Clang 3.4 from Clang 3.5 on Ubuntu 14.04.

    * Pepper 40 SDK is required to build Mozc for NaCl.

    * Android 5.1 Lollipop SDK (or higher) is required to build Mozc for Android.

  * Major changes:

    * Target API level of Android binaries are incremented to 22, that is, `Build.VERSION_CODES.LOLLIPOP_MR1` a.k.a. Android 5.1.

    * LOUDS Trie engine was rewritten for better performance and maintainability.

    * `python build_mozc.py runtests` is now supported in Windows.

  * Known issues:

    * [#263](https://github.com/google/mozc/issues/263): Voiced sound marks on the key pad is not placed at correct position in Android

    * [#273](https://github.com/google/mozc/issues/273): Compilation errors in Android arm64 and mips64 build

  * Fixed issues:

    * [#286](https://github.com/google/mozc/issues/286): FIX: Build fails if clang-3.5 package is used in Ubuntu 14.04

  * Total commits:

    * [33 commits](https://github.com/google/mozc/compare/091dc3bafa1645432dd9b8ba1ba0f77645d39c1a...20c1c08d7d4e89530e3e42db3476d682981c2b68).





2.16.2021.102 - 2.16.2037.102 / *2015-01-24* - *2015-01-25*

--------------------------------------------------

You can check out Mozc [2.16.2037.102](https://github.com/google/mozc/commit/091dc3bafa1645432dd9b8ba1ba0f77645d39c1a) as follows.



```

gclient sync --revision=091dc3bafa1645432dd9b8ba1ba0f77645d39c1a

```



Summary of changes between [2.16.2021.102](https://github.com/google/mozc/commit/f78dad8d2c16d77f20577f04c2fa95ed85c386cb) and [2.16.2037.102](https://github.com/google/mozc/commit/091dc3bafa1645432dd9b8ba1ba0f77645d39c1a).



  * DEPS changes:

    * none

  * Build related changes:

    * libc++ is used by default to build Android target binaries.

    * [#276](https://github.com/google/mozc/issues/276): Clang 3.5 is now required to build Mozc for Android, NaCl, and Linux.

    * Visual C++ 2013 is required to build Mozc for Windows.

  * Major changes:

    * [#277](https://github.com/google/mozc/issues/277): Mozc for Windows now requires Windows Vista SP2 and later. Mozc [2.16.2034.102](https://github.com/google/mozc/commit/389932c227827de7fcd17a217de96c5b5a838672) is the last version that can run on Windows XP and Windows 2003 Server.

  * Known issues:

    * [#263](https://github.com/google/mozc/issues/263): Voiced sound marks on the key pad is not placed at correct position in Android

    * [#273](https://github.com/google/mozc/issues/273): Compilation errors in Android arm64 and mips64 build

  * Fixed issues:

    * [#274](https://github.com/google/mozc/issues/274): FIX: Inconsistency between suggestion candidates and conversion candidates

    * [#275](https://github.com/google/mozc/issues/275): FIX: Learning algorithm is sometimes too aggressive when punctuation is committed

    * [#276](https://github.com/google/mozc/issues/276): FIX: Require Clang to build Linux host binaries

    * [#277](https://github.com/google/mozc/issues/277): FIX: Discontinue the support of Windows XP/2003 Server

  * Total commits:

    * [17 commits](https://github.com/google/mozc/compare/5c96a77a0454f5877153d18d8a7ca5a5ddfb964b...091dc3bafa1645432dd9b8ba1ba0f77645d39c1a).





2.16.2008.102 - 2.16.2020.102 / *2015-01-01* - *2015-01-18*

--------------------------------------------------

You can check out Mozc [2.16.2020.102](https://github.com/google/mozc/commit/5c96a77a0454f5877153d18d8a7ca5a5ddfb964b) as follows.



```

gclient sync --revision=5c96a77a0454f5877153d18d8a7ca5a5ddfb964b

```



Summary of changes between [2.16.2008.102](https://github.com/google/mozc/commit/60de3075dde2ff1903aa820a7f9110455e3091c7) and [2.16.2020.102](https://github.com/google/mozc/commit/5c96a77a0454f5877153d18d8a7ca5a5ddfb964b).



  * DEPS changes:

    * protobuf: [bba83652e1be610bdb7ee1566ad18346d98b843c -> 172019c40bf548908ab09bfd276074c929d48415](https://github.com/google/protobuf/compare/172019c40bf548908ab09bfd276074c929d48415...bba83652e1be610bdb7ee1566ad18346d98b843c) (downgrading)

  * Build related changes:

    * Ubuntu 14.04 is used as the reference build/test environment for Android, `NaCl`, and Linux.  Hereafter we will not make sure that Mozc can be built on Ubuntu 12.04.

  * Known issues:

    * [#263](https://github.com/google/mozc/issues/263): Voiced sound marks on the key pad is not placed at correct position in Android

    * [#273](https://github.com/google/mozc/issues/273): Compilation errors in Android arm64 and mips64 build

  * Fixed issues:

    * [#265](https://github.com/google/mozc/issues/265): FIX: All resources are not released in Service.onDestory

    * [#266](https://github.com/google/mozc/issues/266): FIX: Many emojis are suggested from space

    * [#267](https://github.com/google/mozc/issues/267): FIX: Noisy candidate "itsumo" due to language aware conversion

    * [#269](https://github.com/google/mozc/issues/269): FIX: BuildInDocker fails when building for Android

    * [#271](https://github.com/google/mozc/issues/271): FIX: Runtime CHECK failure on Windows: protobuf/src/google/protobuf/descriptor.cc:1018

    * [#272](https://github.com/google/mozc/issues/272): FIX: `AssertionError` in `gen_zip_code_seed.py`

  * Total commits:

    * [13 commits](https://github.com/google/mozc/compare/1ffe8c9b56798baf6cac68a6dd6d539e0ccaad82...5c96a77a0454f5877153d18d8a7ca5a5ddfb964b).





2.16.2004.102 - 2.16.2007.102 / *2014-12-22* - *2014-12-24*

--------------------------------------------------

You can check out Mozc [2.16.2007.102](https://github.com/google/mozc/commit/1ffe8c9b56798baf6cac68a6dd6d539e0ccaad82) as follows.



```

gclient sync --revision=1ffe8c9b56798baf6cac68a6dd6d539e0ccaad82

```



Summary of changes between [2.16.2004.102](https://github.com/google/mozc/commit/70aa0ddaf4a1e57daccb10797d3afee433f174f6) and [2.16.2007.102](https://github.com/google/mozc/commit/1ffe8c9b56798baf6cac68a6dd6d539e0ccaad82).



  * DEPS changes:

    * fontTools: initial import as of [5ba7d98a4153fad57258fca23b0bcb238717aec3](https://github.com/googlei18n/fonttools/compare/a8f3feacb0e197c00f3f1c236777748a4dc6cf64...5ba7d98a4153fad57258fca23b0bcb238717aec3)

  * Build related changes:

    * Android build requires Android-21 SDK

  * Major changes:

    * Enable Material Theme on Android

    * Support floating window and floating mode indicator on Android 5.0 and later when physical keyboard is attached

    * Improve accessibility support on Android

  * Known issues:

    * [#263](https://github.com/google/mozc/issues/263): Voiced sound marks on the key pad is not placed at correct position in Android

  * Total commits:

    * [4 commits](https://github.com/google/mozc/compare/fe635d73050960cdfdb31a11dc3d08f636e14d49...1ffe8c9b56798baf6cac68a6dd6d539e0ccaad82).





2.16.1918.102 - 2.16.2003.102 / *2014-11-09* - *2014-12-21*

--------------------------------------------------

You can check out Mozc [2.16.2003.102](https://github.com/google/mozc/commit/fe635d73050960cdfdb31a11dc3d08f636e14d49) as follows.



```

gclient sync --revision=fe635d73050960cdfdb31a11dc3d08f636e14d49

```



Summary of changes between [2.16.1918.102](https://github.com/google/mozc/commit/b729086960878ccca5f2229a4fc9701e84093583) and [2.16.2003.102](https://github.com/google/mozc/commit/fe635d73050960cdfdb31a11dc3d08f636e14d49).



  * DEPS changes:

    * gtest: [r692 -> r700](https://code.google.com/p/googletest/source/list?start=700&num=9)

    * gmock: [r485 -> r501](https://code.google.com/p/googlemock/source/list?start=501&num=17)

    * gyp: [r1987 -> r2012](https://code.google.com/p/gyp/source/list?start=2012&num=26)

    * protobuf: [172019c40bf548908ab09bfd276074c929d48415 -> bba83652e1be610bdb7ee1566ad18346d98b843c](https://github.com/google/protobuf/compare/172019c40bf548908ab09bfd276074c929d48415...bba83652e1be610bdb7ee1566ad18346d98b843c)

  * Build related changes:

    * Android build requires NDK r10d

    * [#259](https://github.com/google/mozc/issues/259): Android build supports arm64/mips64/x86-64

    * [#260](https://github.com/google/mozc/issues/260): Android build supports Clang 3.5 and libc++

    * Versioning scheme for Android is changed. See r439 (on Google Code) for details.

    * Build time dependency on libzinnia-dev is removed from Android and NaCl builds

  * Major changes:

    * Android 2.1 - Android 3.2 are no longer supported

    * armeabi-v7a is always enabled in arm 32-bit build for Android

    * Updated main dictionary, Emoji dictionary, emoticon dictionary, and single kanji dictionary

  * Fixed issues:

    * [#248](https://github.com/google/mozc/issues/248): FIX: IME crashes when using US International hardware keyboard

    * [#255](https://github.com/google/mozc/issues/255): FIX: ibus-mozc + XIM: preedit text is not cleared after preedit commit triggered by focus change

    * [#257](https://github.com/google/mozc/issues/257): FIX: Entering symbol view causes NPE when "Switch Access" accessibility mode is enabled

    * [#261](https://github.com/google/mozc/issues/261): FIX: An empty word can be suggested in the candidate list

  * Total commits:

    * [87 commits](https://github.com/google/mozc/compare/026d814598ba223e3becc638b01c79935ea98ee2...fe635d73050960cdfdb31a11dc3d08f636e14d49).



---



Release History of Mozc 1.X

---------------------------



##1.0.558.102 - 1.15.1917.102 / *2010-12-09* - *2014-11-03*



**TODO: Import previous release notes here.**



Summary of changes between [1.0.558.102](https://github.com/google/mozc/commit/664029b064d23e0520309ec09d89ea5013783ce6) and [1.15.1917.102](https://github.com/google/mozc/commit/026d814598ba223e3becc638b01c79935ea98ee2).

  * Total commits:

    * [161 commits](https://github.com/google/mozc/compare/cae073cc74bc31625a659eb91e95d557cb2a6428...026d814598ba223e3becc638b01c79935ea98ee2).



---



Release History of Mozc 0.X

---------------------------



##0.11.347.100 - 0.13.523.102 / *2010-05-10* - *2010-11-02*



**TODO: Import previous release notes here.**



Summary of changes between [0.11.347.100](https://github.com/google/mozc/commit/0fdb7a7b04bdbbc640058e1856b278e668a69b1e) and [0.13.523.102](https://github.com/google/mozc/commit/cae073cc74bc31625a659eb91e95d557cb2a6428).

  * Total commits:

    * [17 commits](https://github.com/google/mozc/compare/1d6e951d92680d30e1a41c16e8fa74eed4039098...cae073cc74bc31625a659eb91e95d557cb2a6428).
