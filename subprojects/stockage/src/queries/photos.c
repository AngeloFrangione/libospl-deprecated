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
 * \file setting.c
 * \brief This file contains photos table manipulation wrapper
 * \author Angelo Frangione
 *
 * There is a function for every sql query type.
 */

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "include/stockage.h"

/**
 * \brief insert a photo row into photos table
 *
 * 
 * \param db database data structure
 * \param pic structure containing the photo data
 */
int insert_photo(t_db *db, t_photos *pic)
{
	char	query[BUFFER_SIZE] = "insert into photos (hash, original_name, "
	"new_name, import_datetime, random, import_year, import_month, import_day, "
	"import_hour, import_minut, import_second, exif_height, exif_width, "
	"exif_brand, exif_peripheral) ";

	sprintf(query + 211, "values (\"%s\", \"%s\", \"%s\", \"%s\", \"%s\", \"%d\", "
		"\"%d\", \"%d\", \"%d\", \"%d\", \"%d\", \"%d\", \"%d\", \"%s\", "
		"\"%s\");", pic->hash, pic->original_name, pic->new_name,
		pic->import_datetime, pic->random,pic->import_year, pic->import_month,
		pic->import_day, pic->import_hour, pic->import_minut,
		pic->import_second, pic->exif_height, pic->exif_width,
		pic->exif_brand, pic->exif_peripheral);
	stockage_write(db, query);
	return 0;
}

/**
 * \brief update a photo column that has a TEXT type
 *
 * 
 * \param db database data structure
 * \param id the identifier of the picture
 * \param col the coloumn name you want to update
 * \param value the text value to be inserted instead of the old one
 */
int update_photo_char(t_db *db, int id, char *col, char *value)
{
	char	query[BUFFER_SIZE] = "update photos set ";

	sprintf(query + 18, "%s=\"%s\" where id=%d;", col, value, id);
	stockage_write(db, query);
	return 0;
}

/**
 * \brief update a photo column that has a INTEGER type
 *
 * 
 * \param db database data structure
 * \param id the unique identifier of the picture
 * \param col the coloumn name you want to update
 * \param value the integer value to be inserted instead of the old one
 */
int update_photo_int(t_db *db, int id, char *col, int value)
{
	char	query[BUFFER_SIZE] = "update photos set ";

	sprintf(query + 18, "%s=%d where id=%d;", col, value, id);
	stockage_write(db, query);
	return 0;
}

/**
 * \brief update a photo column to NULL
 *
 * 
 * \param db database data structure
 * \param id the unique identifier of the picture
 * \param col the coloumn name you want to update
 * \param value the integer value to be inserted instead of the old one
 */
int update_photo_null(t_db *db, int id, char *col)
{
	char	query[BUFFER_SIZE] = "update photos set ";

	sprintf(query + 18, "%s=NULL where id=%d;", col, id);
	stockage_write(db, query);
	return 0;
}

static int callback_single(char *value, int ac, char **av, char **column)
{
	strcpy(value, av[0]);
	return 0;
}

/**
 * \brief select a single column into photos table
 *
 * 
 * \param db database data structure
 * \param id the unique identifier of the picture
 * \param col the coloumn name you want to select
 * \param value a pointer to an initialized memory location where 
 * the column will be stored into
 */
int select_photo_single(t_db *db, int id, char *col, char *value)
{

	char	query[BUFFER_SIZE];

	sprintf(query, "select %s from photos where id=%d", col, id);
	stockage_read(db, query, callback_single, value);
	return 0;
}

static int _callback_multiple(t_photos *pic, int ac, char **av, char **column)
{
	static int current = 0;

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

static int _callback(t_photos *pic, int ac, char **av, char **column)
{
	strcpy(pic->hash, av[1]);
	strcpy(pic->original_name, av[2]);
	strcpy(pic->new_name, av[3]);
	strcpy(pic->import_datetime, av[4]);
	pic->import_year = atoi(av[5]);
	pic->import_month = atoi(av[6]);
	pic->import_day = atoi(av[7]);
	pic->import_hour = atoi(av[8]);
	pic->import_minut = atoi(av[9]);
	pic->import_second = atoi(av[10]);
	pic->exif_height = atoi(av[11]);
	pic->exif_width = atoi(av[12]);
	if (av[13])
		strcpy(pic->exif_brand, av[13]);
	if (av[14])
		strcpy(pic->exif_peripheral, av[14]);
	pic->fav = atoi(av[15]);
	return 0;
}

/**
 * \brief select a single column into photos table
 *
 * 
 * \param db database data structure
 * \param id the unique identifier of the picture 
 * \param pic a pointer to an initialized memory location that points 
 * to a t_photos structure, every will be stored into this structure. 
 */
int select_photo(t_db *db, int id, t_photos *pic)
{
	char		query[BUFFER_SIZE];

	sprintf(query, "select * from photos where id=%d", id);
	stockage_read(db, query, _callback, pic);
	return 0;
}

int select_photo_multiple(t_db *db, int id, t_photos *pic)
{
	char		query[BUFFER_SIZE];

	sprintf(query, "select * from photos where id=%d", id);
	stockage_read(db, query, _callback_multiple, pic);
	return 0;
}


int select_photo_all(t_db *db, t_photos *pics)
{
	char		query[BUFFER_SIZE];

	sprintf(query, "select * from photos");
	stockage_read(db, query, _callback_multiple, pics);
	return 0;
}


/**
 * \brief delete a row into photos table
 *
 * 
 * \param db database data structure
 * \param id the unique identifier of the picture
 */
int delete_photo(t_db *db, int id)
{
	char	query[BUFFER_SIZE] = "delete from photos where id=";
	
	sprintf(query + 28, "%d;", id);
	stockage_write(db, query);
	return 0;
}
