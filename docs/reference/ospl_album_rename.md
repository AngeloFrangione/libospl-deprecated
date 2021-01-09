# ospl_album_rename
(since version 0.1.0)  
rename an album from an ospl library

## Description
```c
int ospl_album_rename(char *library, int id, char *name);
```
This functions renames the album with id ``id`` to a new name ``name``
It also renames the album folder located in ``library/photos/``

## Parameters
**`library`**: the path of an ospl library.  
**``id``**: the album ``ìd`` that will be renamed.  
**``name``**: the new name of the album.  

## Return values

|``value``    | ``signification``                                 |
|-------------|---------------------------------------------------|
|``SUCCESS``  | album successfully renamed                        |
|``EDBFAIL``  | an error occurred when accessing to database      |
|``ENOTFOUND``| album not found with this ``id``                  |
|``EERRNO``   | a system error eccured, use perror() to show it   |


## Example
```c
#include <ospl.h>

int main(void)
{
	int ret;
	char *library = "path/to/photo/library/";
	int album_id = 12;

	if ((ret = ospl_album_rename(library, album_id)) < 0)
	{
		printf("Failed to rename album: %s", ospl_enum_error(ret));
		return 1;
	}
	else
		printf("Album successfully renamed.");
}
```

## Behavior

This function first try's to find if the album exists, then it renames the folder of the album, if it succeeds, the album is renamed in database.


## Changelog

|``version`` | ``description``                     |
|------------|-------------------------------------|
|``v0.1.0``  | ``the function is introduced``      |


## Enhancements

- If renaming in database fails do not rename the folder. 
