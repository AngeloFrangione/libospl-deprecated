#include <stdio.h>
#include "include/thumbnailer.h"

int main(int ac, char **av)
{
	printf("input: %s\n", av[1]);
	create_thumbnail(av[1], "output.jpg", 200);
	return 0;
}