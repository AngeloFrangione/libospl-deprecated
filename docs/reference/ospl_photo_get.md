# ospl_photo_get
(since version 0.1.0)  
get informations about a specific photo

## Description
```c
int ospl_photo_get(char *library, int id, t_photos *photo);
```
This function gets information about a photo and puts them into a [``t_photos``](/{{ site.baseurl }}/reference#data-structures) ``struct``

## Parameters
**`library`**: the path of an ospl library.  
**``id``**: the ``id`` of a photo.  
**``photo``**: the [``t_photos``](/{{ site.baseurl }}/reference#data-structures) ``struct`` that will be completed, this should be statically allocated or dynamically allocated with ``malloc``. 

## Return values

| ``value``   | ``signification``                            |
| ----------- | -------------------------------------------- |
| ``SUCCESS`` | no errors occurred during operation          |
| ``EDBFAIL`` | an error occurred when accessing to database |


## Example
```c
#include <ospl.h>

int main(void)
{
	int ret;
	char *library = "path/to/photo/library/";
	int photo_id = 32;
	t_photos photo = { 0 };

	if ((ret = ospl_photo_get(library, photo_id, photo)) < 0)
	{
		printf("Failed to get info about picture with id %d: %s", photo_id, ospl_enum_error(ret));
		return 1;
	}
	else
		printf("original name: %s\n import year: %d", photo.original_name, photo.import_year);
	return 0;
}
```

## Changelog

| ``version`` | ``description``                 |
| ----------- | ------------------------------- |
| ``v0.1.0``  | ``the function is introduced``  |


## Enhancements

- return a ENOTFOUND error if the picture doesn't exist.

