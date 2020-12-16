/*	libospl - Open Source Photo Library
	an opensource and multiplateform photo library management that can be used
	to store and sort all your pictures.
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
# define VERSION_REVISION "0"

# define SUPPORTED_IMAGES (char *[]) {"image/jpeg"}
# define NB_SUPPORTED_IMAGES 1
# define TRUE 1
# define FALSE 0

// Future maybe settings
# define THUMB_HEIGHT 500

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


// Library related functions
int ospl_create_library(char *library);
int ospl_import_picture(char *library, char *path);
/*
** int ospl_import_folder(char *library, char *path);
*/
int ospl_list_albums(char *library, t_album *list);
int ospl_album_listpic(char *library, int album, uint32_t *list);
int ospl_album_assocpic(char *library, int photo, uint32_t *list);
int ospl_create_album(char *library, char *name);
int ospl_rename_album(char *library, int id, char *name);
int ospl_delete_album(char *library, int id);
int ospl_album_addpic(char *library, int photo, int album);
int ospl_album_delpic(char *library, int photo, int album);
int ospl_album_movepic(char *library, int photo, int old, int new);
int ospl_picture_get(char *library, int id, t_photos *list);
int ospl_picture_list(char *library, t_photos *list);
int ospl_picture_delete(char *library, int id);


// Common usage functions
void fill_tdb(t_db *db, char *library);
int create_directory(char *path);
int copy_file(char* source, char* destination);
int file_exists(char *path);
int folder_exists(char *path);
int indexof(char *string, char character);
int is_supported(char *src);
int get_magic(char *file_path, char **magic);
int library_exists(char *path);

#endif