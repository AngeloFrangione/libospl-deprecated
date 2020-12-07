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

#include <errno.h>
#include <stockage.h>
#include <cwalk.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "ospl.h"

static int create_folder(char *path)
{
	if (folder_exists(path))
	{
		errno = EEXIST;
		return 1;
	}
	else
		return create_directory(path);
}

static int create_database_file(char *path)
{
	int r = 0;
	char tmp[4096] = {0};
	t_db db;

	cwk_path_join(path, DATABASE_FILENAME, tmp, sizeof(tmp));
	r = create_database(tmp);
	db.path = tmp;
	r = r & insert_setting(&db, "version", VERSION_MAJOR"."VERSION_MINOR"."VERSION_REVISION);
	return r;
}

/**
  * \brief Creates an OSPL library
  *
  * \param path new library path
  * \return 0 with success and 1 when an error occurs
  */
int ospl_create_library(char *path)
{
	int r;
	char tmp[4096] = { 0 };

	r = create_folder(path);
	cwk_path_join(path, "pictures", tmp, sizeof(tmp));
	r = r & create_folder(tmp);
	cwk_path_join(tmp, "import", tmp, sizeof(tmp));
	r = r & create_folder(tmp);
	cwk_path_join(path, "thumbnails", tmp, sizeof(tmp));
	r = r & create_folder(tmp);
	if (r)
		return r;
	return create_database_file(path);
}
