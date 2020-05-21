# Project
project('stockage', 'c')

# Dependencies
deps = [dependency('threads'),
		dependency('sqlite3')]

# Sources
source =['src/stockage.c',
		'src/queries/settings.c']

# Library
stockage = shared_library(	'stockage', source,
						            install: true,
						            include_directories : 'include',
					             	dependencies : deps,
						            soversion: 0, version: '0.0.1'
)

install_headers('include/stockage.h',  subdir : 'ospl')

# CLI
executable( 'cli', 'main.c', 
			link_with: stockage, 
			dependencies : deps
)

stockage_dep = declare_dependency(include_directories: 'include', link_with: stockage)
