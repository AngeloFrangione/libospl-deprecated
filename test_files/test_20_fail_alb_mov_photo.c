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
	t_album album;
	if (ospl_photo_associated_album(lib_name, 1, &album) != ERR_PHO_NF)
	{
		printf("no error executing ospl_photo_associated_album\n");
		return 0;
	}
	t_photos pho;
	if (ospl_album_list_photos(lib_name, 2, &pho) != ERR_ALB_NF)
	{
		printf("no error executing ospl_album_list_photos\n");
		return 0;
	}
	if (remove_dir(lib_name))
	{
		printf("executing remove_dir function failed\n");
		return 0;
	}
	return 1;
}
