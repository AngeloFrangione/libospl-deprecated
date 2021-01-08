# ospl_import_photo

(since version 0.1.0)  
import a photo into library

## Description

```c
int ospl_import_photo(char *library, char *path);
```

This functions imports a folder located at ``path`` in an ospl library located at  ``library`` into album with id ``album``

## Parameters

**`library`**: the path of an ospl library.  
**`path`**: the path of a photo.



## Supported formats

| format  | compatible since version |
| ------- | ------------------------ |
| ``JPG`` | ``0.1.0``                |



## Return values

| ``value``     | ``signification``                            |
| ------------- | -------------------------------------------- |
| ``id``        | the id of the photo is           |
| ``ENOTFOUND`` | the photo ``path`` given does not exist      |
| ``EDBFAIL``   | an error occurred when accessing to database |



## Example

```c
#include <ospl.h>

int main(void)
{
	int ret;
	char *library = "path/to/photo/library";
	if ((ret = ospl_create_library(library)) < 0)
	{
		printf("Failed to import photo: %s", ospl_enum_error(ret));
		return 1;
	}
	else
		printf("Photo imported successfully");
}
```

## Behavior

This function will extract informations about a picture, like the name, an ``md5`` hash. It will copy the actual time. And insert the photo into the database, if success, it will copy the picture into the ``library/photos/import`` folder with a new name composed of it's original name and the import date and time. If success, it will create a thumbnail into the ``library/thumbnails/`` folder. if success, the ``id`` of the just inserted photo is returned.

## Changelog

| ``version`` | ``description``                |
| ----------- | ------------------------------ |
| ``v0.1.0``  | ``the function is introduced`` |
