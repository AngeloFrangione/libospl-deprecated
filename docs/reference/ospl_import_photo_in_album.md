# ospl_import_photo_in_album
(since version 0.1.0)  
import a photo directly into an existing album.



## Description

```c
int ospl_import_photo_in_album(char *library, char *path, int album);
```
This functions imports a photo located at `path` in an ospl library located at `library` into album with id `album`

## Parameters

**`library`**: the path of an ospl library.  
**`path`**: the path of a photo.  
**`album`**: the `id` of an existing album  


## Supported formats

| format | compatible since version |
| ------ | ------------------------ |
| `JPG`  | `0.1.0`                  |


## Return values

| `value`         | `signification`                                              |
| --------------- | ------------------------------------------------------------ |
| `SUCCESS`       | photo successfully imported  into album `album` inherited from `ospl_album_add_photo` |
| `ERR_NOT_FOUND` | the photo `path` given does not exist inherited from `ospl_import_photo` |
| `ERR_DB`        | an error occurred when accessing to database inherited from `ospl_import_photo` or `ospl_album_add_photo` |
| `ERR_ALB_NF`    | album not found with this `id` inherited from `ospl_album_add_photo` |
| `< -1000`       | a system error occurred, adding +1000 to this value gives the `errno` associated with the error inherited from `ospl_import_photo` or `ospl_album_add_photo` |


## Example

```c
#include <ospl.h>

int main(void)
{
	int ret;
	char *library = "path/to/photo/library/";
	int album_id = 1;

	if ((ret = ospl_import_photo_in_album(library, "path/to/photo.jpg", album_id)) < 0)
	{
		printf("Failed to import photo: %s", ospl_enum_error(ret));
		return 1;
	}
	else
		printf("Photo imported successfully in album %d", album_id);
	return 0;
}
```


## Behavior

This function imports the photo, then adds  it to the specified album. If the album doesn't exist, the photo will still be imported, and an error is reported.


## Changelog

| `version` | `description`                           |
| --------- | --------------------------------------- |
| `v0.1.1`  | adapting to the new error return system |
| `v0.1.0`  | the function is introduced              |


## Enhancements

- Do not import photo if album do not exist. (scheduled for `v0.1.1`)
