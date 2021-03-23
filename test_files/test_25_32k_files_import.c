#include "includes/ospl.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <sys/time.h>


int main(void)
{
	struct timeval nstime;
	char lib_name[50];

	gettimeofday(&nstime, NULL);
	srand(nstime.tv_usec);
	int r = rand();
	sprintf(lib_name, "test_Library_25_%d", r);
	if (ospl_create_library(lib_name) < 0)
	{
		printf("Error executing ospl_create_library\n");
		printf("lib_name: %s\n", lib_name);
		return 1;
	}
	t_import_status *status;
	status = ospl_import_folder(lib_name, "../test_files/ressources/empty_files/");
	if (status[0].id != ERR_NOT_SUPPORTED && status[32499].id != ERR_NOT_SUPPORTED)
	{
		printf("there is an error with more than 32k files in folder to import\n");
	}
	free_import_status(&status);
	if (remove_dir(lib_name))
	{
		printf("executing remove_dir function failed\n");
		return 1;
	}
	return 0;
}
