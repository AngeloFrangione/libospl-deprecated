# ospl_import_folder_in_album
(since version 0.1.0)  
import a folder full of photos directly into an existing album

## Description
```c
int ospl_import_folder_in_album(char *library, char *path, int album);
```
This function will import an entire folder located at ``path`` of photos into an ospl library located at ``library``

## Parameters
**`library`**: the path of an ospl library.  
**``path``**: the path of the folder, containing photos.
**``album``**: the ``id`` of an existing album  


## Return values

|``value``    | ``signification``                                 |
|-------------|---------------------------------------------------|
|``SUCCESS``  | library successfully created                      |
|``ENOTFOUND``| the folder was not found                          |



## Example
```c
#include <ospl.h>

int main(void)
{
	int ret;
	int album_id = 1;
	char *library = "path/to/photo/library";
	if ((ret = ospl_import_folder_in_album(library, "path/to/folder/with/photos/"), album_id) < 0)
	{
		printf("Failed to import folder: %s", ospl_enum_error(ret));
		return 1;
	}
	else
		printf("Successfully imported folder in album %d", album_id);
}
```

## Behavior

This function calls **[``ospl_import_photo_in_album``](/{{ site.baseurl }}/reference/ospl_import_photo_in_album)** with every file in the given folder.


## Changelog

|``version`` | ``description``                     |
|------------|-------------------------------------|
|``v0.1.0``  | ``the function is introduced``      |


## Enhancements

- This function could return a specific error if the album does not exist by checking first if the album exists. Or do another function with this behavior.
- This function should return a list of success/fail of every file found in the folder.
- This function should use sqlite transactions to speed up the import process.
