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
	t_photos pho = { 0 };

	gettimeofday(&nstime, NULL);
	srand(nstime.tv_usec);
	int r = rand();
	sprintf(lib_name, "test_Library_4_%d", r);
	if (ospl_import_photo(lib_name, "../test_files/ressources/1b3BAEr6IJk.jpg") >= 0)
	{
		printf("No error executing ospl_import_photo\n");
		return 0;
	}
	if (ospl_create_library(lib_name) < 0)
	{
		printf("Error executing ospl_create_library\n");
		printf("lib_name: %s\n", lib_name);
		return 0;
	}
	if (ospl_import_photo(lib_name, "../test_files/ressources/1b3BAEr6IJk.jpg") < 0)
	{
		printf("an error executing ospl_import_photo\n");
		return 0;
	}
	if (ospl_photo_get(lib_name, 10, &pho) >= 0)
	{
		printf("No error executing ospl_photo_get\n");
		return 0;
	}
	if (ospl_import_photo(lib_name, "../test_files/ressources/not.jpg") >= 0)
	{
		printf("No error executing ospl_import_photo\n");
		return 0;
	}
	sprintf(tmp, "rm -rf %s", lib_name);
	if (system(tmp))
	{
		printf("executing the system command failed\n");
		return 0;
	}
	if (ospl_photo_get(lib_name, 1, &pho) >= 0)
	{
		printf("No error executing ospl_photo_get\n");
		return 0;
	}
	sprintf(tmp, "%s/photos/import/%s", lib_name, pho.new_name);
	if (file_exists(tmp))
	{
		printf("photo present in import folder: %s\n", tmp);
		return 0;
	}
	return 1;
}
