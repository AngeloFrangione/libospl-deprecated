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
 * \brief This file contains setting manipulation wrapper
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
 * \param dbpath path of the database
 * \param pic structure containing the photo data
 */
int insert_photo(char *dbpath, t_photos *pic)
{
	t_db	db;
	char	query[BUFFER_SIZE] = "insert into photos (hash, original_name, "
	"new_name, import_datetime, import_year, import_month, import_day, "
	"import_hour, import_minut, import_second, exif_height, exif_width, "
	"exif_brand, exif_peripheral) ";

	sprintf(query + 203, "values (\"%s\", \"%s\", \"%s\", \"%s\", \"%d\", "
		"\"%d\", \"%d\", \"%d\", \"%d\", \"%d\", \"%d\", \"%d\", \"%s\", "
		"\"%s\");", pic->hash, pic->original_name, pic->new_name,
		pic->import_datetime, pic->import_year, pic->import_month,
		pic->import_day, pic->import_hour, pic->import_minut,
		pic->import_second, pic->exif_height, pic->exif_width,
		pic->exif_brand, pic->exif_peripheral);
	printf("%s\n", query);
	init_connection(&db);
	init_db_transaction_rw(&db, dbpath);
	insert_transaction(query, &db);
	finalize_transaction(&db);
	return 0;
}

/**
 * \brief update a photo column that has a TEXT type
 *
 * 
 * \param dbpath path of the database
 * \param id the identifier of the picture
 * \param col the coloumn name you want to update
 * \param value the text value to be inserted instead of the old one
 */
int update_photo_char(char *dbpath, int id, char *col, char *value)
{
	t_db	db;
	char	query[BUFFER_SIZE] = "update photos set ";

	sprintf(query + 18, "%s=\"%s\" where id=%d;", col, value, id);
	init_connection(&db);
	init_db_transaction_rw(&db, dbpath);
	insert_transaction(query, &db);
	finalize_transaction(&db);
	return 0;
}

/**
 * \brief update a photo column that has a INTEGER type
 *
 * 
 * \param dbpath path of the database
 * \param id the unique identifier of the picture
 * \param col the coloumn name you want to update
 * \param value the integer value to be inserted instead of the old one
 */
int update_photo_int(char *dbpath, int id, char *col, int value)
{
	t_db	db;
	char	query[BUFFER_SIZE] = "update photos set ";

	sprintf(query + 18, "%s=%d where id=%d;", col, value, id);
	printf("%s\n", query);
	init_connection(&db);
	init_db_transaction_rw(&db, dbpath);
	insert_transaction(query, &db);
	finalize_transaction(&db);
	return 0;
}

/**
 * \brief update a photo column to NULL
 *
 * 
 * \param dbpath path of the database
 * \param id the unique identifier of the picture
 * \param col the coloumn name you want to update
 * \param value the integer value to be inserted instead of the old one
 */
int update_photo_null(char *dbpath, int id, char *col)
{
	t_db	db;
	char	query[BUFFER_SIZE] = "update photos set ";

	sprintf(query + 18, "%s=NULL where id=%d;", col, id);
	printf("%s\n", query);
	init_connection(&db);
	init_db_transaction_rw(&db, dbpath);
	insert_transaction(query, &db);
	finalize_transaction(&db);
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
 * \param dbpath path of the database
 * \param id the unique identifier of the picture
 * \param col the coloumn name you want to select
 * \param value a pointer to an initialized memory location where 
 * the column will be stored into
 */
int select_photo_single(char *dbpath, int id, char *col, char *value)
{
	t_db	db;
	char	query[BUFFER_SIZE];

	sprintf(query, "select %s from photos where id=%d", col, id);
	init_connection(&db);
	init_db_transaction_rw(&db, dbpath);	
	select_transaction_data(query, &db, callback_single, value);
	finalize_transaction(&db);
	return 0;
}

static int callback(t_photos *pic, int ac, char **av, char **column)
{
	strcpy(pic->hash, av[1]);
	return 0;
}

/**
 * \brief select a single column into photos table
 *
 * 
 * \param dbpath path of the database
 * \param id the unique identifier of the picture 
 * \param pic a pointer to an initialized memory location that points 
 * to an t_photos structure, every will be stored into this structure. 
 */
int select_photo(char *dbpath, int id, t_photos *pic)
{
	t_db		db;
	char		query[BUFFER_SIZE];

	sprintf(query, "select * from photos where id=%d", id);
	init_connection(&db);
	init_db_transaction_rw(&db, dbpath);	
	select_transaction_data(query, &db, callback, pic);
	finalize_transaction(&db);
	return 0;
}

/**
 * \brief delete a row into photos table
 *
 * 
 * \param dbpath path of the database
 * \param id the unique identifier of the picture
 */
int delete_photo(char *dbpath, int id)
{
	t_db	db;
	char	query[BUFFER_SIZE] = "delete from photos where id=";
	
	sprintf(query + 28, "%d;", id);
	init_connection(&db);
	init_db_transaction_rw(&db, dbpath);
	insert_transaction(query, &db);
	finalize_transaction(&db);
	return 0;
}
