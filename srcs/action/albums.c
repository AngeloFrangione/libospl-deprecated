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

#include <string.h>
#include <stdio.h>
#include <ospl.h>
#include <cwalk.h>
#include <stockage.h>

int ospl_album_list(char *library, t_album *list)
{
	t_db db = {0};

	fill_tdb(&db, library);
	if (list_albums(&db, list))
		return EDBFAIL;
	return SUCCESS;
}

int ospl_album_list_photos(char *library, int album, t_photos *list)
{
	t_db db = {0};

	fill_tdb(&db, library);
	if (list_contains(&db, album, list))
		return EDBFAIL;
	return SUCCESS;
}

int ospl_photo_associated_album(char *library, int photo, t_album *list)
{
	t_db db = {0};

	fill_tdb(&db, library);
	if (photo_contained(&db, photo, list))
		return EDBFAIL;
	return SUCCESS;
}

int ospl_album_create(char *library, char *name)
{
	t_db db = {0};
	char tmp[512] = {0};

	cwk_path_join(library, "/photos/", tmp, sizeof(tmp));
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

int ospl_album_rename(char *library, int id, char *name)
{
	t_db db = {0};
	t_album album = {0};
	char tmp_new[512] = {0};
	char tmp_old[512] = {0};
	
	cwk_path_join(library, "/photos/", tmp_new, sizeof(tmp_new));
	cwk_path_join(tmp_new, name, tmp_new, sizeof(tmp_new));
	fill_tdb(&db, library);
	if(select_album(&db, id, &album))
		return EDBFAIL;
	if (!album.id)
		return ENOTFOUND;
	cwk_path_join(library, "/photos/", tmp_old, sizeof(tmp_old));
	cwk_path_join(tmp_old, album.name, tmp_old, sizeof(tmp_old));
	if (rename(tmp_old, tmp_new))
		return EERRNO;
	if (rename_album(&db, id, name))
		return EDBFAIL;
	return SUCCESS;
}

int ospl_album_delete(char *library, int id)
{
	t_db db = {0};
	char tmp[512] = { 0 };
	t_album album = { 0 };

	fill_tdb(&db, library);
	if(select_album(&db, id, &album))
		return EDBFAIL;
	if (!album.id)
		return ENOTFOUND;
	cwk_path_join(library, "/photos/", tmp, sizeof(tmp));
	cwk_path_join(tmp, album.name, tmp, sizeof(tmp));
	if(!delete_album(&db, id))
		remove_dir(tmp);
	else
		return EERRNO;
	return SUCCESS;
}

int ospl_album_add_photo(char *library, int photo, int album)
{
	t_db db = {0};
	t_photos pho = { 0 };
	t_album alb = { 0 };
	char tmp_original[512] = { 0 };
	char tmp_link[512] = { 0 };

	fill_tdb(&db, library);
	if (select_photo(&db, photo, &pho) < 0)
		return EDBFAIL;
	if (select_album(&db, album, &alb) < 0)
		return EDBFAIL;
	cwk_path_join(library, "/photos/import/", tmp_original, sizeof(tmp_original));
	cwk_path_join(tmp_original, pho.new_name, tmp_original, sizeof(tmp_original));

	cwk_path_join(library, "/photos/", tmp_link, sizeof(tmp_link));
	cwk_path_join(tmp_link, alb.name, tmp_link, sizeof(tmp_link));
	cwk_path_join(tmp_link, pho.new_name, tmp_link, sizeof(tmp_link));

	if (insert_contains(&db, photo, album) < 0)
		return EDBFAIL;
	if (hard_link(tmp_original, tmp_link) < 0)
		return EHARDLINK;
	return SUCCESS;
}

int ospl_album_delete_photo(char *library, int photo, int album)
{
	t_db db = {0};
	t_photos pho = { 0 };
	t_album alb = { 0 };
	char tmp[512] = { 0 };

	fill_tdb(&db, library);
	if (select_photo(&db, photo, &pho) < 0 || select_album(&db, album, &alb) < 0)
		return EDBFAIL;

	cwk_path_join(library, "/photos/", tmp, sizeof(tmp));
	cwk_path_join(tmp, alb.name, tmp, sizeof(tmp));
	cwk_path_join(tmp, pho.new_name, tmp, sizeof(tmp));

	if (delete_contains(&db, photo, album))
		return EDBFAIL;
	remove(tmp);
	return SUCCESS;
}

int ospl_album_move_photo(char *library, int photo, int old, int new)
{
	t_db db = {0};
	t_photos pho = { 0 };
	t_album alb_old = { 0 };
	t_album alb_new = { 0 };
	char tmp_old[512] = { 0 };
	char tmp_new[512] = { 0 };

	fill_tdb(&db, library);
	if (select_photo(&db, photo, &pho) < 0 || select_album(&db, old, &alb_old) < 0)
		return EDBFAIL;
	if (select_album(&db, new, &alb_new) < 0)
		return EDBFAIL;

	cwk_path_join(library, "/photos/", tmp_old, sizeof(tmp_old));
	cwk_path_join(tmp_old, alb_old.name, tmp_old, sizeof(tmp_old));
	cwk_path_join(tmp_old, pho.new_name, tmp_old, sizeof(tmp_old));

	cwk_path_join(library, "/photos/", tmp_new, sizeof(tmp_new));
	cwk_path_join(tmp_new, alb_new.name, tmp_new, sizeof(tmp_new));
	cwk_path_join(tmp_new, pho.new_name, tmp_new, sizeof(tmp_new));

	if (move_contains(&db, photo, old, new))
		return EDBFAIL;
	printf("moving %s to %s\n", tmp_old, tmp_new);
	rename(tmp_old, tmp_new);
	return SUCCESS;
}
