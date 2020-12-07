# Project
project('ospl', 'c')
cmake = import('cmake')

# Enable debugging
add_global_arguments('-DDEBUG=TRUE', language: 'c')

# Subprojects
thumbnailer_proj = subproject('thumbnailer')
thumbnailer = thumbnailer_proj.get_variable('thumbnailer_dep')
stockage_proj = subproject('stockage')
stockage = stockage_proj.get_variable('stockage_dep')
md5_proj = subproject('md5')
md5 = md5_proj.get_variable('md5_dep')

cwalk_proj = subproject('cwalk')
cwalk = cwalk_proj.get_variable('cwalk_dep')

# Dependencies
deps = [thumbnailer,
		stockage,
		cwalk,
		md5,
		dependency('threads'),
		meson.get_compiler('c').find_library('m'),
		meson.get_compiler('c').find_library('magic')]


source =['srcs/ospl.c', 'srcs/common.c', 
		'srcs/action/create.c',
		'srcs/action/import.c',
		'srcs/action/albums.c',
		'srcs/action/export.c']

# Library
ospl = shared_library(	'ospl', source,
						install: true,
						include_directories : 'includes',
						dependencies : deps,
						soversion: 0, version: '0.0.1'
)

install_headers('includes/ospl.h', subdir : 'ospl')

# CLI
executable(	'ospl', 'cli.c',
			link_with: ospl,
			dependencies : deps
)
