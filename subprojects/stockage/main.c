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
#define TRUE 1
#define FALSE 0
#include <stdio.h>
#include <string.h>
#include "include/stockage.h"

int main(int argc, char const *argv[])
{
	t_db db;
	memset(&db, 0, sizeof(t_db));

	db.path = "test.db";

	remove(db.path);
	create_database("test.db");
	// db.transaction = 1;
	///// Testing settings /////
	char value1[10] = {0};
	insert_setting(&db, "version", "0.1.0");
	select_setting(&db, "version", value1);
	printf("%s\n", value1);
	update_setting(&db, "version", "0.52");
	
	select_setting(&db, "version", value1);
	printf("%s\n", value1);

	//// Testing photos /////
	// create_database(&db);
	t_photos pic;
	memset(&pic, 0, sizeof(t_photos));
	strcpy(pic.hash, "dc93f5c86d19546fd6563fb7d806026d");
	strcpy(pic.original_name, "IMG_0001.jpg");
	strcpy(pic.new_name, "20207235139136407971_IMG_0001.jpg");
	strcpy(pic.import_datetime, "20207235132633098006");
	pic.import_year = 2020;
	pic.import_month = 05;
	pic.import_day = 22;
	pic.import_hour = 4;
	pic.import_minut = 41;
	pic.import_second = 55;
	strcpy(pic.exif_brand, "");
	strcpy(pic.exif_peripheral, "");
	insert_photo(&db, &pic);
	update_photo_null(&db, 1, "exif_brand");
	char value2[255] = {0};
	select_photo_single(&db, 1, "original_name", value2);
	printf("%s\n", value2);

	t_photos picc;
	memset(&picc, 0, sizeof(t_photos));
	strcpy(picc.hash, "Henlo");
	select_photo(&db, 1, &picc);
	printf("%s\n", picc.hash);
	// db.commit = 1;
	delete_photo(&db, 2);

	return 0;
}
