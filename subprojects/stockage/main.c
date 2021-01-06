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
	t_photos pho;
	memset(&pho, 0, sizeof(t_photos));
	strcpy(pho.hash, "dc93f5c86d19546fd6563fb7d806026d");
	strcpy(pho.original_name, "IMG_0001.jpg");
	strcpy(pho.new_name, "20207235139136407971_IMG_0001.jpg");
	strcpy(pho.import_datetime, "20207235132633098006");
	pho.import_year = 2020;
	pho.import_month = 05;
	pho.import_day = 22;
	pho.import_hour = 4;
	pho.import_minut = 41;
	pho.import_second = 55;
	strcpy(pho.exif_brand, "");
	strcpy(pho.exif_peripheral, "");
	insert_photo(&db, &pho);
	insert_photo(&db, &pho);
	update_photo_null(&db, 1, "exif_brand");
	char value2[255] = {0};
	select_photo_single(&db, 1, "original_name", value2);
	printf("%s\n", value2);

	t_photos phoc;
	memset(&phoc, 0, sizeof(t_photos));
	strcpy(phoc.hash, "Henlo");
	select_photo(&db, 1, &phoc);
	printf("%s\n", phoc.hash);
	// db.commit = 1;
	create_album(&db, "Vacances");
	create_album(&db, "Mon amour");
	insert_contains(&db, 1, 1);
	insert_contains(&db, 2, 2);
	move_contains(&db, 1, 1, 2);
	uint32_t list[65000];
	memset(list, 0, sizeof(uint32_t) * 65000);
	photo_contained(&db, 1, list);
	for (int i = 0;list[i]; i++)
	{
		printf("[%d]\n", list[i]);
	}
	t_album alb_list[2] = { 0 };
	list_albums(&db, alb_list);
	printf("name: [%s]\n", alb_list[0].name);
	printf("name: [%s]\n", alb_list[1].name);

	// delete_contains(&db, 1, 1);
	// rename_album(&db, 1, "Vacances 2");
	// delete_album(&db, 1);
	// delete_photo(&db, 1);
	printf("-----------------------------\n");
	t_photos pho_list[255] = { 0 };
	select_photo_all(&db, pho_list);
	printf("original_name | import_year\n");
	for (int i = 0;pho_list[i].import_year; i++)
	{
		printf("%13s %11d\n", pho_list[i].original_name, pho_list[i].import_year);
	}

	return 0;
}
