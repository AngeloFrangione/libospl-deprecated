# ospl_import_folder_in_album
(since version 0.1.0)  
import a folder full of photos directly into an existing album



## Description

```c
int ospl_import_folder_in_album(char *library, char *path, int album);
```
This function will import an entire folder located at `path` of photos into an ospl library located at `library`


## Parameters
**`library`**: the path of an ospl library.  
**`path`**: the path of the folder, containing photos.
**`album`**: the `id` of an existing album  


## Return values

| `value`            | `signification`                                                               |
| ------------------ | ----------------------------------------------------------------------------- |
| `t_import_status*` | folder successfully imported                                                  |
| `NULL`             | the folder or album was not found, or an error occured while executing malloc |


## Example

```c
#include <ospl.h>
#include <ospl.h>

int main(void)
{
	t_import_status *status;
	char *library = "path/to/photo/library/";
	int album_id = 1;

	if (!(status = ospl_import_folder_in_album(library, "path/to/folder/with/photos/", album_id)))
	{
		printf("Failed to import folder: The folder or the album doesn't exist. Or allocating memory failed.");
		return 1;
	}
	else
    {
        printf("Successfully imported folder into album:");
        while (status->path)
        {
            if (status->id < 0)
                printf("status: %d |", ospl_enum_error(status->id));
            else
                printf("status: successfully imported |");
            printf(" path: %s", status->path);
        }
        free_import_status(&status);
    }
	return 0;
}
```


## Behavior

This function calls **[`ospl_import_folder`](/{{ site.baseurl }}/reference/ospl_import_folder)**, If it succeeds, it adds every photo to the album calling **[`ospl_album_add_photo`](/{{ site.baseurl }}/reference/ospl_album_add_photo)** using the `t_import_status*` returned by `ospl_import_folder`. 


## Changelog

| `version` | `description`                                                       |
| --------- | ------------------------------------------------------------------- |
| `v0.1.1`  | adapting to the new error return system & return `t_status_import*` |
| `v0.1.0`  | the function is introduced                                          |


## Enhancements

- This function should use sqlite transactions to speed up the import process. (scheduled for `v0.2.0`)
