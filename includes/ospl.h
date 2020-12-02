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

/// Number of ospl verbs that are available
# define ARGS_COUNT 5
# define DATABASE_FILENAME "database.db"
# define DATABASE_NAME_LEN 12
# define LIBRARY_EXTENTION_LEN 5
# define LIBRARY_EXTENTION ".ospl"
# define VERSION_MAJOR "0"
# define VERSION_MINOR "1"
# define VERSION_REVISION "0"
# define CREATE_OPTS "v"
# define IMPORT_OPTS "vfF"
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

/*int ospl_import_folder(char *library, char *path);
int ospl_export_picture(char *library, unsigned id);
int ospl_export_album(char *library, unsigned id);
int ospl_album_create(char *library, unsigned id);
int ospl_album_rename(char *library, unsigned id, char *name);
int ospl_album_remove(char *library, unsigned id);
char *ospl_album_getname(char *library, unsigned id);
*/

// Common usage functions
int create_directory(char *path);
int copy_file(char* source, char* destination);
int file_exists(char *path);
int folder_exists(char *path);
int indexof(char *string, char character);
int is_supported(char *src);
int get_magic(char *file_path, char **magic);
int library_exists(char *path);

#endif