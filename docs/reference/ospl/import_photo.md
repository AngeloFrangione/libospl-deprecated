# ospl_import_photo
(since version 0.1.0)  
import a photo into library



## Description

```c
int ospl_import_photo(char *library, char *path);
```
This functions imports a folder located at `path` in an ospl library located at  `library` into album with id `album`


## Parameters

**`library`**: the path of an ospl library.  
**`path`**: the path of a photo.


## Supported formats

| format | compatible since version |
| ------ | ------------------------ |
| `JPG`  | `0.1.0`                  |


## Return values

| `value`         | `signification`                                              |
| --------------- | ------------------------------------------------------------ |
| `id`            | the id of the photo is returned on success                   |
| `ERR_NOT_FOUND` | the photo `path` given does not exist                        |
| `ERR_DB`        | an error occurred when accessing to database                 |
| `< -1000`       | a system error occurred, adding +1000 to this value gives the `errno` associated with the error |


## Example

```c
#include <ospl.h>

int main(void)
{
	int ret;
	char *library = "path/to/photo/library/";
	char *path = "path/to/picture.jpg"

	if ((ret = ospl_import_photo(library, path)) < 0)
	{
		printf("Failed to import photo: %s", ospl_enum_error(ret));
		return 1;
	}
	else
		printf("Photo imported successfully");
	return 0;
}
```


## Behavior

Since version 0.2.0 this function is a shortcut. It calls **[`ospl_import_photo_t`](/{{ site.baseurl }}/reference/ospl/import_photo_t)** passing NULL as transaction parameter.


## Changelog

| `version` | `description`                                         |
| --------- | ----------------------------------------------------- |
| `v0.2.0`  | the brain of this function is moved to **[`ospl_import_photo_t`](/{{ site.baseurl }}/reference/ospl/import_photo_t)**. It will call it with NULL as 3rd parameter |
| `v0.1.1`  | adapting to the new error return system               |
| `v0.1.0`  | the function is introduced                            |
