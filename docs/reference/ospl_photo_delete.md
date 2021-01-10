# ospl_photo_delete
(since version 0.1.0)  
delete a specific photo from a library

## Description
```c
int ospl_photo_delete(char *library, int id);
```
This function deletes the photo ``id`` photo from an ospl.

## Parameters
**`library`**: the path of an ospl library.  
**``id``**: the ``id`` of the photo that will be deleted.  


## Return values

| ``value``   | ``signification``                                 |
| ----------- | ------------------------------------------------- |
| ``SUCCESS`` | photo successfully removed from library           |
| ``EERRNO``  | a system error occurred, use perror() to show it   |


## Example
```c
#include <ospl.h>

int main(void)
{
	int ret;
	char *library = "path/to/photo/library/";
	int photo_id = 49;

	if ((ret = ospl_photo_delete(library, photo_id)) < 0)
	{
		printf("Failed to remove photo %d from library: %s", photo_id,  ospl_enum_error(ret));
		return 1;
	}
	else
		printf("Photo successfully removed.");
	return 0;
}
```

## Behavior

This function gets the photo names then deletes the picture from library, and finally removes it from the import folder. 

## Changelog

| ``version`` | ``description``                 |
| ----------- | ------------------------------- |
| ``v0.1.0``  | ``the function is introduced``  |


## Enhancements

- delete also the photo from the album(s) it is.
- check if the photo exist, if not return error message.
- check sql return.
