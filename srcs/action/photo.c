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
#if defined(_WIN32)
# include <windows.h>
# endif
#include <stdio.h>
#include <string.h>
#include <ospl.h>
#include <cwalk.h>
#include <stockage.h>
#include <errno.h>

int ospl_photo_get(char *library, int photo, t_photos *info)
{
	t_db db = {0};

	fill_tdb(&db, library);
	if (db_select_photo(&db, photo, info))
		return ERR_DB;
	if (info->id == 0)
		return ERR_PHO_NF;
	return SUCCESS;
}

int ospl_photo_list(char *library, t_photos *list)
{
	t_db db = {0};

	fill_tdb(&db, library);
	if (db_select_photo_all(&db, list))
		return ERR_DB;
	return SUCCESS;
}

int ospl_photo_delete(char *library, int photo)
{
	int t = 0;
	t_db db = { 0 };
	t_photos pho = { 0 };
	char tmp_import[PATH_LEN_BUFFER] = { 0 };
	char tmp_thumb[PATH_LEN_BUFFER] = { 0 };

	fill_tdb(&db, library);
	if (db_select_photo(&db, photo, &pho) || !(t = 1) || !pho.id ||
		db_delete_photo(&db, photo))
		return (t) ? ERR_PHO_NF : ERR_DB;
	cwk_path_join(library, "photos/import", tmp_import, sizeof(tmp_import));
	cwk_path_join(library, "thumbnails", tmp_thumb, sizeof(tmp_thumb));
	cwk_path_join(tmp_import, pho.new_name, tmp_import, sizeof(tmp_import));
	cwk_path_join(tmp_thumb, pho.new_name, tmp_thumb, sizeof(tmp_thumb));
	#ifdef _WIN32
		if (!DeleteFileA(tmp_import))
			return ERR_WIN_REM;
		if (!DeleteFileA(tmp_thumb))
			return ERR_WIN_REM;
	#else
		if (remove(tmp_import) || remove(tmp_thumb))
			return -1000 - errno;
	#endif
	return SUCCESS;
}
