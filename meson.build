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
		'srcs/db/database_albums.c',
		'srcs/db/database_settings.c',
		'srcs/db/database_photos.c',
		'srcs/action/create.c',
		'srcs/action/import.c',
		'srcs/action/photo.c',
		'srcs/action/albums.c',
		'srcs/action/export.c']

# Library
cargs =['-Wall', '-Wextra', '-Wno-unused-parameter']
ospl = shared_library(	'ospl', source,
						install: true,
						include_directories : 'includes',
						dependencies : deps,
						soversion: 0, version: '0.0.1',
						c_args: cargs
)

install_headers('includes/ospl.h', subdir : 'ospl')

# CLI
executable(	'ospl', 'cli.c',
			link_with: ospl,
			dependencies : deps
)

# TESTS
test_1_create_lib = executable('test_1_create_lib', 'test_files/test_1_create_lib.c', link_with: ospl, dependencies : deps)
test_2_import = executable('test_import', 'test_files/test_2_import.c', link_with: ospl, dependencies : deps)
test_3_create_alb = executable('test_3_create_alb', 'test_files/test_3_create_alb.c', link_with: ospl, dependencies : deps)
test_4_import_in_album = executable('test_4_import_in_album', 'test_files/test_4_import_in_album.c', link_with: ospl, dependencies : deps)
test_5_import_folder = executable('test_5_import_folder', 'test_files/test_5_import_folder.c', link_with: ospl, dependencies : deps)
test_6_import_folder_in_album = executable('test_6_import_folder_in_album', 'test_files/test_6_import_folder_in_album.c', link_with: ospl, dependencies : deps)
test_7_rename_alb = executable('test_7_rename_alb', 'test_files/test_7_rename_alb.c', link_with: ospl, dependencies : deps)
test_8_delete_alb = executable('test_8_delete_alb', 'test_files/test_8_delete_alb.c', link_with: ospl, dependencies : deps)
test_9_alb_del_photo = executable('test_9_alb_del_photo', 'test_files/test_9_alb_del_photo.c', link_with: ospl, dependencies : deps)
test_10_alb_mov_photo = executable('test_10_alb_mov_photo', 'test_files/test_10_alb_mov_photo.c', link_with: ospl, dependencies : deps)
test_11_del_photo = executable('test_11_del_photo', 'test_files/test_11_del_photo.c', link_with: ospl, dependencies : deps)
test_12_list_albums = executable('test_12_list_albums', 'test_files/test_12_list_albums.c', link_with: ospl, dependencies : deps)


test('1_create_lib', test_1_create_lib)
test('2_import', test_2_import)
test('3_create_alb', test_3_create_alb)
test('4_import_in_album', test_4_import_in_album)
test('5_import_folder', test_5_import_folder)
test('6_import_folder_in_album', test_6_import_folder_in_album)
test('7_rename_alb', test_7_rename_alb)
test('8_delete_alb', test_8_delete_alb)
test('9_alb_del_photo', test_9_alb_del_photo)
test('10_alb_mov_photo', test_10_alb_mov_photo)
test('11_del_photo', test_11_del_photo)
test('12_list_albums', test_12_list_albums)
