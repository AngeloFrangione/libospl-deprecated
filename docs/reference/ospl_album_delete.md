# ospl_album_delete
(since version 0.1.0)  
delete an album from an ospl library

## Description
```c
int ospl_album_delete(char *library, int id);
```
This function deletes the album with id ``id`` from the databse, it also removes the album folder located at ``library/photos/``

## Parameters
**`library`**: the path of an ospl library.  
**``id``** the album ``id`` that will be deleted.  

## Return values

| ``value``     | ``signification``                                |
| ------------- | ------------------------------------------------ |
| ``SUCCESS``   | album successfully deleted                       |
| ``EDBFAIL``   | an error occurred when accessing to database     |
| ``ENOTFOUND`` | album not found with this ``id``                 |
| ``EERRNO``    | a system error occurred, use perror() to show it |


## Example
```c
#include <ospl.h>

int main(void)
{
	int ret;
	char *library = "path/to/photo/library/";
	int album_id = 12;

	if ((ret = ospl_album_delete(library, album_id)) < 0)
	{
		printf("Failed to delete album: %s", ospl_enum_error(ret));
		return 1;
	}
	else
		printf("Album successfully deleted");
	return 0;
}
```

## Behavior

This function checks if the album exist, if it does, it will be deleted from the databse, if the removal from the database succeeds, the folder is removed, including every photo hardlink inside.

## Changelog

| ``version`` | ``description``                 |
| ----------- | ------------------------------- |
| ``v0.1.0``  | ``the function is introduced``  |
