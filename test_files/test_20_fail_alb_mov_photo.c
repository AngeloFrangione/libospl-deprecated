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
	sprintf(lib_name, "test_Library_20_%d", r);
	if (ospl_album_move_photo(lib_name, 1, 1, 2) >= 0)
	{
		printf("no error executing ospl_album_move_photo\n");
		return 0;
	}
	if (ospl_create_library(lib_name) < 0)
	{
		printf("Error executing ospl_create_library");
		printf("lib_name: %s\n", lib_name);
		return 0;
	}
	if (ospl_album_create(lib_name, "Vacances") < 0)
	{
		printf("error executing ospl_album_create\n");
		return 0;
	}
	if (ospl_album_move_photo(lib_name, 1, 2, 1) >= 0)
	{
		printf("no error executing ospl_album_move_photo\n");
		return 0;
	}
	if (ospl_album_move_photo(lib_name, 1, 1, 2) >= 0)
	{
		printf("no error executing ospl_album_move_photo\n");
		return 0;
	}
	if (ospl_album_move_photo(lib_name, 1, 1, 1) >= 0)
	{
		printf("no error executing ospl_album_move_photo\n");
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
