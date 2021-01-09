# ospl_photo_associated_album
(since version 0.1.0)  
get the albums where a specific photo is stored


## Description
```c
int ospl_photo_associated_album(char *library, int photo, t_album *list);
```
This function lists every album where a specific photo is stored and puts them into a [``t_album``](/{{ site.baseurl }}/reference#data-structures) ``struct``


## Parameters
**`library`**: the path of an ospl library.  
**`photo`**: the ``id`` of the photo to lookup for.  
**`list`**: a pointer to the first [`t_album`](/{{ site.baseurl }}/reference) structure, this should be statically allocated or dynamically allocated with ``malloc``. 

## Return values

|``value``    | ``signification``                            |
|-------------|----------------------------------------------|
|``SUCCESS``  | no errors occured during operation           |
|``EDBFAIL``  | an error occurred when accessing to database |


## Example
```c
#include <ospl.h>

int main(void)
{
	int ret;
	char *library = "path/to/photo/library/";
	t_album albums[128] = { 0 };
	int photo_id 29;

	if ((ret = ospl_photo_associated_album(library, photo_id, albums)) < 0)
	{
		printf("Failed to list albums associated with photo %d: %s", photo_id, ospl_enum_error(ret));
		return 1;
	}
	else
	{
		int i = 0;
		while(albums[i].id) // if id is 0 nothing has been pushed and it means end of the list. Only works if the list has been initialized with zeroes.
		{
			printf("%3d | %10s\n", albums[i].id, albums[i].name);
			++i;
		}
	}
}
```

## Changelog

|``version`` | ``description``                     |
|------------|-------------------------------------|
|``v0.1.0``  | ``the function is introduced``      |
