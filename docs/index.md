### What is libospl ?
libospl is a fast C library for easily managing a photolibrary. You can use libospl to manage your folders, albums, photos, import folders of photos. It will generate automaticly a thumbnail and put the photos in the place. All informations are stored into an sqlite3 database.
### Example 
```c
#include <ospl.h>

int main(void)
{
	int ret;
	char *library = "path/to/photo/library";
	if ((ret = ospl_create_library(library)) < 0)
	{
		printf("Failed to create library: %s", ospl_enum_error(ret));
		return 1;
	}
	if ((ret = ospl_import_photo(library, "path/to/photo.jpg")) < 0)
	{
		printf("Failed to import photo: %s", ospl_enum_error(ret));
		return 1;
	}
}
```

This will create a library at `path/to/photo/library` and import the photo located at `path/to/photo.jpg`
