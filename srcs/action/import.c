#include <stdio.h>
#include <thumbnailer.h>
#include "ospl.h"

int ospl_import_picture(char *library, char *path)
{
	if(!is_supported(path))
	{
		printf("image %s not supported\n", path);
		return 1;
	}

	return 0;
}
