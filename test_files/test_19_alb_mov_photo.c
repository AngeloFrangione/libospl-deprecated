#include "includes/ospl.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <sys/time.h>


int main(void)
{
	struct timeval nstime;
	char tmp[4096] = {0};
	char lib_name[50];
	int ret = 0;

	gettimeofday(&nstime, NULL);
	srand(nstime.tv_usec);
	int r = rand();
	sprintf(lib_name, "test_Library_19_%d", r);
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
	sprintf(tmp, "%s/photos/Vacances", lib_name);
	if (!folder_exists(tmp))
	{
		printf("album folder not found %s\n", tmp);
		return 1;
	}
	if (ospl_import_photo_in_album(lib_name, "../test_files/ressources/1b3BAEr6IJk.jpg", 1) < 0)
	{
		printf("error executing ospl_import_photo_in_album\n");
		return 1;
	}
	if (ospl_album_create(lib_name, "Album de test") < 0)
	{
		printf("error executing ospl_album_create\n");
		return 1;
	}
	t_photos pho;
	if (ospl_photo_get(lib_name, 1, &pho) < 0)
	{
		printf("Error executing ospl_photo_get\n");
		return 1;
	}
	sprintf(tmp, "%s/photos/import/%s", lib_name, pho.new_name);
	if (!file_exists(tmp))
	{
		printf("photo not present in import folder: %s\n", tmp);
		return 1;
	}
	sprintf(tmp, "%s/photos/Vacances/%s", lib_name, pho.new_name);
	if (!file_exists(tmp))
	{
		printf("photo not present in the album folder: %s\n", tmp);
		return 1;
	}
	t_album album;
	if ((ret = ospl_photo_associated_album(lib_name, 1, &album)) < 0)
	{
		printf("error executing ospl_photo_associated_album: %s\n", ospl_enum_error(ret));
		return 1;
	}
	if (album.id != 1)
	{
		printf("assoc_pho doesn't get the right album_id. expected: 1 result: %d\n", album.id);
		return 1;
	}
	if (ospl_album_list_photos(lib_name, 1, &pho) < 0)
	{
		printf("error executing ospl_album_list_photos\n");
		return 1;
	}
	if (pho.id != 1)
	{
		printf("list_pho doesn't get the right pho_id. expected: 1 result: %d\n", pho.id);
		return 1;
	}

	if (ospl_album_move_photo(lib_name, 1, 1, 2) < 0)
	{
		printf("error executing ospl_album_move_photo\n");
		return 1;
	}
	if (ospl_photo_associated_album(lib_name, 1, &album) < 0)
	{
		printf("error executing ospl_photo_associated_album\n");
		return 1;
	}
	if (album.id != 2)
	{
		printf("assoc_pho doesn't get the right album_id. expected: 2 result: %d\n", album.id);
		return 1;
	}
	if (ospl_album_list_photos(lib_name, 1, &pho) < 0)
	{
		printf("error executing ospl_album_list_photos\n");
		return 1;
	}
	if (pho.id != 1)
	{
		printf("list_pho doesn't get the right pho_id. expected: 1 result: %d\n", pho.id);
		return 1;
	}
	if (remove_dir(lib_name))
	{
		printf("executing remove_dir function failed\n");
		return 1;
	}
	return 0;
}
