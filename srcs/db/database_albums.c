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

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "ospl.h"

static int _callback_album(t_album *list, int ac, char **av, char **column)
{
	static int current = 0;

	if (!list)
	{
		current = 0;
		return 0;
	}
	list[current].id = atoi(av[0]);
	strcpy(list[current].name, av[1]);
	current++;
	return 0;
}

int db_create_album(t_db *db, char *name)
{
	char	query[BUFFER_SIZE] = "insert into albums (name) ";

	sprintf(query + 26, "values(\"%s\")", name);
	if (stockage_write(db, query))
		return 1;
	return 0;
}

int db_rename_album(t_db *db, int id, char *name)
{
	char	query[BUFFER_SIZE] = "update albums set name=";

	sprintf(query + 23, "\"%s\" where id=%d;", name, id);
	if (stockage_write(db, query))
		return 1;
	return 0;
}

int db_delete_album(t_db *db, int id)
{
	char	query[BUFFER_SIZE] = "delete from albums where id=";

	sprintf(query + 28, "%d;", id);
	if (stockage_write(db, query))
		return 1;
	return 0;
}

int db_insert_contains(t_db *db, int photo, int album)
{
	char	query[BUFFER_SIZE] = "insert into contains (containing_album, contained_photo) ";

	sprintf(query + 57, "values(\"%d\",\"%d\")", album, photo);
	if (stockage_write(db, query))
		return 1;
	return 0;
}

int db_delete_contains(t_db *db, int photo, int album)
{
	char	query[BUFFER_SIZE] = "delete from contains where ";

	sprintf(query + 27, "containing_album=%d and contained_photo=%d;", photo, album);
	if (stockage_write(db, query))
		return 1;
	return 0;
}

int db_move_contains(t_db *db, int photo, int old_album, int new_album)
{
	char	query[BUFFER_SIZE] = "update contains set containing_album=";

	sprintf(query + 37, "%d where contained_photo=%d and containing_album=%d", 
			new_album, photo, old_album);
	if (stockage_write(db, query))
		return 1;
	return 0;
}

int db_photo_contained(t_db *db, int pho, t_album *list)
{
	char	query[BUFFER_SIZE];

	sprintf(query, "SELECT DISTINCT albums.* FROM albums INNER JOIN contains ON albums.id = contains.containing_album WHERE contains.contained_photo = %d;", pho);
	_callback_album(NULL, 0, NULL, NULL);
	if (stockage_read(db, query, _callback_album, list))
		return 1;
	_callback_album(NULL, 0, NULL, NULL);
	return 0;
}

int db_list_albums(t_db *db, t_album *list)
{
	char	query[BUFFER_SIZE] = "select * from albums";

	_callback_album(NULL, 0, NULL, NULL);
	if (stockage_read(db, query, _callback_album, list))
		return 1;
	_callback_album(NULL, 0, NULL, NULL);
	return 0;
}

int db_select_album(t_db *db, int id, t_album *album)
{
	char	query[BUFFER_SIZE];

	sprintf(query, "select * from albums where id=%d;", id);
	_callback_album(NULL, 0, NULL, NULL);
	if (stockage_read(db, query, _callback_album, album))
		return 1;
	_callback_album(NULL, 0, NULL, NULL);
	return 0;
}
