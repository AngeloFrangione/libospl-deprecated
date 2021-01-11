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
	sprintf(lib_name, "test_Library_16_%d", r);
	if (ospl_album_delete(lib_name, 1) >= 0)
	{
		printf("no errorexecuting ospl_album_delete\n");
		return 0;
	}
	if (ospl_create_library(lib_name) < 0)
	{
		printf("Error executing ospl_create_library\n");
		printf("lib_name: %s\n", lib_name);
		return 0;
	}
	if (ospl_album_delete(lib_name, 1) >= 0)
	{
		printf("no error executing ospl_album_delete\n");
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
