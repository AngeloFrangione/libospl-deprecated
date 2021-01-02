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
	sprintf(lib_name, "test_Library_11_%d", r);
	if (ospl_create_library(lib_name) < 0)
	{
		printf("Error executing ospl_create_library\n");
		printf("lib_name: %s\n", lib_name);
		return 1;
	}
	if (ospl_import_picture(lib_name, "../test_files/ressources/1b3BAEr6IJk.jpg") < 0)
	{
		printf("Error executing ospl_import_picture\n");
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
	if (ospl_picture_delete(lib_name, 1) < 0)
	{
		printf("error executing ospl_picture_delete\n");
		return 1;
	}
	if (file_exists(tmp))
	{
		printf("picture present in import folder altho it was deleted: %s\n", tmp);
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
