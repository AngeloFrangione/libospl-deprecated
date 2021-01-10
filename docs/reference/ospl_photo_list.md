# ospl_photo_list
(since version 0.1.0)  
list every photo from a library

## Description
```c
int ospl_photo_list(char *library, t_photos *list);
```
This function list every photo in the library and put them into a [``t_photos``](/{{ site.baseurl }}/reference#data-structures) ``struct`` pointer


## Parameters
**`library`**: the path of an ospl library.  
**``list``**: a pointer to the first [`t_photos`](/{{ site.baseurl }}/reference#data-structures) structure, this should be statically allocated or dynamically allocated with ``malloc``.  


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
	t_photos photos[1024] = { 0 };

	if ((ret = ospl_photo_list(library, photos)) < 0)
	{
		printf("Failed to list photos: %s", ospl_enum_error(ret));
		return 1;
	}
	else
	{
		int i = 0;
		while(photos[i].id) // if id is 0 nothing has been pushed and it means end of the list. Only works if the list has been initialized with zeroes.
		{
			printf("%3d | %10s\n", photos[i].id, photos[i].original_name);
			++i;
		}
	}
	return 0;
}
```

## Changelog

| ``version`` | ``description``                 |
| ----------- | ------------------------------- |
| ``v0.1.0``  | ``the function is introduced``  |


## Enhancements

- be able to limit/range the number of photos, sort them by import date/shoot date, create a new function for that?
