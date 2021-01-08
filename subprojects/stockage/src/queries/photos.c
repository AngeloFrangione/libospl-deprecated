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
 * \param pho structure containing the photo data
 */
int insert_photo(t_db *db, t_photos *pho)
{
	char	query[BUFFER_SIZE] = "insert into photos (hash, original_name, "
	"new_name, import_datetime, random, import_year, import_month, import_day, "
	"import_hour, import_minute, import_second, exif_height, exif_width, "
	"exif_brand, exif_peripheral) ";

	sprintf(query + 211, "values (\"%s\", \"%s\", \"%s\", \"%s\", \"%s\", \"%d\", "
		"\"%d\", \"%d\", \"%d\", \"%d\", \"%d\", \"%d\", \"%d\", \"%s\", "
		"\"%s\");", pho->hash, pho->original_name, pho->new_name,
		pho->import_datetime, pho->random,pho->import_year, pho->import_month,
		pho->import_day, pho->import_hour, pho->import_minute,
		pho->import_second, pho->exif_height, pho->exif_width,
		pho->exif_brand, pho->exif_peripheral);
	if (stockage_write(db, query))
		return 1;
	return 0;
}

/**
 * \brief update a photo column that has a TEXT type
 *
 * 
 * \param db database data structure
 * \param id the identifier of the photo
 * \param col the coloumn name you want to update
 * \param value the text value to be inserted instead of the old one
 */
int update_photo_char(t_db *db, int id, char *col, char *value)
{
	char	query[BUFFER_SIZE] = "update photos set ";

	sprintf(query + 18, "%s=\"%s\" where id=%d;", col, value, id);
	if (stockage_write(db, query))
		return 1;
	return 0;
}

/**
 * \brief update a photo column that has a INTEGER type
 *
 * 
 * \param db database data structure
 * \param id the unique identifier of the photo
 * \param col the coloumn name you want to update
 * \param value the integer value to be inserted instead of the old one
 */
int update_photo_int(t_db *db, int id, char *col, int value)
{
	char	query[BUFFER_SIZE] = "update photos set ";

	sprintf(query + 18, "%s=%d where id=%d;", col, value, id);
	if (stockage_write(db, query))
		return 1;
	return 0;
}

/**
 * \brief update a photo column to NULL
 *
 * 
 * \param db database data structure
 * \param id the unique identifier of the photo
 * \param col the coloumn name you want to update
 * \param value the integer value to be inserted instead of the old one
 */
int update_photo_null(t_db *db, int id, char *col)
{
	char	query[BUFFER_SIZE] = "update photos set ";

	sprintf(query + 18, "%s=NULL where id=%d;", col, id);
	if (stockage_write(db, query))
		return 1;
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
 * \param id the unique identifier of the photo
 * \param col the coloumn name you want to select
 * \param value a pointer to an initialized memory location where 
 * the column will be stored into
 */
int select_photo_single(t_db *db, int id, char *col, char *value)
{

	char	query[BUFFER_SIZE];

	sprintf(query, "select %s from photos where id=%d", col, id);
	if (stockage_read(db, query, callback_single, value))
		return 1;
	return 0;
}

static int _callback(t_photos *pho, int ac, char **av, char **column)
{
	static int current = 0;

	if (!pho)
	{
		current = 0;
		return 0;
	}
	pho[current].id = atoi(av[0]);
	strcpy(pho[current].hash, av[1]);
	strcpy(pho[current].original_name, av[2]);
	strcpy(pho[current].new_name, av[3]);
	strcpy(pho[current].import_datetime, av[4]);
	pho[current].import_year = atoi(av[5]);
	pho[current].import_month = atoi(av[6]);
	pho[current].import_day = atoi(av[7]);
	pho[current].import_hour = atoi(av[8]);
	pho[current].import_minute = atoi(av[9]);
	pho[current].import_second = atoi(av[10]);
	pho[current].exif_height = atoi(av[11]);
	pho[current].exif_width = atoi(av[12]);
	if (av[13])
		strcpy(pho[current].exif_brand, av[13]);
	if (av[14])
		strcpy(pho[current].exif_peripheral, av[14]);
	pho[current].fav = atoi(av[15]);
	++current;
	return 0;
}

/**
 * \brief select a single column into photos table
 *
 * 
 * \param db database data structure
 * \param id the unique identifier of the photo 
 * \param pho a pointer to an initialized memory location that points 
 * to a t_photos structure, every will be stored into this structure. 
 */
int select_photo(t_db *db, int id, t_photos *pho)
{
	char		query[BUFFER_SIZE];

	sprintf(query, "select * from photos where id=%d", id);
	_callback(NULL, 0, NULL, NULL);
	if (stockage_read(db, query, _callback, pho))
		return 1;
	_callback(NULL, 0, NULL, NULL);
	return 0;
}

int select_photo_multiple(t_db *db, int id, t_photos *pho)
{
	char		query[BUFFER_SIZE];

	sprintf(query, "select * from photos where id=%d", id);
	if (stockage_read(db, query, _callback, pho))
		return 1;
	return 0;
}


int select_photo_all(t_db *db, t_photos *phos)
{
	char		query[BUFFER_SIZE];

	sprintf(query, "select * from photos");
	_callback(NULL, 0, NULL, NULL);
	if (stockage_read(db, query, _callback, phos))
		return 1;
	_callback(NULL, 0, NULL, NULL);
	return 0;
}


/**
 * \brief delete a row into photos table
 *
 * 
 * \param db database data structure
 * \param id the unique identifier of the photo
 */
int delete_photo(t_db *db, int id)
{
	char	query[BUFFER_SIZE] = "delete from photos where id=";
	
	sprintf(query + 28, "%d;", id);
	if (stockage_write(db, query))
		return 1;
	return 0;
}
