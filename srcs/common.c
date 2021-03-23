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
# include <windows.h>
#else
# include <sys/sendfile.h>
# include <unistd.h>
#endif
#if defined(__APPLE__) || defined(__FreeBSD__)
# include <copyfile.h>
#endif
#include <dirent.h>
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
	return CreateHardLink(new, current, NULL);
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
	{
		perror(NULL);
		return 1;
	}
	else
	{
		while ((dir = readdir(d)))
		{
			if (!strcmp(dir->d_name, ".") || !strcmp(dir->d_name, ".."))
				continue;
			cwk_path_join(path, dir->d_name, tmp, sizeof(tmp));
			if(folder_exists(tmp))
				remove_dir(tmp);
			printf("removing %s\n", tmp);
			#ifdef _WIN32
				DeleteFileA(tmp);
			#else
				remove(tmp);
			#endif
		}
		#ifdef _WIN32
			RemoveDirectoryA(path);
		#else
			remove(path);
		#endif
		closedir(d);
		return 0;
	}
}

#if defined (_WIN32)
int copy_file(char* source, char* destination)
{
	return CopyFile(source, destination, 0);
}
#else
int copy_file(char* source, char* destination)
{    

	int input, output;
	if ((input = open(source, O_RDONLY)) == -1)
		return -1;
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
#endif
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
