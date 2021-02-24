# Project
project('thumbnailer', 'c')

# Dependencies
deps = [dependency('libjpeg'),
		dependency('libexif'),
		meson.get_compiler('c').find_library('magic')]

# Library
cargs =['-Wall', '-Wextra', '-Wno-unused-parameter', '-Wno-restrict', '-Wno-sign-compare']
thumbnailer = shared_library(	'thumbnailer', 'src/thumbnailer.c', 'src/epeg.c',
						            install: true,
						            include_directories : 'include',
					             	dependencies : deps,
						            soversion: 0, version: '0.0.1',
						            c_args: cargs
)

install_headers('include/thumbnailer.h',  subdir : 'ospl')
install_headers('include/epeg.h',  subdir : 'ospl')

thumbnailer_dep = declare_dependency(include_directories: 'include', link_with: thumbnailer)
