# Project
project('thumbnailer', 'c')

# Dependencies
deps = [dependency('libjpeg'),
		dependency('libexif'),
		dependency('threads'),
		dependency('sqlite3'),
		meson.get_compiler('c').find_library('magic')]

# Library
thumbnailer = shared_library(	'thumbnailer', 'src/thumbnailer.c', 'src/epeg.c',
						            install: true,
						            include_directories : 'include',
					             	dependencies : deps,
						            soversion: 0, version: '0.0.1'
)

install_headers('include/thumbnailer.h',  subdir : 'ospl')
install_headers('include/epeg.h',  subdir : 'ospl')

# CLI
executable( 'cli', 'main.c', 
			link_with: thumbnailer, 
			dependencies : deps
)

thumbnailer_dep = declare_dependency(include_directories: 'include', link_with: thumbnailer)
