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

#include <sys/stat.h>
#include <dirent.h>
#include <magic.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <cwalk.h>
#include "ospl.h"

/**
  * \brief Creates a directory for windows and UNIX
  *
  * \param path the path were to create new folder
  * \return the return of the system mkdir function
  */
int create_directory(char *path)
{
	#if defined(_WIN32)
	return mkdir(path);
	#else
	return mkdir(path, 0777);
	#endif
}

/**
  * \brief Checks if file given in parameter exists
  *
  * \param path location to test
  * \return 1 if the file exists
  * \return 0 if the file does not exists
  */
int file_exists(char *path)
{
	struct stat buffer;
	int exist = stat(path, &buffer);

	if(exist == 0)
		return 1;
	else
		return 0;
}

/**
  * \brief Checks if folder exists
  *
  * \param path location to check
  * \return 1 if the folder exists 
  * \return 0 if the folder does not exists
  */
int folder_exists(char *path)
{
	DIR* dir = opendir(path);
	if (dir)
	{
		closedir(dir);
		return 1;
	}
	else
		return 0;
}

/**
  * \brief Get the index of a character in a string
  *
  * \param s string to search in
  * \param c character to search with
  * \return the index from c in s
  * \return if c was not found in s returns -1
  */
int indexof(char *s, char c)
{
	int i;

	i = 0;
	if (!s)
		return (-1);
	while (s[i])
	{
		if (s[i] == c)
			return (i);
		++i;
	}
	return (-1);
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
	char *magic;
	
	get_magic(src, &magic);
	for (int i = 0; i < NB_SUPPORTED_IMAGES; i++)
	{
		if (!strcmp(p[i], magic))
			return i + 1;
	}
	return 0;
}

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
  * \brief Checks if libarary exists
  *
  * \param path location to test
  * \return 1 if the library exists
  * \return 0 if the library does not exists
  */
int library_exists(char *lib)
{
	char db[512];

	cwk_path_join(lib, "database.db", db, sizeof(db));
	if (folder_exists(lib) && file_exists(db))
		return 1;
	else
		return 0;
}
