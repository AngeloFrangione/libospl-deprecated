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

#include <errno.h>
#include <stockage.h>
#include <cwalk.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "ospl.h"

static int create_database_file(char *path)
{
	char tmp[PATH_LEN_BUFFER] = {0};
	t_db db;

	cwk_path_join(path, DATABASE_FILENAME, tmp, sizeof(tmp));
	db.path = tmp;

	if (create_database(tmp) | db_insert_setting(&db, "version", VERSION_MAJOR"."VERSION_MINOR"."VERSION_REVISION))
	 return ERR_DB;
	return 0;
}

int ospl_create_library(char *path)
{
	int ret = 0;
	char tmp[PATH_LEN_BUFFER] = { 0 };

	ret |= create_directory(path);
	cwk_path_join(path, "photos", tmp, sizeof(tmp));
	ret |= create_directory(tmp);
	cwk_path_join(tmp, "import", tmp, sizeof(tmp));
	ret |= create_directory(tmp);
	cwk_path_join(path, "thumbnails", tmp, sizeof(tmp));
	ret |= create_directory(tmp);

	if (ret < 0)
	{
		remove_dir(path);
		return -1000 - errno;
	}
	if (create_database_file(path) < 0)
	{
		remove_dir(path);
		return ERR_DB;
	}
	return 0;
}
