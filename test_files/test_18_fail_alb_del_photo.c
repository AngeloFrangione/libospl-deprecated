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
	sprintf(lib_name, "test_Library_18_%d", r);
	if (ospl_album_delete_photo(lib_name, 1, 1) >= 0)
	{
		printf("no error executing ospl_album_delete_photo\n");
		return 0;
	}
	return 1;
}
