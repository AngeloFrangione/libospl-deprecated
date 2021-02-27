# ospl_import_folder
(since version 0.1.0)  
import a folder full of photos



## Description

```c
int ospl_import_folder(char *library, char *path);
```
This function will import an entire folder located at `path` of photos into an ospl library located at `library`


## Parameters
**`library`**: the path of an ospl library.  
**`path`**: the path of the folder, containing photos.


## Return values

| `value`            | `signification`                                                      |
| ------------------ | -------------------------------------------------------------------- |
| `t_import_status*` | folder successfully imported                                         |
| `NULL`             | the folder was not found, or an error occured while executing malloc |


## Example

```c
#include <ospl.h>

int main(void)
{
	t_import_status *status;
	char *library = "path/to/photo/library/";

	if (!(status = ospl_import_folder(library, "path/to/folder/with/photos/")))
	{
		printf("Failed to import folder: It doesn't exist or allocating memory failed.");
		return 1;
	}
	else
    {
        printf("Successfully imported folder:");
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

This function calls **[`ospl_import_photo`](/{{ site.baseurl }}/reference/ospl_import_photo)** with every file in the given folder. 
It will return an array of [**`t_import_status*`**](/{{ site.baseurl }}/reference#data-structures) structures.
This array is dynamically allocated with malloc. The last element contains NULL in the `path` element from this structure.
You can free the entire array by calling this function:

```c
 void free_import_status(t_import_status **status);
```
the `id` element from the structure is filled with the return value of **[`ospl_import_photo_t`](/{{ site.baseurl }}/reference/ospl_import_photo_t)**
the `path` element from the structure is filled with the path of the file that ospl imported.


## Changelog

| `version` | `description`                                                       |
| --------- | ------------------------------------------------------------------- |
| `v0.2.0`  | using sqlite transaction mode to speed up the process               |
| `v0.1.1`  | adapting to the new error return system & return `t_status_import*` |
| `v0.1.0`  | the function is introduced                                          |

