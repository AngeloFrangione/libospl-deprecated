# Project
project('ospl', 'c', version : '0.1.1')
cmake = import('cmake')

run_target('empty_files',
  command : 'scripts/create_emptyfiles.sh')

run_target('copy_dlls',
	command: 'scripts/copy_dlls.sh')

# Enable debugging
add_global_arguments('-DDEBUG=TRUE', language: 'c')

# Subprojects
stockage_proj = subproject('stockage')
stockage = stockage_proj.get_variable('stockage_dep')
md5_proj = subproject('md5')
md5 = md5_proj.get_variable('md5_dep')
thumbnailer_proj = subproject('thumbnailer')
thumbnailer = thumbnailer_proj.get_variable('thumbnailer_dep')

cwalk_proj = subproject('cwalk')
cwalk = cwalk_proj.get_variable('cwalk_dep')

# Dependencies
deps = [stockage,
		cwalk,
		md5,
		dependency('threads'),
		thumbnailer,
		meson.get_compiler('c').find_library('m')]

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
cargs =['-Wall', '-Wextra', '-Wno-unused-parameter', '-Wno-restrict']
ospl = shared_library(	'ospl', source,
						install: true,
						include_directories : 'includes',
						dependencies : deps,
						soversion: 0, version: '0.1.1',
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
test_2_fail_create_lib = executable('test_2_fail_create_lib', 'test_files/test_2_fail_create_lib.c', link_with: ospl, dependencies : deps)
test_3_import = executable('test_3_import', 'test_files/test_3_import.c', link_with: ospl, dependencies : deps)
test_4_fail_import = executable('test_4_fail_import', 'test_files/test_4_fail_import.c', link_with: ospl, dependencies : deps)
test_5_create_alb = executable('test_5_create_alb', 'test_files/test_5_create_alb.c', link_with: ospl, dependencies : deps)
test_6_fail_create_alb = executable('test_6_fail_create_alb', 'test_files/test_6_fail_create_alb.c', link_with: ospl, dependencies : deps)
test_7_import_in_album = executable('test_7_import_in_album', 'test_files/test_7_import_in_album.c', link_with: ospl, dependencies : deps)
test_8_fail_import_in_album = executable('test_8_fail_import_in_album', 'test_files/test_8_fail_import_in_album.c', link_with: ospl, dependencies : deps)
test_9_import_folder = executable('test_9_import_folder', 'test_files/test_9_import_folder.c', link_with: ospl, dependencies : deps)
test_10_fail_import_folder = executable('test_10_fail_import_folder', 'test_files/test_10_fail_import_folder.c', link_with: ospl, dependencies : deps)
test_11_import_folder_in_album = executable('test_11_import_folder_in_album', 'test_files/test_11_import_folder_in_album.c', link_with: ospl, dependencies : deps)
test_12_fail_import_folder_in_album = executable('test_12_fail_import_folder_in_album', 'test_files/test_12_fail_import_folder_in_album.c', link_with: ospl, dependencies : deps)
test_13_rename_alb = executable('test_13_rename_alb', 'test_files/test_13_rename_alb.c', link_with: ospl, dependencies : deps)
test_14_fail_rename_alb = executable('test_14_fail_rename_alb', 'test_files/test_14_fail_rename_alb.c', link_with: ospl, dependencies : deps)
test_15_delete_alb = executable('test_15_delete_alb', 'test_files/test_15_delete_alb.c', link_with: ospl, dependencies : deps)
test_16_fail_delete_alb = executable('test_16_fail_delete_alb', 'test_files/test_16_fail_delete_alb.c', link_with: ospl, dependencies : deps)
test_17_alb_del_photo = executable('test_17_alb_del_photo', 'test_files/test_17_alb_del_photo.c', link_with: ospl, dependencies : deps)
test_18_fail_alb_del_photo = executable('test_18_fail_alb_del_photo', 'test_files/test_18_fail_alb_del_photo.c', link_with: ospl, dependencies : deps)
test_19_alb_mov_photo = executable('test_19_alb_mov_photo', 'test_files/test_19_alb_mov_photo.c', link_with: ospl, dependencies : deps)
test_20_fail_alb_mov_photo = executable('test_20_fail_alb_mov_photo', 'test_files/test_20_fail_alb_mov_photo.c', link_with: ospl, dependencies : deps)
test_21_del_photo = executable('test_21_del_photo', 'test_files/test_21_del_photo.c', link_with: ospl, dependencies : deps)
test_22_fail_del_photo = executable('test_22_fail_del_photo', 'test_files/test_22_fail_del_photo.c', link_with: ospl, dependencies : deps)
test_23_list_albums = executable('test_23_list_albums', 'test_files/test_23_list_albums.c', link_with: ospl, dependencies : deps)
test_24_fail_list_albums = executable('test_24_fail_list_albums', 'test_files/test_24_fail_list_albums.c', link_with: ospl, dependencies : deps)
test_25_32k_files_import = executable('test_25_32k_files_import', 'test_files/test_25_32k_files_import.c',link_with: ospl, dependencies : deps)

test('1_create_lib', test_1_create_lib)
test('2_fail_create_lib', test_2_fail_create_lib, should_fail: true)
test('3_import', test_3_import)
test('4_fail_import', test_4_fail_import, should_fail: true)
test('5_create_alb', test_5_create_alb)
test('6_fail_create_alb', test_6_fail_create_alb, should_fail: true)
test('7_import_in_album', test_7_import_in_album)
test('8_fail_import_in_album', test_8_fail_import_in_album, should_fail: true)
test('9_import_folder', test_9_import_folder)
test('10_fail_import_folder', test_10_fail_import_folder, should_fail: true)
test('11_import_folder_in_album', test_11_import_folder_in_album)
test('12_fail_import_folder_in_album', test_12_fail_import_folder_in_album, should_fail: true)
test('13_rename_alb', test_13_rename_alb)
test('14_fail_rename_alb', test_14_fail_rename_alb, should_fail: true)
test('15_delete_alb', test_15_delete_alb)
test('16_fail_delete_alb', test_16_fail_delete_alb, should_fail: true)
test('17_alb_del_photo', test_17_alb_del_photo)
test('18_fail_alb_del_photo', test_18_fail_alb_del_photo, should_fail: true)
test('19_alb_mov_photo', test_19_alb_mov_photo)
test('19_fail_alb_mov_photo', test_20_fail_alb_mov_photo, should_fail: true)
test('21_del_photo', test_21_del_photo)
test('22_fail_del_photo', test_22_fail_del_photo, should_fail: true)
test('23_list_albums', test_23_list_albums)
test('24_fail_list_albums', test_24_fail_list_albums, should_fail: true)
test('25_32k_files_import', test_25_32k_files_import, timeout: 60)
