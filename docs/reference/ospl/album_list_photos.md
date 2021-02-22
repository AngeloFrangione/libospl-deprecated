# ospl_album_list_photos
(since version 0.1.0)  
get the photo list from an album



## Description

```c
int ospl_album_list_photos(char *library, int album, t_photos *list);
```
This function lists every photo inside a specific album from an ospl library and puts them into a [`t_photos`](/{{ site.baseurl }}/reference#data-structures) `struct`

## Parameters

**`library`**: the path of an ospl library.  
**`list`**: a pointer to the first [`t_photos`](/{{ site.baseurl }}/reference#data-structures) structure, this should be statically allocated or dynamically allocated with `malloc`. 


## Return values

| `value`   | `signification`                              |
| --------- | -------------------------------------------- |
| `SUCCESS` | no errors occurred during operation          |
| `ERR_DB`  | an error occurred when accessing to database |


## Example

```c
#include <ospl.h>

int main(void)
{
	int ret;
	char *library = "path/to/photo/library/";
	t_photos photos[1024] = { 0 };
	int album_id = 1;

	if ((ret = ospl_album_list_photos(library, album_id, photos)) < 0)
	{
		printf("Failed to list photos from album %d: %s", album_id, ospl_enum_error(ret));
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

| `version` | `description`                           |
| --------- | --------------------------------------- |
| `v0.1.1`  | adapting to the new error return system |
| `v0.1.0`  | the function is introduced              |
