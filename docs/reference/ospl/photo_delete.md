# ospl_photo_delete
(since version 0.1.0)  
delete a specific photo from a library



## Description

```c
int ospl_photo_delete(char *library, int photo);
```
This function deletes the photo with `id` `photo` photo from an ospl.


## Parameters

**`library`**: the path of an ospl library.  
**`photo`**: the `id` of the photo that will be deleted.  


## Return values

| `value`      | `signification`                                                                                 |
| ------------ | ----------------------------------------------------------------------------------------------- |
| `SUCCESS`    | photo successfully removed from library                                                         |
| `ERR_DB`     | an error occurred when accessing to database                                                    |
| `ERR_PHO_NF` | photo not found with `id` `photo`                                                               |
| `< -1000`    | a system error occurred, adding +1000 to this value gives the `errno` associated with the error |


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

This function gets the photo names then deletes the photo from library, and finally removes it from the import folder. 


## Changelog

| `version` | `description`                                                                   |
| --------- | ------------------------------------------------------------------------------- |
| `v0.1.1`  | adapting to the new error return system & return error if photo does not exists |
| `v0.1.0`  | the function is introduced                                                      |


## Enhancements

- Delete also the photo from the album(s) it is. (scheduled for `v0.2.0`)
