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

#ifdef _WIN32
# include <windows.h>
#endif
#include <string.h>
#include <stdlib.h>
#include <dirent.h>
#include <math.h>
#include <time.h>
#include <stdio.h>
#include <errno.h>

#include <cwalk.h>
#include <thumbnailer.h>
#include <stockage.h>
#include <md5.h>


#include "ospl.h"

static void get_time(t_current_time *ct)
{
	#if defined(__APPLE__) || defined(__FreeBSD__) || defined(__UNIX__)
	time_t t = time(NULL);
	struct tm tm = *localtime(&t);
	struct timespec spec;
	
	clock_gettime(CLOCK_REALTIME_COARSE, &spec);

	ct->Y = (unsigned int)tm.tm_year + 1900;
	ct->M = (unsigned int)tm.tm_mon + 1;
	ct->d = (unsigned int)tm.tm_mday;
	ct->h = (unsigned int)tm.tm_hour;
	ct->m = (unsigned int)tm.tm_min;
	ct->s = (unsigned int)tm.tm_sec;
	ct->ms = round(spec.tv_nsec / 1.0e6);
	#endif
	#if defined(_WIN32)
	SYSTEMTIME wintime;
	GetSystemTime(&wintime);
	ct->Y = wintime.wYear;
	ct->M = wintime.wMonth;
	ct->d = wintime.wDay;
	ct->h = wintime.wHour;
	ct->m = wintime.wMinute;
	ct->s = wintime.wSecond;
	ct->ms = wintime.wMilliseconds;
	#endif
}

static int get_info(t_db *db, t_photos *pho, char *path, char *library)
{
	size_t len;
	char hash[33] = {0};
	t_current_time ct;
	const char *name;

	md5(path, hash);
	get_time(&ct);
	srand(time(0) + ct.ms);
	cwk_path_get_basename(path, &name, &len);
	sprintf(pho->random, "%010d", rand());
	strcpy(pho->hash, hash);
	strcpy(pho->original_name, name);
	sprintf(pho->import_datetime, "%d-%02d-%02d-%02d-%02d-%02d-%03d",
	ct.Y, ct.M, ct.d, ct.h, ct.m, ct.s, ct.ms);
	sprintf(pho->new_name, "%s_%s", pho->import_datetime, pho->original_name);
	pho->import_year = (uint16_t)ct.Y;
	pho->import_month = (uint8_t)ct.M;
	pho->import_day = (uint8_t)ct.d;
	pho->import_hour = (uint8_t)ct.h;
	pho->import_minute = (uint8_t)ct.m;
	pho->import_second = (uint8_t)ct.s;
	fill_tdb(db, library);
	return SUCCESS;
}

int ospl_import_photo(char *library, char *path)
{
	t_db db = {0};
	t_photos pho = {0};
	char import_path[PATH_LEN_BUFFER] = {0};
	char thumb_path[PATH_LEN_BUFFER] = {0};
	if (!file_exists(path))
		return ERR_NOT_FOUND;
	if(!is_supported(path))
		return ERR_NOT_SUPPORTED;
	get_info(&db, &pho, path, library);
	if (db_insert_photo(&db, &pho))
		return ERR_DB;
	int id = stockage_get_last_insert_rowid(db.db);
	cwk_path_join(library, "/photos/import", import_path, sizeof(import_path));
	cwk_path_join(library, "/thumbnails/", thumb_path, sizeof(thumb_path));
	cwk_path_join(thumb_path, pho.new_name, thumb_path, sizeof(thumb_path));
	cwk_path_join(import_path, pho.new_name, import_path, sizeof(import_path));

	if (copy_file(path, import_path) < 0)
	{
		return -1000 - errno;
	}
	create_thumbnail(import_path, thumb_path, THUMB_HEIGHT);
	return id;
}

int ospl_import_photo_in_album(char *library, char *path, int album)
{
	int r, id;
	t_db db;
	t_album alb;

	fill_tdb(&db, library);
	db_select_album(&db, album, &alb);
	if (alb.id != album)
		return ERR_ALB_NF;
	if ((id = ospl_import_photo(library, path)) <= 0)
		return id;
	if ((r = ospl_album_add_photo(library, id, album)) < 0)
		return r;
	return id;
}

t_import_status *ospl_import_folder(char *library, char *path)
{
	DIR *d;
	int i = 0;
	int j = 1;
	struct dirent *dir;
	char tmp[PATH_LEN_BUFFER] = { 0 };
	t_import_status *status = NULL;
	t_import_status *tmp_status = NULL;

	if (!(d = opendir(path)))
		return NULL;
	while ((dir = readdir(d)))
	{
		if (!(i % 32000))
		{
			tmp_status = status;
			status = realloc(status, sizeof(t_import_status*) * (32000 * j) + 1);
			if (!status)
			{
				free_import_status(&tmp_status);
				return NULL;
			}
			j++;
		}
		if (!strcmp(dir->d_name, ".") || !strcmp(dir->d_name, ".."))
			continue;
		cwk_path_join(path, dir->d_name, tmp, sizeof(tmp));
		status[i].path = strdup(tmp);
		if (!status[i].path)
		{
			free_import_status(&status);
			return NULL;
		}
		status[i].id = ospl_import_photo(library, tmp);
		++i;
	}
	if (status)
		status[i].path = NULL;
	closedir(d);
	return status;
}

t_import_status *ospl_import_folder_in_album(char *library, char *path, int album)
{
	t_import_status *status;
	int i = 0;
	t_db db;
	t_album alb;

	fill_tdb(&db, library);
	db_select_album(&db, album, &alb);
	if (alb.id != album)
		return NULL;
	status = ospl_import_folder(library, path);
	if (!status)
		return NULL;

	while (status[i].path)
	{
		if (status[i].id > 0)
			ospl_album_add_photo(library, status[i].id, album);
		++i;
	}
	return status;
}

