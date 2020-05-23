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

#ifndef STOCKAGE_H
# define STOCKAGE_H

#include <sqlite3.h>

#define JOURNAL_MODE_MEMORY "PRAGMA journal_mode = MEMORY;"
#define SYNCRONOUS_OFF 		"PRAGMA synchronous = 0;"
#define TABLE 				"BEGIN TRANSACTION;\
CREATE TABLE IF NOT EXISTS `settings` (\
	`name`	TEXT NOT NULL UNIQUE,\
	`value`	TEXT,\
	PRIMARY KEY(`name`)\
);\
CREATE TABLE IF NOT EXISTS `photos` (\
	`id`				INTEGER NOT NULL PRIMARY KEY AUTOINCREMENT UNIQUE,\
	`hash`				TEXT,\
	`original_name`		TEXT,\
	`new_name`			TEXT,\
	`import_datetime`	TEXT,\
	`import_year`		INTEGER,\
	`import_month`		INTEGER,\
	`import_day`		INTEGER,\
	`import_hour`		INTEGER,\
	`import_minut`		INTEGER,\
	`import_second`		INTEGER,\
	`exif_height`		INTEGER,\
	`exif_width`		INTEGER,\
	`exif_brand`		TEXT,\
	`exif_peripheral`	TEXT,\
	`fav`				INTEGER DEFAULT 0\
);\
CREATE TABLE IF NOT EXISTS `includes` (\
	`including_folder`	INTEGER,\
	`included_folder`	INTEGER,\
	FOREIGN KEY(`included_folder`) REFERENCES `folders`(`id`),\
	PRIMARY KEY(`including_folder`,`included_folder`),\
	FOREIGN KEY(`including_folder`) REFERENCES `folders`(`id`)\
);\
CREATE TABLE IF NOT EXISTS `holds` (\
	`holding_folder`	INTEGER,\
	`holded_album`	INTEGER,\
	FOREIGN KEY(`holded_album`) REFERENCES `albums`(`id`),\
	FOREIGN KEY(`holding_folder`) REFERENCES `folders`(`id`),\
	PRIMARY KEY(`holding_folder`,`holded_album`)\
);\
CREATE TABLE IF NOT EXISTS `folders` (\
	`id`	INTEGER NOT NULL PRIMARY KEY AUTOINCREMENT UNIQUE,\
	`name`	INTEGER\
);\
CREATE TABLE IF NOT EXISTS `contains` (\
	`containing_album`	INTEGER,\
	`contained_photo`	INTEGER,\
	FOREIGN KEY(`contained_photo`) REFERENCES `photos`(`id`),\
	FOREIGN KEY(`containing_album`) REFERENCES `albums`(`id`),\
	PRIMARY KEY(`containing_album`,`contained_photo`)\
);\
CREATE TABLE IF NOT EXISTS `albums` (\
	`id`	INTEGER NOT NULL PRIMARY KEY AUTOINCREMENT UNIQUE,\
	`name`	TEXT\
);\
COMMIT;"

#define BUFFER_SIZE			512

typedef struct			s_db
{
	sqlite3 			*db;
	int					transaction;
	void				*param;
}						t_db;


/*
 * 
 * Generic read / write functions
 * 
 */
int check_sqlite_return(int rc, t_db *db);
int init_db_rw(t_db *db, char *path);
int init_db_transaction_rw(t_db *db, char *path);
int create_database(char *path);
int insert_transaction(char *query, t_db *db);
int select_transaction(char *query, t_db *db, int callback());
int select_transaction_data(char *query, t_db *db, int callback(), void *data);
int finalize_transaction(t_db *db);
int init_connection(t_db *db);


/*
 * 
 * Queries
 * 
 */
int insert_setting(char *dbpath, char *name, char *value);
int update_setting(char *dbpath, char *name, char *value);
int select_setting(char *dbpath, char *name, char *value);
int delete_setting(char *dbpath, char *name);
#endif
