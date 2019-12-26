# Project
project('ospl', 'c')
cmake = import('cmake')

# Subprojects

thumbnailer_proj = subproject('thumbnailer')
thumbnailer = thumbnailer_proj.get_variable('thumbnailer_dep')
stockage_proj = subproject('stockage')
stockage = stockage_proj.get_variable('stockage_dep')

cwalk_proj = subproject('cwalk')
cwalk = cwalk_proj.get_variable('cwalk_dep')

#libcwalk = cmake.subproject('cwalk')

# Dependencies
deps = [thumbnailer,
		stockage,
		cwalk,
		dependency('libjpeg'),
		dependency('libexif'),
		dependency('threads'),
		dependency('sqlite3'),
		meson.get_compiler('c').find_library('magic')]

source =['srcs/ospl.c', 'srcs/common.c', 
		'srcs/action/create.c',
		'srcs/action/import.c',
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
