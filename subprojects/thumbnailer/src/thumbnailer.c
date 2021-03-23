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

#ifndef _WIN32
# include <magic.h>
#endif
#include "epeg.h"
#include "thumbnailer.h"


#ifndef _WIN32
/**
  * \brief Get the mime type from file with the magic number
  *
  * \param file_path path of the file to look for the magic
  * \param magic buffer were the mimetype will be put
  * in (don't have to be allocaded)
  * \return 1 if an error occured
  * \return 0 if the mime type was succefully put into magic
  */
int get_magic(char *file_path, char **magic)
{
	magic_t magic_cookie;

	magic_cookie = magic_open(MAGIC_MIME_TYPE);
	if (!magic_cookie)
	{
		printf("unable to initialize magic library\n");
		return 1;
	}
	if (magic_load(magic_cookie, NULL))
	{
		printf("cannot load magic database - %s\n", magic_error(magic_cookie));
		magic_close(magic_cookie);
		return 1;
	}
	*magic = strdup(magic_file(magic_cookie, file_path));
	magic_close(magic_cookie);
	return 0;
}

/**
  * \brief Check if an image is supported
  *
  * \param src path of the image to check
  * \return the index of the MimeType + 1 if supported
  * \return 0 if not supported
  */
int is_supported(char *src)
{
	char **p = SUPPORTED_IMAGES;
	char *magic = NULL;

	if (get_magic(src, &magic))
		return 0;
	for (int i = 0; i < NB_SUPPORTED_IMAGES; i++)
	{
		if (!strcmp(p[i], magic))
		{
			free(magic);
			return i + 1;
		}
	}
	free(magic);
	return 0;
}
#endif

#ifdef _WIN32
int get_ext(char *src, char **ext)
{
	int i = 0, len;

	len = strlen(src);
	while (src[len - i] != '.' || i == len)
		++i;
	*ext = calloc(len - i, sizeof(char *));
	strcpy(*ext, &src[len - i]);
	return 0;
}

/**
  * \brief Check if an image is supported
  *
  * \param src path of the image to check
  * \return the index of the MimeType + 1 if supported
  * \return 0 if not supported
  */
int is_supported(char *src)
{
	char **p = SUPPORTED_IMAGE_EXT;
	char *ext = NULL;

	if (get_ext(src, &ext))
		return 0;
	for (int i = 0; i < NB_SUPPORTED_EXT; i++)
	{
		if (!strcmp(p[i], ext))
		{
			free(ext);
			return i + 1;
		}
	}
	free(ext);
	return 0;
}
#endif



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
			return 1;
}

int create_thumbnail(char *src, char *dst, int width)
{
	switch (is_supported((char*)src))
	{
		case JPEG:
			return create_thumbnail_jpeg(src, dst, width);
			break;
		#ifdef _WIN32
		case JPG:
			return create_thumbnail_jpeg(src, dst, width);
			break;
		#endif
		default:
			return E_NOSUPPORT;
			break;
	}
}
