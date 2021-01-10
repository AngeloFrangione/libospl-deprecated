# ospl_album_create
(since version 0.1.0)  
create an album in an ospl library

## Description
```c
int ospl_album_create(char *library, char *name);
```
This function creates an album named ``name`` into an ospl provided with ``library``. It will create a new folder into the ``library/photos/`` folder.

## Parameters
**`library`**: the path of an ospl library.  
**`name`**: the name of the album.

## Return values

|``value``     | ``signification``                                |
| ------------ | ------------------------------------------------ |
| ``SUCCESS``  | album successfully created                       |
| ``EAEXISTS`` | the path given already exists                    |
| ``EDBFAIL``  | an error occurred when accessing to database     |
| ``EERRNO``   | a system error occurred, use perror() to show it |


## Example
```c
#include <ospl.h>

int main(void)
{
	int ret;
	char *library = "path/to/photo/library/";

	if ((ret = ospl_album_create(library, "Vacation in Tokyo - 1994")) < 0)
	{
		printf("Failed to create album: %s", ospl_enum_error(ret));
		return 1;
	}
	else
		printf("Album successfully created.");
	return 0;
}
```

## Behavior

This function creates the album into the library first. If it fails the directory isn't created. 

## Changelog

| ``version`` | ``description``                 |
| ----------- | ------------------------------- |
| ``v0.1.0``  | ``the function is introduced``  |

## Enhancements

- return the created album ``id`` on success.
