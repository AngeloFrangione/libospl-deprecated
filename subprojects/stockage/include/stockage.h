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

#ifndef STOCKAGE_H
# define STOCKAGE_H

#include <sqlite3.h>
#include <stdint.h>

#define JOURNAL_MODE_MEMORY "PRAGMA journal_mode = MEMORY;"
#define SYNCRONOUS_OFF 		"PRAGMA synchronous = 0;"
#define TABLE 				"BEGIN TRANSACTION;"\
"CREATE TABLE IF NOT EXISTS `settings` ("\
"	`name`	TEXT NOT NULL UNIQUE,"\
"	`value`	TEXT,"\
"	PRIMARY KEY(`name`)"\
");"\
"CREATE TABLE IF NOT EXISTS `photos` ("\
"	`id`				INTEGER NOT NULL UNIQUE,"\
"	`hash`				TEXT NOT NULL,"\
"	`original_name`		TEXT NOT NULL,"\
"	`new_name`			TEXT NOT NULL,"\
"	`import_datetime`	TEXT,"\
"	`import_year`		INTEGER,"\
"	`import_month`		INTEGER,"\
"	`import_day`		INTEGER,"\
"	`import_hour`		INTEGER,"\
"	`import_minute`		INTEGER,"\
"	`import_second`		INTEGER,"\
"	`exif_height`		INTEGER,"\
"	`exif_width`		INTEGER,"\
"	`exif_time`			TEXT,"\
"	`exif_brand`		TEXT,"\
"	`exif_peripheral`	TEXT,"\
"	`fav`				INTEGER DEFAULT 0,"\
"	`random`			TEXT,"\
"	PRIMARY KEY(`id` AUTOINCREMENT)"\
");"\
"CREATE TABLE IF NOT EXISTS `includes` ("\
"	`including_folder`	INTEGER,"\
"	`included_folder`	INTEGER,"\
"	FOREIGN KEY(`including_folder`) REFERENCES `folders`(`id`),"\
"	FOREIGN KEY(`included_folder`) REFERENCES `folders`(`id`),"\
"	PRIMARY KEY(`including_folder`,`included_folder`)"\
");"\
"CREATE TABLE IF NOT EXISTS `holds` ("\
"	`held_folder`	INTEGER,"\
"	`holded_album`		INTEGER,"\
"	FOREIGN KEY(`holded_album`) REFERENCES `albums`(`id`),"\
"	FOREIGN KEY(`held_folder`) REFERENCES `folders`(`id`),"\
"	PRIMARY KEY(`held_folder`,`holded_album`)"\
");"\
"CREATE TABLE IF NOT EXISTS `folders` ("\
"	`id`	INTEGER NOT NULL UNIQUE,"\
"	`name`	INTEGER,"\
"	PRIMARY KEY(`id` AUTOINCREMENT)"\
");"\
"CREATE TABLE IF NOT EXISTS `contains` ("\
"	`containing_album`	INTEGER,"\
"	`contained_photo`	INTEGER,"\
"	FOREIGN KEY(`contained_photo`) REFERENCES `photos`(`id`),"\
"	FOREIGN KEY(`containing_album`) REFERENCES `albums`(`id`),"\
"	PRIMARY KEY(`containing_album`,`contained_photo`)"\
");"\
"CREATE TABLE IF NOT EXISTS `albums` ("\
"	`id`	INTEGER NOT NULL UNIQUE,"\
"	`name`	TEXT,"\
"	PRIMARY KEY(`id` AUTOINCREMENT)"\
");"\
"CREATE TABLE IF NOT EXISTS `includes` ("\
"	`including_folder`	INTEGER,"\
"	`included_folder`	INTEGER,"\
"	FOREIGN KEY(`including_folder`) REFERENCES `folders`(`id`),"\
"	FOREIGN KEY(`included_folder`) REFERENCES `folders`(`id`),"\
"	PRIMARY KEY(`including_folder`,`included_folder`)"\
");"\
"COMMIT;"

#define BUFFER_SIZE			1024

typedef struct			s_photos
{
	int					id;
	char				hash[33];
	char				original_name[255];
	char				new_name[255];
	char				import_datetime[32];
	char				random[11];
	uint16_t			import_year;
	uint8_t				import_month;
	uint8_t				import_day;
	uint8_t				import_hour;
	uint8_t				import_minute;
	uint8_t				import_second;
	uint32_t			exif_height;
	uint32_t			exif_width;
	char				exif_brand[32];
	char				exif_peripheral[32];
	uint8_t				fav;
}						t_photos;

typedef struct			s_album
{
	int					id;
	char				name[255];
}						t_album;

typedef struct			s_db
{
	sqlite3				*db;
	char				*path;
}						t_db;

/*
 * 
 * Generic read / write functions
 * 
 */
int get_last_insert_rowid(sqlite3 *sqlite);
int check_sqlite_return(int rc, t_db *db, char *query);
int stockage_init(t_db *db);
int create_database(char *path);
int stockage_query_write(char *query, t_db *db);
int stockage_query_read(char *query, t_db *db, int callback(), void *data);
int stockage_commit(t_db *db);

/*
 * 
 * Higher level read / write functions
 * 
 */
int stockage_write(t_db *db, char *query);
int stockage_read(t_db *db, char *query, int callback(), void *value);

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
int insert_photo(t_db *db, t_photos *pho);
int update_photo_int(t_db *db, int id, char *col, int value);
int update_photo_char(t_db *db, int id, char *col, char *value);
int update_photo_null(t_db *db, int id, char *col);
int select_photo_single(t_db *db, int id, char *col, char *value);
int select_photo_multiple(t_db *db, int id, t_photos *pho);
int select_photo_all(t_db *db, t_photos *pho);
int select_photo(t_db *db, int id, t_photos *pho);
int delete_photo(t_db *db, int id);
int select_last_photo_id(t_db *db);

/*
 * 
 * Queries - albums table
 * 
 */
int create_album(t_db *db, char *name);
int rename_album(t_db *db, int id, char *name);
int delete_album(t_db *db, int id);

int insert_contains(t_db *db, int photo, int album);
int delete_contains(t_db *db, int photo, int album);
int move_contains(t_db *db, int photo, int old_album, int new_album);
int list_contains(t_db *db, int album, t_photos *list);
int photo_contained(t_db *db, int photo, t_album *list);
int list_albums(t_db *db, t_album *list);
int select_album(t_db *db, int id, t_album *album);

#endif
