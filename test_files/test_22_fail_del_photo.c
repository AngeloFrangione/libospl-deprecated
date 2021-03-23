#include "includes/ospl.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <sys/time.h>


int main(void)
{
	struct timeval nstime;
	char lib_name[50];
	int ret;

	gettimeofday(&nstime, NULL);
	srand(nstime.tv_usec);
	int r = rand();
	sprintf(lib_name, "test_Library_22_%d", r);
	if ((ret = ospl_photo_delete(lib_name, 1)) != ERR_DB)
	{
		printf("wrong error returned executing ospl_photo_delete(expected: %d): %d\n",ERR_DB, ret);
		return 0;
	}
	if (ospl_create_library(lib_name) < 0)
	{
		printf("Error executing ospl_create_library\n");
		printf("lib_name: %s\n", lib_name);
		return 0;
	}
	if ((ret = ospl_photo_delete(lib_name, 1)) != ERR_PHO_NF)
	{
		printf("wrong error returned executing ospl_photo_delete(expected: %d): %d\n",ERR_PHO_NF, ret);
		return 0;
	}
	if (remove_dir(lib_name))
	{
		printf("executing remove_dir function failed\n");
		return 0;
	}
	return 1;
}
