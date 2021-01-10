# ospl_album_move_photo
(since version 0.1.0)  
move a photo from an album to another album



## Description
```c
int ospl_album_move_photo(char *library, int photo, int old, int new);
```
This function moves a photo ``photo`` from album ``old`` to album ``new``.


## Parameters
**`library`**: the path of an ospl library.  
**``photo``**: the photo ``id`` that will be moved.  
**``old``**: the album ``id`` where the photo is currently in.  
**``new``**: the album ``id`` where the photo will be moved.  

## Return values

|``value``    | ``signification``                            |
| ----------- | -------------------------------------------- |
| ``SUCCESS`` | photo removed from album successfully        |
| ``EDBFAIL`` | an error occurred when accessing to database |


## Example
```c
#include <ospl.h>

int main(void)
{
	int ret;
	int old_album_id = 12;
	int new_album_id = 7;
	int photo_id = 370;
	char *library = "path/to/photo/library/";
	
	if ((ret = ospl_album_move_photo(library, photo_id, old_album_id, new_album_id)) < 0)
	{
		printf("Failed to move photo %d from album %d to album %d: %s", photo_id, old_album_id, new_album_id, ospl_enum_error(ret));
		return 1;
	}
	else
		printf("Photo successfully moved");
	return 0;
}
```

## Behavior

This function gets the photo name and album names from database, then it moves the photo in the database, and finally moves the photo hard link to the new album.

## Changelog

| ``version`` | ``description``                 |
| ----------- | ------------------------------- |
| ``v0.1.0``  | ``the function is introduced``  |


## Enhancements

- return a not found value when an album or a photo does not exist
