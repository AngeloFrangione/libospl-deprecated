# ospl_album_add_photo
(since version 0.1.0)  
add a photo to an existing album



## Description

```c
int ospl_album_add_photo(char *library, int photo, int album);
```
This function adds an existing photo `photo` to an existing album `album`.


## Parameters

**`library`**: the path of an ospl library.  
**`photo`**: the photo `id` that will be added to the album.  
**`album`**: the album `id` that will contain the photo.  


## Return values

| `value`      | `signification`                                                                                 |
| ------------ | ----------------------------------------------------------------------------------------------- |
| `SUCCESS`    | photo added to album with success                                                               |
| `ERR_DB`     | an error occurred when accessing to database                                                    |
| `ERR_ALB_NF` | album not found with `id` `album`                                                               |
| `ERR_PHO_NF` | photo not found with `id` `photo`                                                               |
| `< -1000`    | a system error occurred, adding +1000 to this value gives the `errno` associated with the error |


## Example

```c
#include <ospl.h>

int main(void)
{
	int ret;
	int album_id = 12;
	int photo_id = 370;
	char *library = "path/to/photo/library/";

	if ((ret = ospl_album_add_photo(library, photo_id, album_id)) < 0)
	{
		printf("Failed to add photo %d to album %d: %s", photo_id, album_id, ospl_enum_error(ret));
		return 1;
	}
	else
		printf("Photo successfully added to album.");
	return 0;
}
```


## Behavior

This function adds the photo `photo` to the album `album` by adding them to the contains table, without verifying if any of them exists. Then it will create a hard link of the photo from the import folder to the album. A hard link does make show the same photo into another folder, without taking twice the space on the disk. 


## Changelog

| `version` | `description`                           |
| --------- | --------------------------------------- |
| `v0.1.1`  | adapting to the new error return system |
| `v0.1.0`  | the function is introduced              |
