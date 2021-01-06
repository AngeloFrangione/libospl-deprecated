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
 * \brief This file contains setting table manipulation wrapper
 * \author Angelo Frangione
 *
 * There is a function for every sql query type.
 */

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "include/stockage.h"

/**
 * \brief insert a row into settings table
 *
 * 
 * \param db database data structure
 * \param name name of the setting
 * \param value value of the setting
 */
int insert_setting(t_db *db, char *name, char *value)
{
	char	query[BUFFER_SIZE] = "insert into settings (name, value) ";
	sprintf(query + 35, "values (\"%s\", \"%s\");", name, value);

	if (stockage_write(db, query))
		return 1;
	return 0;
}

/**
 * \brief update a row into settings table
 *
 * 
 * \param db database data structure
 * \param name name of the setting
 * \param value value of the setting
 */
int update_setting(t_db *db, char *name, char *value)
{
	char	query[BUFFER_SIZE] = "update settings set value=";

	sprintf(query + 26, "\"%s\" where name=\"%s\";", value, name);
	if (stockage_write(db, query))
		return 1;
	return 0;
}

static int callback(char *param, int argc, char **argv, char **column)
{
	strcpy(param, argv[1]);
	return 0;
}

/**
 * \brief select a row into settings table
 *
 * 
 * \param db database data structure
 * \param name name of the setting to be selected
 * \param value a pointer to an initialized memory location where 
 * the value will be stored into
 */
int select_setting(t_db *db, char *name, char *value)
{
	char	query[BUFFER_SIZE] = "select * from settings ";
	
	sprintf(query + 23, "where name = \"%s\"", name);
	if (stockage_read(db, query, callback, value))
		return 1;
	return 0;
}

/**
 * \brief delete a row into settings table
 *
 * 
 * \param db database data structure
 * \param name name of the setting to be removed
 */
int delete_setting(t_db *db, char *name)
{
	char	query[BUFFER_SIZE] = "delete from settings where name=";
	
	sprintf(query + 32, "%s;", name);
	if (stockage_write(db, query))
		return 1;
	return 0;
}
