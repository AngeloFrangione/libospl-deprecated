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

	gettimeofday(&nstime, NULL);
	srand(nstime.tv_usec);
	int r = rand();
	sprintf(lib_name, "test_Library_9_%d", r);
	if (ospl_create_library(lib_name) < 0)
	{
		printf("Error executing ospl_create_library\n");
		printf("lib_name: %s\n", lib_name);
		return 1;
	}
	t_import_status *status;
	status = ospl_import_folder(lib_name, "../test_files/ressources/Album of random photos/");
	if (!status)
	{
		printf("Error executing ospl_import_folder\n");
		return 1;
	}
	t_photos pho[65] = { 0 };
	if (ospl_photo_list(lib_name, pho) < 0)
	{
		printf("Error executing ospl_photo_list\n");
		return 1;
	}
	for (int i = 0; i < 57; ++i)
	{
		if (status[i].id != i + 1)
		{
			printf("id not corresponding expected %d got %d\n", i + 1, status[i].id);
			return 1;
		}
		sprintf(tmp, "%s/photos/import/%s", lib_name, pho[i].new_name);
		if (!file_exists(tmp))
		{
			printf("photo not present in import folder: %s\n", tmp);
			return 1;
		}
	}
	free_import_status(&status);
	sprintf(tmp, "rm -rf %s", lib_name);
	if (system(tmp))
	{
		printf("executing the system command failed\n");
		return 1;
	}
	return 0;
}
