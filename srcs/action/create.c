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
	int r = 0;
	char tmp[4096] = {0};
	t_db db;

	cwk_path_join(path, DATABASE_FILENAME, tmp, sizeof(tmp));
	r = create_database(tmp);
	if (r)
	 return -1;
	db.path = tmp;
	r = db_insert_setting(&db, "version", VERSION_MAJOR"."VERSION_MINOR"."VERSION_REVISION);
	if (r)
		return -1;
	return 0;
}

int ospl_create_library(char *path)
{
	int r;
	char tmp[4096] = { 0 };

	if (folder_exists(path))
		return EAEXISTS;
	else
		r = create_directory(path);
	if (r)
		return EERRNO;
	cwk_path_join(path, "photos", tmp, sizeof(tmp));
	r = create_directory(tmp);
	if (r < 0)
	{
		remove_dir(path);
		return EERRNO;
	}
	cwk_path_join(tmp, "import", tmp, sizeof(tmp));
	r = create_directory(tmp);
	if (r < 0)
	{
		remove_dir(path);
		return EERRNO;
	}
	cwk_path_join(path, "thumbnails", tmp, sizeof(tmp));
	r = create_directory(tmp);
	if (r)
	{
		remove_dir(path);
		return EERRNO;
	}
	r = create_database_file(path);
	if (r)
		return EDBFAIL;
	return 0;
}
