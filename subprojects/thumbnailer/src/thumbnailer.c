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

#include <magic.h>
#include "epeg.h"
#include "thumbnailer.h"

static int get_magic(char *actual_file, char **magic)
{
	magic_t magic_cookie;

	magic_cookie = magic_open(MAGIC_MIME_TYPE);	
	if (magic_cookie == NULL)
		return 1;
	if (magic_load(magic_cookie, NULL) != 0)
	{
		magic_close(magic_cookie);
		return 1;
	}
	*magic = strdup(magic_file(magic_cookie, actual_file));
	magic_close(magic_cookie);
	return 0;
}

static int is_supported(char *src)
{
	char **p = SUPPORTED_IMAGES;
	char *magic;
	
	get_magic(src, &magic);
	for (int i = 0; i < NB_SUPPORTED_IMAGES; i++)
	{
		if (!strcmp(p[i], magic))
		{
			free(magic);
			return i;
		}
	}
	free(magic);
	return 0;
}

int create_thumbnail_jpeg(char *src, char *dst, int width)
{
		float ratio;
		int thumb_width = width;
		int thumb_height;
		int r;
		int thumb_quality = 100;
		char *thumb_comment = NULL;
		Epeg_Image *image = epeg_file_open(src);

		if (!image)
			return E_PATH;
		ratio = (float)thumb_width / (float)image->in.w;
		thumb_height = (int)(image->in.h * ratio);
		epeg_decode_size_set			(image, thumb_width, thumb_height);
		epeg_quality_set				(image, thumb_quality);
		epeg_thumbnail_comments_enable	(image, 1);
		epeg_comment_set				(image, thumb_comment);
		epeg_file_output_set			(image, dst);
		r = epeg_encode					(image);
		epeg_close						(image);
		if (r) 
			return E_ENCODE;
		else
			return 0;
}

int create_thumbnail(char *src, char *dst, int width)
{
	switch (is_supported((char*)src))
	{
		case JPEG:
			return create_thumbnail_jpeg(src, dst, width);
			break;
		default:
			return E_NOSUPPORT;
			break;
	}
}
