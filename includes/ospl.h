/*	libospl - Open Source Photo Library
	an opensource and multiplateform photo library management that can be used
	to store and sort all your photos.
	Copyright (C) 2019-2020 Angelo Frangione

	This program is free software; you can redistribute it and/or modify
	it under the terms of the GNU General Public License as published by
	the Free Software Foundation; either version 2 of the License, or
	(at your option) any later version.

	This program is distributed in the hope that it will be useful,
	but WITHOUT ANY WARRANTY; without even the implied warranty of
	MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
	GNU General Public License for more details.

	You should have received a copy of the GNU General Public License along
	with this program; if not, write to the Free Software Foundation, Inc.,
	51 Franklin Street, Fifth Floor, Boston, MA 02110-1301 USA.
*/

#ifndef OSPL_H
#define OSPL_H

# include <stockage.h>

# define DATABASE_FILENAME "database.db"
# define DATABASE_NAME_LEN 12
# define LIBRARY_EXTENTION_LEN 5
# define LIBRARY_EXTENTION ".ospl"
# define VERSION_MAJOR "0"
# define VERSION_MINOR "1"
# define VERSION_REVISION "1"

# define SUPPORTED_IMAGES (char *[]) {"image/jpeg"}
# define NB_SUPPORTED_IMAGES 1
# define TRUE 1
# define FALSE 0
# define PATH_LEN_BUFFER 4096

// Future maybe settings
# define THUMB_HEIGHT 500

enum SUCCESS
{
	SUCCESS = 0
};

enum ERRORS
{
	ERR_OTHER = -1000,	// other error
	ERR_EXISTS,			// the file or folder already exists
	ERR_DB,				// database communication failed
	ERR_NOT_FOUND,		// element not found
	ERR_NOT_SUPPORTED,	// element not supported
	ERR_THUMB,			// thumbnail creation failed
	ERR_PHO_NF,			// photo not found in db
	ERR_ALB_NF,			// album not found in db
};

typedef struct	s_current_time
{
	unsigned int Y;
	unsigned int M;
	unsigned int d;
	unsigned int h;
	unsigned int m;
	unsigned int s;
	unsigned int ms;
}				t_current_time;


// External functions
char *enum_error(int error_code);

// Library related functions
int ospl_create_library(char *library);
int ospl_import_photo(char *library, char *path);
int ospl_import_photo_in_album(char *library, char *path, int album);
int ospl_import_folder(char *library, char *path);
int ospl_import_folder_in_album(char *library, char *path, int album);
int ospl_album_list(char *library, t_album *list);
int ospl_album_list_photos(char *library, int album, t_photos *list);
int ospl_album_create(char *library, char *name);
int ospl_album_rename(char *library, int album, char *name);
int ospl_album_delete(char *library, int album);
int ospl_album_add_photo(char *library, int photo, int album);
int ospl_album_delete_photo(char *library, int photo, int album);
int ospl_album_move_photo(char *library, int photo, int old, int new);
int ospl_photo_associated_album(char *library, int photo, t_album *list);
int ospl_photo_get(char *library, int photo, t_photos *photos);
int ospl_photo_list(char *library, t_photos *list);
int ospl_photo_delete(char *library, int photo);


///// Database common usage function
/// PHOTOS ///
int db_insert_photo(t_db *db, t_photos *pho);
int db_select_photo(t_db *db, int id, t_photos *pho);
int db_select_photo_multiple(t_db *db, int id, t_photos *pho);
int db_select_photo_all(t_db *db, t_photos *phos);
int db_delete_photo(t_db *db, int id);
int db_update_photo_null(t_db *db, int id, char *col);
int db_update_photo_int(t_db *db, int id, char *col, int value);
int db_update_photo_char(t_db *db, int id, char *col, char *value);
/// SETTINGS/ ///
int db_insert_setting(t_db *db, char *name, char *value);
int db_update_setting(t_db *db, char *name, char *value);
int db_select_setting(t_db *db, char *name, char *value);
int db_delete_setting(t_db *db, char *name);
/// ALBUMS ///
int db_create_album(t_db *db, char *name);
int db_rename_album(t_db *db, int id, char *name);
int db_delete_album(t_db *db, int id);
int db_insert_contains(t_db *db, int photo, int album);
int db_delete_contains(t_db *db, int photo, int album);
int db_move_contains(t_db *db, int photo, int old_album, int new_album);
int db_list_contains(t_db *db, int album, t_photos *list);
int db_photo_contained(t_db *db, int pho, t_album *list);
int db_list_albums(t_db *db, t_album *list);
int db_select_album(t_db *db, int id, t_album *album);

// Common usage functions
void fill_tdb(t_db *db, char *library);
int hard_link(char *current, char * new);
int create_directory(char *path);
int copy_file(char* source, char* destination);
int file_exists(char *path);
int folder_exists(char *path);
int is_supported(char *src);
int get_magic(char *file_path, char **magic);
int library_exists(char *path);
int remove_dir(char *path);

#endif
