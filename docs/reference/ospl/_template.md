# 
(since version 0.1.0)  



## Description

```c
int ospl_(char *library);
```


## Parameters

**`library`**: the path of an ospl library.  


## Return values

| `value`   | `signification`                                   |
| --------- | ------------------------------------------------- |
| `SUCCESS` |                                                   |
|           |                                                   |


## Example

```c
#include <ospl.h>

int main(void)
{
	int ret;
	char *library = "path/to/photo/library/";

	if ((ret = ospl_(library)) < 0)
	{
		printf("Failed to : %s", ospl_enum_error(ret));
		return 1;
	}
	else
		printf("");
	return 0;
}
```


## Behavior


## Changelog

| `version` | `description`              |
| ----------- | ------------------------ |
| `v0.1.0`  | the function is introduced |


## Enhancements


