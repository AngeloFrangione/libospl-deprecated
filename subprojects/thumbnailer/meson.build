# Project
project('thumbnailer', 'c')


# Subprojects
exif_proj = subproject('libexif')
exif = exif_proj.get_variable('exif_dep')

if not meson.is_cross_build()
	cc = meson.get_compiler('c')
	magic = cc.find_library('magic', required : false)
endif

# Dependencies
if meson.is_cross_build()
	deps = [dependency('libjpeg'), exif]
else
	deps = [dependency('libjpeg'), exif, magic]
endif




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

# CLI
executable(	'cli', ['cli.c'],
			link_with: thumbnailer,
			dependencies : deps
)

thumbnailer_dep = declare_dependency(include_directories: 'include', link_with: thumbnailer)
