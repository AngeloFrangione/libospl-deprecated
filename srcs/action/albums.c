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

#include <string.h>
#include <stdio.h>
#include <ospl.h>
#include <cwalk.h>
#include <stockage.h>

int ospl_list_albums(char *library, t_album *list)
{
	t_db db = {0};

	fill_tdb(&db, library);
	if (list_albums(&db, list))
		return EDBFAIL;
	return SUCCESS;
}

int ospl_album_listpic(char *library, int album, uint32_t *list)
{
	t_db db = {0};

	fill_tdb(&db, library);
	if (list_contains(&db, album, list))
		return EDBFAIL;
	return SUCCESS;
}

int ospl_album_assocpic(char *library, int photo, uint32_t *list)
{
	t_db db = {0};

	fill_tdb(&db, library);
	if (photo_contained(&db, photo, list))
		return EDBFAIL;
	return SUCCESS;
}

int ospl_create_album(char *library, char *name)
{
	t_db db = {0};
	char tmp[512] = {0};

	cwk_path_join(library, "/pictures/", tmp, sizeof(tmp));
	cwk_path_join(tmp, name, tmp, sizeof(tmp));
	fill_tdb(&db, library);
	if(folder_exists(tmp))
		return EAEXISTS;
	if (create_album(&db, name))
		return EDBFAIL;
	if (!create_directory(tmp))
		return SUCCESS;
	else
		return EERRNO;
}

int ospl_rename_album(char *library, int id, char *name)
{
	t_db db = {0};

	fill_tdb(&db, library);
	if (rename_album(&db, id, name))
		return EDBFAIL;
	return SUCCESS;
}

int ospl_delete_album(char *library, int id)
{
	t_db db = {0};
	char tmp[512] = { 0 };
	t_album album = { 0 };

	fill_tdb(&db, library);
	if(select_album(&db, id, &album))
		return EDBFAIL;
	if (!album.id)
		return ENOTFOUND;
	cwk_path_join(library, "/pictures/", tmp, sizeof(tmp));
	cwk_path_join(tmp, album.name, tmp, sizeof(tmp));
	if(!delete_album(&db, id))
		remove_dir(tmp);
	else
		return EERRNO;
	return SUCCESS;
}

int ospl_album_addpic(char *library, int photo, int album)
{
	t_db db = {0};

	fill_tdb(&db, library);
	if (insert_contains(&db, photo, album))
		return EDBFAIL;
	return SUCCESS;
}

int ospl_album_delpic(char *library, int photo, int album)
{
	t_db db = {0};

	fill_tdb(&db, library);
	if (delete_contains(&db, photo, album))
		return EDBFAIL;
	return SUCCESS;
}

int ospl_album_movepic(char *library, int photo, int old, int new)
{
	t_db db = {0};

	fill_tdb(&db, library);
	if (move_contains(&db, photo, old, new))
		return EDBFAIL;
	return SUCCESS;
}
