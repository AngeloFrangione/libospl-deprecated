# Project
project('stockage', 'c')

# Dependencies
deps = [dependency('sqlite3')]

# Sources
source =['src/stockage.c']

# Library
cargs =['-Wall', '-Wextra', '-Wno-unused-parameter', '-Wno-restrict']
stockage = shared_library(	'stockage', source,
						            install: true,
						            include_directories : 'include',
					             	dependencies : deps,
						            soversion: 0, version: '0.0.1',
						            c_args: cargs
)

install_headers('include/stockage.h',  subdir : 'ospl')

stockage_dep = declare_dependency(include_directories: 'include', link_with: stockage)
