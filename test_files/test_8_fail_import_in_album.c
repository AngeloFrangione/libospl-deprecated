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
	sprintf(lib_name, "test_Library_8_%d", r);
	if (ospl_create_library(lib_name) < 0)
	{
		printf("Error executing ospl_create_library\n");
		printf("lib_name: %s\n", lib_name);
		return 0;
	}
	if (ospl_album_create(lib_name, "Vacances") < 0)
	{
		printf("error executing ospl_album_create\n");
		return 0;
	}
	sprintf(tmp, "%s/photos/Vacances", lib_name);
	if (!folder_exists(tmp))
	{
		printf("album folder not found %s\n", tmp);
		return 0;
	}
	if (ospl_import_photo_in_album(lib_name, "../test_files/ressources/not.jpg", 1) >= 0)
	{
		printf("no error executing ospl_import_photo_in_album\n");
		return 0;
	}
	if (ospl_album_add_photo(lib_name, 1, 1) >= 0) 
	{
		printf("no error executing ospl_album_add_photo\n");
		return 0;
	}
	if (ospl_album_add_photo(lib_name, 1, 10) >= 0) 
	{
		printf("no error executing ospl_album_add_photo\n");
		return 0;
	}
	if (ospl_import_photo_in_album(lib_name, "../test_files/ressources/1b3BAEr6IJk.jpg", 50) >= 0)
	{
		printf("no error executing ospl_import_photo_in_album\n");
		return 0;
	}
	sprintf(tmp, "rm -rf %s", lib_name);
	if (system(tmp))
	{
		printf("executing the system command failed\n");
		return 0;
	}
	return 1;
}
