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
	sprintf(lib_name, "test_Library_15_%d", r);
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
	r = ospl_album_delete(lib_name, 1);
	if (r < 0)
	{
		printf("executing ospl_album_delete failed\n");
		printf("%s", ospl_enum_error(r));
		return 1;
	}
	sprintf(tmp, "%s/photos/Vacances", lib_name);
	if (folder_exists(tmp))
	{
		printf("album folder still here altho it was deleted: %s\n", tmp);
		return 1;
	}
	if (remove_dir(lib_name))
	{
		printf("executing remove_dir function failed\n");
		return 1;
	}
	return 0;
}
