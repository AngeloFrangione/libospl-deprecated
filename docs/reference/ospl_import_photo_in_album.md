# ospl_import_photo_in_album

(since version 0.1.0)  
import a photo directly into an existing album.

## Description

```c
int ospl_import_photo_in_album(char *library, char *path, int album);
```

This functions imports a photo located at ``path`` in an ospl library located at ``library`` into album with id ``album``

## Parameters

**`library`**: the path of an ospl library.  
**`path`**: the path of a photo.  
**``album``**: the ``id`` of an existing album  



## Supported formats

| format  | compatible since version |
| ------- | ------------------------ |
| ``JPG`` | ``0.1.0``                |



## Return values

| ``value``     | ``signification``                                 |
| ------------- | ------------------------------------------------- |
| ``SUCCESS``   | photo successfully imported  into album ``album`` |
| ``ENOTFOUND`` | the photo ``path`` given does not exist           |
| ``EDBFAIL``   | an error occurred when accessing to database      |



## Example

```c
#include <ospl.h>

int main(void)
{
	int ret;
	char *library = "path/to/photo/library/";
	int album_id = 1;

	if ((ret = ospl_import_photo_in_album(library, "path/to/photo.jpg", album_id)) < 0)
	{
		printf("Failed to import photo: %s", ospl_enum_error(ret));
		return 1;
	}
	else
		printf("Photo imported successfully in album %d", album_id);
	return 0;
}
```

## Behavior

This function imports the picture, then adds  it to the specified album. If the album doesn't exist, the photo will still be imported, and no error is returned.


## Changelog

| ``version`` | ``description``                 |
| ----------- | ------------------------------- |
| ``v0.1.0``  | ``the function is introduced``  |



## Enhancements

- This function could return a specific error if the album does not exist by checking first if the album exists. Or do another function with this behavior.
