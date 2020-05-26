# Project
project('md5', 'c')


# Library
md5 = shared_library('md5', 'src/md5.c', 'src/wrapper.c',
								install: true,
								include_directories : 'include',
								soversion: 0, version: '0.0.1'
)

install_headers('include/md5.h',  subdir : 'ospl')

# CLI
executable( 'cli', 'main.c', 
			link_with: md5
)

md5_dep = declare_dependency(include_directories: 'include', link_with: md5)
