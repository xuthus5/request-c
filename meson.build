project('request-c', 'c', version: '0.1', license: 'MIT', meson_version: '>=0.46', default_options: ['c_std=gnu99'],)

cc = meson.get_compiler('c')

add_project_arguments('-D_GNU_SOURCE', language: 'c')
if cc.has_argument('-Wno-unused')
  add_project_arguments('-Wno-unused', language: 'c')
endif

curl = dependency('libcurl', required: true)

public_headers = [
  'request.h',
]

sources = [
  'request.c',
]

librequest_c = library(meson.project_name(), public_headers, sources,
  install: true,
)

librequest_c_dep = declare_dependency(
  link_with: librequest_c,
  include_directories: include_directories('.'),
  dependencies: [curl],
  sources: public_headers,
)

header_subdir = 'request-c'
install_headers(public_headers, subdir: header_subdir)

pkgconfig = import('pkgconfig')
pkgconfig.generate(librequest_c,
  description: 'A request library implementation in C',
  version: meson.project_version(),
  filebase: meson.project_name(),
  name: meson.project_name(),
  subdirs: header_subdir,
)