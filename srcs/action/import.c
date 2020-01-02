#include "ospl.h"

int ospl_import_picture(char *library, char *path)
{
	char **p = SUPPORTED_IMAGES;
	char *magic;

	get_magic(path, magic); 
}
