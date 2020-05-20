#include "include/thumbnailer.h"

int main(int argc, char *argv[])
{
	if (argc < 3)
	{
		printf("no enough arguments\n");
		return 1;
	}
	create_thumbnail(argv[1], argv[2], 500);
	return 0;
}