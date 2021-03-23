#include "includes/ospl.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <sys/time.h>


int main(void)
{
	struct timeval nstime;
	char tmp[4096] = {0};
	char lib_name[50];
	t_import_status *status;

	gettimeofday(&nstime, NULL);
	srand(nstime.tv_usec);
	int r = rand();
	sprintf(lib_name, "test_Library_11_%d", r);
	if (ospl_create_library(lib_name) < 0)
	{
		printf("Error executing ospl_create_library\n");
		printf("lib_name: %s\n", lib_name);
		return 1;
	}
	if (ospl_album_create(lib_name, "Album of random photos") < 0)
	{
		printf("error executing ospl_album_create\n");
		return 1;
	}
	if (!(status = ospl_import_folder_in_album(lib_name, "../test_files/ressources/Album of random photos/", 1)))
	{
		printf("Error executing ospl_import_folder_in_album\n");
		return 1;
	}
	t_photos pho[65] = { 0 };
	if (ospl_album_list_photos(lib_name, 1, pho) < 0)
	{
		printf("Error executing ospl_photo_list\n");
		return 1;
	}
	int i = 0;
	while(pho[i].id)
	{
		sprintf(tmp, "%s/photos/Album of random photos/%s", lib_name, pho[i].new_name);
		if (!file_exists(tmp))
		{
			printf("%s photo not present in import folder: %s\n", pho[i].original_name, tmp);
			return 1;
		}
		++i;
	}
	if (i < 57)
	{
		printf("only found %d phos inside of the album instead of 57\n", i);
		return 1;
	}
	if (ospl_album_delete(lib_name, 1) < 0)
	{
		printf("error executing ospl_album_delete\n");
		return 1;
	}
	i = 0;
	while(pho[i].id)
	{
		sprintf(tmp, "%s/photos/Album of random photos/%s", lib_name, pho[i].new_name);
		if (file_exists(tmp))
		{
			printf("%s photo present in album folder altho it was deleted: %s\n", pho[i].original_name, tmp);
			return 1;
		}
		++i;
	}
	free_import_status(&status);
	if (remove_dir(lib_name))
	{
		printf("executing remove_dir function failed\n");
		return 1;
	}
	return 0;
}
