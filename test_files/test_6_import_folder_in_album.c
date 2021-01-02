#include "includes/ospl.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <sys/time.h>


int main(void)
{
	struct timeval nstime;
	char tmp[300] = {0};
	char lib_name[50];

	gettimeofday(&nstime, NULL);
	srand(nstime.tv_usec);
	int r = rand();
	sprintf(lib_name, "test_Library_6_%d", r);
	if (ospl_create_library(lib_name) < 0)
	{
		printf("Error executing ospl_create_library\n");
		printf("lib_name: %s\n", lib_name);
		return 1;
	}
	if (ospl_create_album(lib_name, "Album of random pictures") < 0)
	{
		printf("error executing ospl_create_album\n");
		return 1;
	}
	if (ospl_import_folder_in_album(lib_name, "../test_files/ressources/Album of random pictures/", 1) < 0)
	{
		printf("Error executing ospl_import_folder_in_album\n");
		return 1;
	}
	t_photos pic[65] = { 0 };
	if (ospl_album_listpic(lib_name, 1, pic) < 0)
	{
		printf("Error executing ospl_picture_list\n");
		return 1;
	}
	int i = 0;
	while(pic[i].id)
	{
		sprintf(tmp, "%s/pictures/Album of random pictures/%s", lib_name, pic[i].new_name);
		if (!file_exists(tmp))
		{
			printf("%s picture not present in import folder: %s\n", pic[i].original_name, tmp);
			return 1;
		}
		++i;
	}
	if (i < 57)
	{
		printf("only found %d pics inside of the album instead of 57\n", i);
		return 1;
	}
	if (ospl_delete_album(lib_name, 1) < 0)
	{
		printf("error executing ospl_delete_album\n");
		return 1;
	}
	i = 0;
	while(pic[i].id)
	{
		sprintf(tmp, "%s/pictures/Album of random pictures/%s", lib_name, pic[i].new_name);
		if (file_exists(tmp))
		{
			printf("%s picture present in album folder altho it was deleted: %s\n", pic[i].original_name, tmp);
			return 1;
		}
		++i;
	}
	sprintf(tmp, "rm -rf %s", lib_name);
	if (system(tmp))
	{
		printf("executing the system command failed\n");
		return 1;
	}
	return 0;
}
