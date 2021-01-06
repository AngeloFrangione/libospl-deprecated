#include "includes/ospl.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <sys/time.h>


int main(void)
{
	struct timeval nstime;
	char tmp[300] = {0};
	char lib_name[50];

	gettimeofday(&nstime, NULL);
	srand(nstime.tv_usec);
	int r = rand();
	sprintf(lib_name, "test_Library_10_%d", r);
	if (ospl_create_library(lib_name) < 0)
	{
		printf("Error executing ospl_create_library\n");
		printf("lib_name: %s\n", lib_name);
		return 1;
	}
	if (ospl_album_create(lib_name, "Vacances") < 0)
	{
		printf("error executing ospl_album_create\n");
		return 1;
	}
	sprintf(tmp, "%s/pictures/Vacances", lib_name);
	if (!folder_exists(tmp))
	{
		printf("album folder not found %s\n", tmp);
		return 1;
	}
	if (ospl_import_picture_in_album(lib_name, "../test_files/ressources/1b3BAEr6IJk.jpg", 1) < 0)
	{
		printf("error executing ospl_import_picture_in_album\n");
		return 1;
	}
	if (ospl_album_create(lib_name, "Album de test") < 0)
	{
		printf("error executing ospl_album_create\n");
		return 1;
	}
	t_photos pic;
	if (ospl_picture_get(lib_name, 1, &pic) < 0)
	{
		printf("Error executing ospl_picture_get\n");
		return 1;
	}
	sprintf(tmp, "%s/pictures/import/%s", lib_name, pic.new_name);
	if (!file_exists(tmp))
	{
		printf("picture not present in import folder: %s\n", tmp);
		return 1;
	}
	sprintf(tmp, "%s/pictures/Vacances/%s", lib_name, pic.new_name);
	if (!file_exists(tmp))
	{
		printf("picture not present in the album folder: %s\n", tmp);
		return 1;
	}
	t_album album;
	if (ospl_album_assocpic(lib_name, 1, &album) < 0)
	{
		printf("error executing ospl_album_assocpic\n");
		return 1;
	}
	if (album.id != 1)
	{
		printf("assoc_pic doesn't get the right album_id. expected: 1 result: %d\n", album.id);
		return 1;
	}
	if (ospl_album_listpic(lib_name, 1, &pic) < 0)
	{
		printf("error executing ospl_album_listpic\n");
		return 1;
	}
	if (pic.id != 1)
	{
		printf("list_pic doesn't get the right pic_id. expected: 1 result: %d\n", pic.id);
		return 1;
	}

	if (ospl_album_movepic(lib_name, 1, 1, 2))
	{
		printf("error executing ospl_album_movepic\n");
		return 1;
	}
	if (ospl_album_assocpic(lib_name, 2, &album) < 0)
	{
		printf("error executing ospl_album_assocpic\n");
		return 1;
	}
	if (album.id != 1)
	{
		printf("assoc_pic doesn't get the right album_id. expected: 1 result: %d\n", album.id);
		return 1;
	}
	if (ospl_album_listpic(lib_name, 1, &pic) < 0)
	{
		printf("error executing ospl_album_listpic\n");
		return 1;
	}
	if (pic.id != 1)
	{
		printf("list_pic doesn't get the right pic_id. expected: 1 result: %d\n", pic.id);
		return 1;
	}

	sprintf(tmp, "rm -rf %s", lib_name);
	if (system(tmp))
	{
		printf("executing the system command failed\n");
		return 1;
	}
	return 0;
}
