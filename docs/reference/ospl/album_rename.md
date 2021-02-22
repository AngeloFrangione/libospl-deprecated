# ospl_album_rename
(since version 0.1.0)  
rename an album from an ospl library



## Description

```c
int ospl_album_rename(char *library, int album, char *name);
```
This functions renames the album with id `id` to a new name `name`
It also renames the album folder located in `library/photos/`


## Parameters

**`library`**: the path of an ospl library.  
**`album`**: the  `id` of the album that will be renamed.  
**`name`**: the new name of the album.  


## Return values

| `value`      | `signification`                                                                                 |
| ------------ | ----------------------------------------------------------------------------------------------- |
| `SUCCESS`    | album successfully renamed                                                                      |
| `ERR_DB`     | an error occurred when accessing to database                                                    |
| `ERR_ALB_NF` | album not found with this `id`                                                                  |
| `< -1000`    | a system error occurred, adding +1000 to this value gives the `errno` associated with the error |


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
	return 0;
}
```


## Behavior

This function  starts by trying to find if the album, if it exists, then the album is renamed in database. if it succeeds, it will  rename the folder of the album.


## Changelog

| `version` | `description`                           |
| --------- | --------------------------------------- |
| `v0.1.1`  | adapting to the new error return system |
| `v0.1.0`  | the function is introduced              |
