# ospl_album_delete_photo
(since version 0.1.0)  
delete a photo from an album


## Description
```c
int ospl_album_delete_photo(char *library, int photo, int album);
```
This function removes a photo ``photo`` from an album ``album``.


## Parameters
**`library`**: the path of an ospl library.  
**``photo``**: the photo ``id`` that will be removed from the album.  
**``album``**: the album ``id`` that contains the photo that will be removed.  

## Return values

| ``value``   | ``signification``                            |
| ----------- | -------------------------------------------- |
| ``SUCCESS`` | photo removed from album successfully        |
| ``EDBFAIL`` | an error occurred when accessing to database |


## Example
```c
#include <ospl.h>

int main(void)
{
	int ret;
	int album_id = 12;
	int photo_id = 370;
	char *library = "path/to/photo/library/";
	
	if ((ret = ospl_album_delete_photo(library, photo_id, album_id)) < 0)
	{
		printf("Failed to remove photo %d from album %d: %s", photo_id, album_id, ospl_enum_error(ret));
		return 1;
	}
	else
		printf("Photo successfully removed from album");
	return 0;
}
```

## Behavior

This function gets the photo name and album name from database, then it removes the photo from the database, and finally delete the photo hard link.

## Changelog

| ``version`` | ``description``                 |
| ----------- | ------------------------------- |
| ``v0.1.0``  | ``the function is introduced``  |


## Enhancements

- return a not found value when an album or a photo does not exist
