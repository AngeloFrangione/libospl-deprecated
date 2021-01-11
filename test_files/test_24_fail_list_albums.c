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
	t_album list[10];
	t_photos plist[10];
	
	gettimeofday(&nstime, NULL);
	srand(nstime.tv_usec);
	int r = rand();
	sprintf(lib_name, "test_Library_24_%d", r);
	if (ospl_album_list(lib_name, list) >= 0)
	{
		printf("no error executing ospl_list_albums\n");
		return 0;
	}

	if (ospl_album_list_photos(lib_name, 1, plist) >= 0)
	{
		printf("no error executing ospl_album_list_photos\n");
		return 0;
	}

	if (ospl_photo_associated_album(lib_name, 1, list) >= 0)
	{
		printf("no error executing ospl_photo_associated_album\n");
		return 0;
	}
	if (ospl_album_add_photo(lib_name, 1, 1) >= 0)
	{
		printf("no error executing ospl_album_add_photo\n");
		return 0;
	}
	return 1;
}
