project('request_c', 'c', 
  version: '0.1', 
  license: 'MIT', 
  meson_version: '>=0.50', 
  default_options: ['c_std=gnu11'],
)

cc = meson.get_compiler('c')

add_project_arguments('-D_GNU_SOURCE', language: 'c')
if cc.has_argument('-Wno-unused')
  add_project_arguments('-Wno-unused', language: 'c')
endif

public_headers = include_directories('.')

sources_headers = [
  'request.h',
]

sources = [
  'request.c',
]

libcurl_dep = dependency('libcurl')

project_target = static_library(
  meson.project_name(),
  sources,
  install : true,
  gnu_symbol_visibility : 'hidden',
  include_directories : public_headers,
  dependencies: libcurl_dep,
)

project_dep = declare_dependency(
  include_directories: public_headers,
  link_with : project_target
)
set_variable(meson.project_name() + '_dep', project_dep)

install_headers(sources_headers, subdir: meson.project_name())

pkgconfig = import('pkgconfig')
pkgconfig.generate(
  description: 'A request library implementation in C',
  version: meson.project_version(),
  filebase: meson.project_name(),
  name: meson.project_name(),
  subdirs: meson.project_name(),
  libraries : project_target,
)