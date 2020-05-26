/*	libospl - Open Source Photo Library
	an opensource and multiplateform photo library management that can be used
	to store and sort all your pictures.
	Copyright (C) 2020 Angelo Frangione

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
#include "md5.h"

int md5(char *filename, char *hash_md5)
{
	unsigned char c[16];
	int i;
	FILE *in_file = fopen(filename, "rb");
	MD5_CTX ctx;
	int bytes;
	unsigned char data[1024];

	if (in_file == NULL)
	{
		printf ("%s can't be opened.\n", filename);
		return 1;
	}
	MD5_Init (&ctx);
	while ((bytes = fread (data, 1, 1024, in_file)) != 0)
		MD5_Update (&ctx, data, bytes);
	MD5_Final (c,&ctx);
	for(i = 0; i < 16; i++)
		sprintf(hash_md5, "%s%x", hash_md5, c[i]);
	fclose (in_file);
	return 0;
}
