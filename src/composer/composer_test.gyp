# Copyright 2010-2021, Google Inc.
# All rights reserved.
#
# Redistribution and use in source and binary forms, with or without
# modification, are permitted provided that the following conditions are
# met:
#
#     * Redistributions of source code must retain the above copyright
# notice, this list of conditions and the following disclaimer.
#     * Redistributions in binary form must reproduce the above
# copyright notice, this list of conditions and the following disclaimer
# in the documentation and/or other materials provided with the
# distribution.
#     * Neither the name of Google Inc. nor the names of its
# contributors may be used to endorse or promote products derived from
# this software without specific prior written permission.
#
# THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
# "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
# LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
# A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT
# OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
# SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
# LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
# DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
# THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
# (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
# OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.

{
  'targets': [
    {
      'target_name': 'composer_test',
      'type': 'executable',
      'sources': [
        'char_chunk_test.cc',      
        'composer_test.cc',
        'composition_input_test.cc',
        'composition_test.cc',
        'mode_switching_handler_test.cc',
        'special_key_test.cc',
        'transliterators_test.cc',
        'table_test.cc',
      ],
      'dependencies': [
        '<(mozc_oss_src_dir)/base/absl.gyp:absl_strings',
        '<(mozc_oss_src_dir)/base/base_test.gyp:clock_mock',
        '<(mozc_oss_src_dir)/config/config.gyp:config_handler',
        '<(mozc_oss_src_dir)/data_manager/testing/mock_data_manager.gyp:mock_data_manager',
        '<(mozc_oss_src_dir)/protocol/protocol.gyp:commands_proto',
        '<(mozc_oss_src_dir)/protocol/protocol.gyp:config_proto',
	'<(mozc_oss_src_dir)/request/request.gyp:request_test_util',
        '<(mozc_oss_src_dir)/testing/testing.gyp:gtest_main',
        'composer.gyp:composer',
      ],
      'variables': {
        'test_size': 'small',
      },
    },
    {
      'target_name': 'key_event_util_test',
      'type': 'executable',
      'sources': [
        'key_event_util_test.cc',
      ],
      'dependencies': [
        '<(mozc_oss_src_dir)/base/absl.gyp:absl_strings',
        '<(mozc_oss_src_dir)/base/base.gyp:base',
        '<(mozc_oss_src_dir)/config/config.gyp:config_handler',
        '<(mozc_oss_src_dir)/testing/testing.gyp:gtest_main',
        'composer.gyp:key_event_util',
        'composer.gyp:key_parser',
      ],
      'variables': {
        'test_size': 'small',
      },
    },
    {
      'target_name': 'key_parser_test',
      'type': 'executable',
      'sources': [
        'key_parser_test.cc',
      ],
      'dependencies': [
        '<(mozc_oss_src_dir)/base/base.gyp:base',
        '<(mozc_oss_src_dir)/config/config.gyp:config_handler',
        '<(mozc_oss_src_dir)/testing/testing.gyp:gtest_main',
        'composer.gyp:key_event_util',
        'composer.gyp:key_parser',
      ],
      'variables': {
        'test_size': 'small',
      },
    },
    # Test cases meta target: this target is referred from gyp/tests.gyp
    {
      'target_name': 'composer_all_test',
      'type': 'none',
      'dependencies': [
        'composer_test',
        'key_event_util_test',
        'key_parser_test',
      ],
    },
  ],
}

