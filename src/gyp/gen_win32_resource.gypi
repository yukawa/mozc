{
  'type': 'none',
  'toolsets': ['host'],
  'dependencies': [
    '<(DEPTH)/win32/base/win32_base.gyp:gen_win32_resource_main#host',
  ],
  'actions': [
    {
      'action_name': 'gen_win32_resource',
      'variables': {
        'generator': '<(PRODUCT_DIR)/gen_win32_resource_main<(EXECUTABLE_SUFFIX)',
        'rc_file': '<(gen_out_dir)/<(gen_output_resource_path)',
      },
      'inputs': [
        '<(gen_main_resource_path)',
      ],
      'outputs': [
        '<(rc_file)',
      ],
      'action': [
        '<(generator)',
        '--proto_file=<(DEPTH)/win32/broker/<(gen_main_resource_path)',
        '--output_file=<(rc_file)',
      ],
      'message': 'Generating resource for <(gen_resource_proj_name).',
    },
  ],
}
