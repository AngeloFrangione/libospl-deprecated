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
	sprintf(lib_name, "test_Library_6_%d", r);
	if (ospl_album_create(lib_name, "Vacances") >= 0)
	{
		printf("no error executing ospl_album_create\n");
		return 0;
	}

	if (ospl_create_library(lib_name) < 0)
	{
		printf("Error executing ospl_create_library\n");
		printf("lib_name: %s\n", lib_name);
		return 0;
	}
	sprintf(tmp, "%s/photos/Vacances", lib_name);
	create_directory(tmp);
	if (ospl_album_create(lib_name, "Vacances") >= 0)
	{
		printf("no error executing ospl_album_create\n");
		return 0;
	}
	if (remove_dir(lib_name))
	{
		printf("executing remove_dir function failed\n");
		return 0;
	}
	return 1;
}
