# ospl_import_folder
(since version 0.1.0)  
import a folder full of photos

## Description
```c
int ospl_import_folder(char *library, char *path);
```

This function will import an entire folder located at ``path`` of photos into an ospl library located at ``library``


## Parameters
**`library`**: the path where the library will be created.  
**``path``**: the path of the folder, containing photos.


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
	char *library = "path/to/photo/library";
	if ((ret = ospl_import_folder(library, "path/to/folder/with/photos/")) < 0)
	{
		printf("Failed to import folder: %s", ospl_enum_error(ret));
		return 1;
	}
	else
		printf("Successfully imported folder");
}
```

## Behavior

This function calls **[``ospl_import_photo``](/{{ site.baseurl }}/reference/ospl_import_photo)** with every file in the given folder.


## Changelog

|``version`` | ``description``                     |
|------------|-------------------------------------|
|``v0.1.0``  | ``the function is introduced``      |


## Enhancements

- This function should return a list of success/fail of every file found in the folder.
- This function should use sqlite transactions to speed up the import process.
