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

#include <sys/stat.h>
#include <fcntl.h>
#if defined(_WIN32)
# include <Windows.h>
#else
# include <unistd.h>
#endif
#if defined(__APPLE__) || defined(__FreeBSD__)
# include <copyfile.h>
#else
# include <sys/sendfile.h>
#endif
#include <dirent.h>
#include <magic.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <cwalk.h>
#include "ospl.h"

void fill_tdb(t_db *db, char *library)
{
	static char db_path[4096];
	memset(db, 0, sizeof(t_db));
	cwk_path_join(library, DATABASE_FILENAME, db_path, sizeof(db_path));
	db->path =  db_path;
}

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

int hard_link(char *current, char * new)
{
	#if defined(_WIN32)
	return CreateHardLink(new, current);
	#else
	return link(current, new);
	#endif
	
}

int remove_dir(char *path)
{
	DIR *d;
	struct dirent *dir;
	char tmp[4096] = { 0 };

	if (!(d = opendir(path)))
		return 1;
	else
	{
		while ((dir = readdir(d)))
		{
			if (!strcmp(dir->d_name, ".") || !strcmp(dir->d_name, ".."))
				continue;
			cwk_path_join(path, dir->d_name, tmp, sizeof(tmp));
			if(folder_exists(tmp))
				remove_dir(tmp);
			remove(tmp);
		}
		remove(path);
		closedir(d);
		return 0;
	}
}

int copy_file(char* source, char* destination)
{    
	int input, output;
	if ((input = open(source, O_RDONLY)) == -1)
	{
		return -1;
	}    
	if ((output = creat(destination, 0660)) == -1)
	{
		close(input);
		return -1;
	}

	#if defined(__APPLE__) || defined(__FreeBSD__)
	//fcopyfile works on FreeBSD and OS X 10.5+ 
	int result = fcopyfile(input, output, 0, COPYFILE_ALL);
	#else
	//sendfile will work with non-socket output (i.e. regular file) on Linux 2.6.33+
	off_t bytesCopied = 0;
	struct stat fileinfo = {0};
	fstat(input, &fileinfo);
	long result = sendfile(output, input, &bytesCopied, fileinfo.st_size);
	#endif
	close(input);
	close(output);
	return (int)result;
}

/**
  * \brief Checks if file the given in parameter exists
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
  * \brief Checks if folder given in paramter exists
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
		{
			free(magic);
			return i + 1;
		}
	}
	free(magic);
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
int library_exists(char *path)
{
	char db[512];

	cwk_path_join(path, "database.db", db, sizeof(db));
	if (folder_exists(path) && file_exists(db))
		return 1;
	else
		return 0;
}
