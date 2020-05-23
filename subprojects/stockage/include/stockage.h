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
#include <stdint.h>

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

#define BUFFER_SIZE			1024

typedef struct			s_photos
{
	char				hash[33];
	char				original_name[255];
	char				new_name[255];
	char				import_datetime[32];
	uint16_t			import_year;
	int					import_month;
	int					import_day;
	int					import_hour;
	int					import_minut;
	int					import_second;
	int					exif_height;
	int					exif_width;
	char				exif_brand[32];
	char				exif_peripheral[32];
	uint8_t				fav;
}						t_photos;

typedef struct			s_db
{
	sqlite3 			*db;
	char				*path;
	int					transaction;
}						t_db;


/*
 * 
 * Generic read / write functions
 * 
 */
int check_sqlite_return(int rc, t_db *db);
int init_db_transaction_rw(t_db *db);
int create_database(char *path);
int insert_transaction(char *query, t_db *db);
int select_transaction(char *query, t_db *db, int callback());
int select_transaction_data(char *query, t_db *db, int callback(), void *data);
int finalize_transaction(t_db *db);


/*
 * 
 * Queries - settings table
 * 
 */
int insert_setting(t_db *db, char *name, char *value);
int update_setting(t_db *db, char *name, char *value);
int select_setting(t_db *db, char *name, char *value);
int delete_setting(t_db *db, char *name);

/*
 * 
 * Queries - photos table
 * 
 */
int insert_photo(t_db *db, t_photos *pic);
int update_photo_int(t_db *db, int id, char *col, int value);
int update_photo_char(t_db *db, int id, char *col, char *value);
int update_photo_null(t_db *db, int id, char *col);
int select_photo_single(t_db *db, int id, char *col, char *value);
int select_photo(t_db *db, int id, t_photos *pic);
int delete_photo(t_db *db, int id);

#endif
