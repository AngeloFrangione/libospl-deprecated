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
#include <errno.h>

int ospl_album_list(char *library, t_album *list)
{
	t_db db = {0};

	fill_tdb(&db, library);

	if (db_list_albums(&db, list))
		return ERR_DB;
	return SUCCESS;
}

int ospl_album_list_photos(char *library, int album, t_photos *list)
{
	t_db db = {0};

	fill_tdb(&db, library);

	if (db_list_contains(&db, album, list))
		return ERR_DB;
	return SUCCESS;
}

int ospl_photo_associated_album(char *library, int photo, t_album *list)
{
	t_db db = {0};

	fill_tdb(&db, library);

	if (db_photo_contained(&db, photo, list))
		return ERR_DB;
	return SUCCESS;
}

int ospl_album_create(char *library, char *name)
{
	t_db db = {0};
	char tmp[PATH_LEN_BUFFER] = {0};

	fill_tdb(&db, library);

	cwk_path_join(library, "/photos/", tmp, sizeof(tmp));
	cwk_path_join(tmp, name, tmp, sizeof(tmp));

	if(folder_exists(tmp))
		return ERR_EXISTS;
	if (db_create_album(&db, name))
		return ERR_DB;
	if (!create_directory(tmp))
		return get_last_insert_rowid(db.db);
	else
		return -1000 - errno;
}

int ospl_album_rename(char *library, int album, char *name)
{
	t_db db = {0};
	t_album alb = {0};
	char tmp_new[PATH_LEN_BUFFER] = {0};
	char tmp_old[PATH_LEN_BUFFER] = {0};
	
	fill_tdb(&db, library);

	cwk_path_join(library, "/photos/", tmp_new, sizeof(tmp_new));
	cwk_path_join(tmp_new, name, tmp_new, sizeof(tmp_new));

	if(db_select_album(&db, album, &alb))
		return ERR_DB;
	if (!alb.id)
		return ERR_ALB_NF;

	cwk_path_join(library, "/photos/", tmp_old, sizeof(tmp_old));
	cwk_path_join(tmp_old, alb.name, tmp_old, sizeof(tmp_old));

	if (db_rename_album(&db, album, name))
		return ERR_DB;
	if (rename(tmp_old, tmp_new))
		return -1000 - errno;
	return SUCCESS;
}

int ospl_album_delete(char *library, int album)
{
	t_db db = {0};
	char tmp[PATH_LEN_BUFFER] = { 0 };
	t_album alb = { 0 };

	fill_tdb(&db, library);
	if(db_select_album(&db, album, &alb))
		return ERR_DB;
	if (!alb.id)
		return ERR_ALB_NF;

	cwk_path_join(library, "/photos/", tmp, sizeof(tmp));
	cwk_path_join(tmp, alb.name, tmp, sizeof(tmp));

	if(!db_delete_album(&db, album))
		remove_dir(tmp);
	else
		return -1000 - errno;
	return SUCCESS;
}

int ospl_album_add_photo(char *library, int photo, int album)
{
	t_db db = {0};
	t_photos pho = { 0 };
	t_album alb = { 0 };
	char tmp_original[PATH_LEN_BUFFER] = { 0 };
	char tmp_link[PATH_LEN_BUFFER] = { 0 };

	fill_tdb(&db, library);
	if (db_select_photo(&db, photo, &pho) || db_select_album(&db, album, &alb))
		return ERR_DB;
	if (alb.id == 0)
		return ERR_ALB_NF;
	if (pho.id == 0)
		return ERR_PHO_NF;

	cwk_path_join(library, "/photos/import/", tmp_original, sizeof(tmp_original));
	cwk_path_join(tmp_original, pho.new_name, tmp_original, sizeof(tmp_original));

	cwk_path_join(library, "/photos/", tmp_link, sizeof(tmp_link));

	cwk_path_join(tmp_link, alb.name, tmp_link, sizeof(tmp_link));
	cwk_path_join(tmp_link, pho.new_name, tmp_link, sizeof(tmp_link));

	if (db_insert_contains(&db, photo, album))
		return ERR_DB;
	if (hard_link(tmp_original, tmp_link) < 0)
		return -1000 - errno;
	return SUCCESS;
}

int ospl_album_delete_photo(char *library, int photo, int album)
{
	t_db db = {0};
	t_photos pho = { 0 };
	t_album alb = { 0 };
	char tmp[PATH_LEN_BUFFER] = { 0 };

	fill_tdb(&db, library);
	if (db_select_photo(&db, photo, &pho) || db_select_album(&db, album, &alb))
		return ERR_DB;
	if (alb.id == 0)
		return ERR_ALB_NF;
	if (pho.id == 0)
		return ERR_PHO_NF;

	cwk_path_join(library, "/photos/", tmp, sizeof(tmp));
	cwk_path_join(tmp, alb.name, tmp, sizeof(tmp));
	cwk_path_join(tmp, pho.new_name, tmp, sizeof(tmp));

	if (db_delete_contains(&db, photo, album))
		return ERR_DB;
	remove(tmp);
	return SUCCESS;
}

int ospl_album_move_photo(char *library, int photo, int old, int new)
{
	t_db db = {0};
	t_photos pho = { 0 };
	t_album alb_old = { 0 };
	t_album alb_new = { 0 };
	char tmp_old[PATH_LEN_BUFFER] = { 0 };
	char tmp_new[PATH_LEN_BUFFER] = { 0 };

	fill_tdb(&db, library);
	if (db_select_photo(&db, photo, &pho) || db_select_album(&db, old, &alb_old) ||
		db_select_album(&db, new, &alb_new))
		return ERR_DB;
	if (alb_old.id == 0)
		return ERR_ALB_NF;
	if (alb_new.id == 0)
		return ERR_ALB_NF;
	if (pho.id == 0)
		return ERR_PHO_NF;

	cwk_path_join(library, "/photos/", tmp_old, sizeof(tmp_old));
	cwk_path_join(tmp_old, alb_old.name, tmp_old, sizeof(tmp_old));
	cwk_path_join(tmp_old, pho.new_name, tmp_old, sizeof(tmp_old));

	cwk_path_join(library, "/photos/", tmp_new, sizeof(tmp_new));
	cwk_path_join(tmp_new, alb_new.name, tmp_new, sizeof(tmp_new));
	cwk_path_join(tmp_new, pho.new_name, tmp_new, sizeof(tmp_new));

	if (db_move_contains(&db, photo, old, new))
		return ERR_DB;
	if (rename(tmp_old, tmp_new) < 0)
		return -1000 - errno;
	return SUCCESS;
}
