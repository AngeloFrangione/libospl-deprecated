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

#ifndef H_THUMBNAILER
# define H_THUMBNAILER
# define SUPPORTED_IMAGES (char *[]) {"image/jpeg"}
# define NB_SUPPORTED_IMAGES 1

enum {JPEG = 0, PNG = 1};

enum {E_PATH = 50, E_ENCODE = 51, E_NOSUPPORT = 52};

// Create thumbnail from jpeg
int create_thumbnail_jpeg(char *src, char *dst, int width);
// Create thumbnail and guess the type of the file returns 0 if success
int create_thumbnail(char *src, char *dst, int width);

#endif