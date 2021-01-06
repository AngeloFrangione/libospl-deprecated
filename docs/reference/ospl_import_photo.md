# ospl_import_photo

(since version 0.1.0)  
import a photo into library

## Description

```c
int ospl_import_photo(char *library, char *path);
```

This functions imports a photo located at ``path`` in an ospl library located at ``library``

## Parameters

**`library`**: the path of an ospl library.  
**`path`**: the path of a photo.



## Supported formats

| format  | compatible since version |
| ------- | ------------------------ |
| ``JPG`` | ``0.1.0``                |



## Return values

| ``value``     | ``signification``                            |
| ------------- | -------------------------------------------- |
| ``SUCCESS``   | photo successfully imported                |
| ``ENOTFOUND`` | the photo ``path`` given does not exist    |
| ``EDBFAIL``   | an error occurred when accessing to database |



## Example

```c
#include <ospl.h>

int main(void)
{
	int ret;
	char *library = "path/to/photo/library";
	if ((ret = ospl_create_library(library)) < 0)
	{
		printf("Failed to import photo: %s", ospl_enum_error(ret));
		return 1;
	}
	else
		printf("Photo imported successfully");
}
```



## Changelog

| ``version`` | ``description``                |
| ----------- | ------------------------------ |
| ``v0.1.0``  | ``the function is introduced`` |
