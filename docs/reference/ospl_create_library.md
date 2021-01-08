# ospl_create_library
(since version 0.1.0)  
create a ospl library

## Description
```c
int ospl_create_library(char *library);
```
This functions creates a ospl library at the given path. How is an ospl library structured ? see [``ospl_structure``](/{{ site.baseurl }}/reference#structure)

## Parameters
**`library`**: the path where the library will be created.

## Return values

|``value``    | ``signification``                                 |
|-------------|---------------------------------------------------|
|``SUCCESS``  | ``library successfully created``                  |
|``EAEXISTS`` | ``the path given already exists``                 |
|``EDBFAIL``  | ``an error occured when accessing to database``   |

## Example
```c
#include <ospl.h>

int main(void)
{
	int ret;
	char *library = "path/to/photo/library";
	if ((ret = ospl_create_library(library)) < 0)
	{
		printf("Failed to create library: %s", ospl_enum_error(ret));
		return 1;
	}
	else
		printf("library successfully created");
}
```

## Behavior

This function create a library by first creating the folder named after the library, if success, it will create the photos folder, then the import folder, and finally, the thumbnails fodlder. If every folder creation is a success, the database file is created. Learn more at [``ospl_structure``](/{{ site.baseurl }}/reference#structure)

## Changelog

|``version`` | ``description``                     |
|------------|-------------------------------------|
|``v0.1.0``  | ``the function is introduced``      |

## Enhancements

- If a failure occurs, try to remove the already created folders.
