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

/**
 * \file albums.c
 * \brief This file contains albums table manipulation wrapper
 * \author Angelo Frangione
 *
 * There is a function for every sql query type.
 */

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "include/stockage.h"

int create_album(t_db *db, char *name)
{
	char	query[BUFFER_SIZE] = "insert into albums (name) ";

	sprintf(query + 26, "values(\"%s\")", name);
	if (stockage_write(db, query))
		return 1;
	return 0;
}

int rename_album(t_db *db, int id, char *name)
{
	char	query[BUFFER_SIZE] = "update albums set name=";

	sprintf(query + 23, "\"%s\" where id=%d;", name, id);
	if (stockage_write(db, query))
		return 1;
	return 0;
}

int delete_album(t_db *db, int id)
{
	char	query[BUFFER_SIZE] = "delete from albums where id=";

	sprintf(query + 28, "%d;", id);
	if (stockage_write(db, query))
		return 1;
	return 0;
}

int insert_contains(t_db *db, int photo, int album)
{
	char	query[BUFFER_SIZE] = "insert into contains (containing_album, contained_photo) ";

	sprintf(query + 57, "values(\"%d\",\"%d\")", album, photo);
	if (stockage_write(db, query))
		return 1;
	return 0;
}

int delete_contains(t_db *db, int photo, int album)
{
	char	query[BUFFER_SIZE] = "delete from contains where ";

	sprintf(query + 27, "containing_album=%d and contained_photo=%d;", photo, album);
	if (stockage_write(db, query))
		return 1;
	return 0;
}

int move_contains(t_db *db, int photo, int old_album, int new_album)
{
	char	query[BUFFER_SIZE] = "update contains set containing_album=";

	sprintf(query + 37, "%d where contained_photo=%d and containing_album=%d", 
			new_album, photo, old_album);
	if (stockage_write(db, query))
		return 1;
	return 0;
}

static int _callback_pictures(t_photos *pic, int ac, char **av, char **column)
{
	static int current = 0;

	if (!pic)
	{
		current = 0;
		return 0;
	}
	pic[current].id = atoi(av[0]);
	strcpy(pic[current].hash, av[1]);
	strcpy(pic[current].original_name, av[2]);
	strcpy(pic[current].new_name, av[3]);
	strcpy(pic[current].import_datetime, av[4]);
	pic[current].import_year = atoi(av[5]);
	pic[current].import_month = atoi(av[6]);
	pic[current].import_day = atoi(av[7]);
	pic[current].import_hour = atoi(av[8]);
	pic[current].import_minut = atoi(av[9]);
	pic[current].import_second = atoi(av[10]);
	pic[current].exif_height = atoi(av[11]);
	pic[current].exif_width = atoi(av[12]);
	if (av[13])
		strcpy(pic[current].exif_brand, av[13]);
	if (av[14])
		strcpy(pic[current].exif_peripheral, av[14]);
	pic[current].fav = atoi(av[15]);
	++current;
	return 0;
}

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

int list_contains(t_db *db, int album, t_photos *list)
{
	char	query[BUFFER_SIZE];

	sprintf(query, "SELECT DISTINCT photos.* FROM photos INNER JOIN contains ON photos.id = contains.contained_photo WHERE contains.containing_album = %d;", album);
	_callback_pictures(NULL, 0, NULL, NULL);
	if (stockage_read(db, query, _callback_pictures, list))
		return 1;
	_callback_pictures(NULL, 0, NULL, NULL);
	return 0;
}

int photo_contained(t_db *db, int pic, t_album *list)
{
	char	query[BUFFER_SIZE];

	sprintf(query, "SELECT DISTINCT albums.* FROM albums INNER JOIN contains ON albums.id = contains.containing_album WHERE contains.contained_photo = %d;", pic);
	_callback_album(NULL, 0, NULL, NULL);
	if (stockage_read(db, query, _callback_album, list))
		return 1;
	_callback_album(NULL, 0, NULL, NULL);
	return 0;
}

int list_albums(t_db *db, t_album *list)
{
	char	query[BUFFER_SIZE] = "select * from albums";

	_callback_album(NULL, 0, NULL, NULL);
	if (stockage_read(db, query, _callback_album, list))
		return 1;
	_callback_album(NULL, 0, NULL, NULL);
	return 0;
}

int select_album(t_db *db, int id, t_album *album)
{
	char	query[BUFFER_SIZE];

	sprintf(query, "select * from albums where id=%d;", id);
	_callback_album(NULL, 0, NULL, NULL);
	if (stockage_read(db, query, _callback_album, album))
		return 1;
	_callback_album(NULL, 0, NULL, NULL);
	return 0;
}