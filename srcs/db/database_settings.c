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
#include "ospl.h"

static int _callback_settings(char *param, int argc, char **argv, char **column)
{
	strcpy(param, argv[1]);
	return 0;
}

int db_insert_setting(t_db *db, char *name, char *value)
{
	char	query[BUFFER_SIZE] = "insert into settings (name, value) ";
	sprintf(query + 35, "values (\"%s\", \"%s\");", name, value);

	if (stockage_write(db, query))
		return 1;
	return 0;
}

int db_update_setting(t_db *db, char *name, char *value)
{
	char	query[BUFFER_SIZE] = "update settings set value=";

	sprintf(query + 26, "\"%s\" where name=\"%s\";", value, name);
	if (stockage_write(db, query))
		return 1;
	return 0;
}

int db_select_setting(t_db *db, char *name, char *value)
{
	char	query[BUFFER_SIZE] = "select * from settings ";
	
	sprintf(query + 23, "where name = \"%s\"", name);
	if (stockage_read(db, query, _callback_settings, value))
		return 1;
	return 0;
}

int db_delete_setting(t_db *db, char *name)
{
	char	query[BUFFER_SIZE] = "delete from settings where name=";
	
	sprintf(query + 32, "%s;", name);
	if (stockage_write(db, query))
		return 1;
	return 0;
}
