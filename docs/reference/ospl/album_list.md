# ospl_album_list
(since version 0.1.0)  
get the entire album list stored in a library



## Description

```c
int ospl_album_list(char *library, t_album *list)
```
This function lists every album from an ospl library and puts them into a [`t_album`](/{{ site.baseurl }}/reference#data-structures) `struct`


## Parameters

**`library`**: the path of an ospl library.  
**`list`**: a pointer to the first [`t_album`](/{{ site.baseurl }}/reference#data-structures) structure, this should be statically allocated or dynamically allocated with `malloc`. 


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
	t_album albums[128] = { 0 };

	if ((ret = ospl_album_list(library, albums)) < 0)
	{
		printf("Failed to list albums: %s", ospl_enum_error(ret));
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
	return 0;
}
```


## Changelog

| `version` | `description`                           |
| --------- | --------------------------------------- |
| `v0.1.1`  | adapting to the new error return system |
| `v0.1.0`  | the function is introduced              |
