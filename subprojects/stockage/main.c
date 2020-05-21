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

#include <stdio.h>
#include "include/stockage.h"

int main(int argc, char const *argv[])
{
	char value[10] = {0};


	create_database("test.db");
	delete_setting("test.db", "name");
	insert_setting("test.db", "version", "0.1.0");
	select_setting("test.db", "version", value);
	printf("%s\n", value);
	update_setting("test.db", "version", "0.52");
	select_setting("test.db", "version", value);
	printf("%s\n", value);
	return 0;
}