#include "includes/ospl.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <sys/time.h>


int main(void)
{
	struct timeval nstime;
	char lib_name[50];

	gettimeofday(&nstime, NULL);
	srand(nstime.tv_usec);
	int r = rand();
	sprintf(lib_name, "test_Library_12_%d", r);
	if (ospl_create_library(lib_name) < 0)
	{
		printf("Error executing ospl_create_library\n");
		printf("lib_name: %s\n", lib_name);
		return 0;
	}
	if (ospl_album_create(lib_name, "Album of random photos") < 0)
	{
		printf("error executing ospl_album_create\n");
		return 0;
	}
	if (ospl_import_folder_in_album(lib_name, "../test_files/not/", 1))
	{
		printf("no error executing ospl_import_folder_in_album\n");
		return 0;
	}
	if (remove_dir(lib_name))
	{
		printf("executing remove_dir function failed\n");
		return 0;
	}
	return 1;
}
