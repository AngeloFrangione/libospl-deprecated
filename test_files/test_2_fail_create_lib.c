#include "includes/ospl.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <sys/time.h>

int main(void)
{
	struct timeval nstime;
	char tmp[50] = {0};
	char lib_name[50];

	gettimeofday(&nstime, NULL);
	srand(nstime.tv_usec);
	int r = rand();
	sprintf(lib_name, "test_Library_2_%d", r);
	if (ospl_create_library(lib_name) < 0)
	{
		printf("Error executing ospl_create_library\n");
		printf("lib_name: %s\n", lib_name);
		return 0;
	}
	if (ospl_create_library(lib_name) < 0)
	{
		printf("Error executing ospl_create_library\n");
		printf("lib_name: %s\n", lib_name);
	}
	sprintf(tmp, "rm -rf %s", lib_name);
	if (system(tmp))
	{
		printf("executing the system command failed\n");
		return 0;
	}
	if (folder_exists(lib_name))
	{
		printf("No lib folder found\n");
		return 0;
	}
	sprintf(tmp, "%s/database.db", lib_name);
	if (file_exists(tmp))
	{
		printf("No db found\n");
		return 0;
	}
	sprintf(tmp, "%s/thumbnails", lib_name);
	if (folder_exists(tmp))
	{
		printf("No thumbnails folder found\n");
		return 0;
	}
	sprintf(tmp, "%s/photos", lib_name);
	if (folder_exists(tmp))
	{
		printf("No photos folder found\n");
		return 0;
	}
	sprintf(tmp, "%s/photos/import/", lib_name);
	if (folder_exists(tmp))
	{
		printf("No import folder found\n");
		return 0;
	}
	if (library_exists(lib_name))
	{
		printf("the library_exists function didn't found a library altho it exists\n");
		return 0;
	}
	return 1;
}
