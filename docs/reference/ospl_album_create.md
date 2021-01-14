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

| `value`      |  `signification`                                                                                |
| ------------ | ----------------------------------------------------------------------------------------------- |
| `SUCCESS`    | album successfully created                                                                      |
| `ERR_EXISTS` | there is already an album with that name                                                        |
| `ERR_DB`     | an error occurred when accessing to database                                                    |
| `< -1000`    | a system error occurred, adding +1000 to this value gives the `errno` associated with the error |


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

This function creates the album into the database first. If it fails the directory is not created. 


## Changelog

| `version` | `description`                           |
| --------- | --------------------------------------- |
| `v0.1.1`  | adapting to the new error return system |
| `v0.1.0`  | the function is introduced              |


## Enhancements

- Return the created album `id` on success. (scheduled for `v0.1.1`)
