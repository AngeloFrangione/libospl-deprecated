# ospl_import_photo_t
(since version 0.1.0)  
import a photo into library



## Description

```c
int ospl_import_photo_t(char *library, char *path, t_db *transaction_db);
```
This functions imports a folder located at `path` in an ospl library located at  `library` into album with id `album`


## Parameters

**`library`**: the path of an ospl library.  
**`path`**: the path of a photo.  
**`transaction_db`**: the db structure used for transactions.  

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
#include <stockage.h>

int main(void)
{
	int ret;
	char *library = "path/to/photo/library/";
	char *path = "path/to/picture.jpg"
	char *path2 = "path/to/picture_2.jpg"
	t_db transaction_db;

	fill_tdb(&transaction_db, library);
	stockage_init(&transaction_db);
	if ((ret = ospl_import_photo_t(library, path)) < 0)
	{
		printf("Failed to import photo: %s", ospl_enum_error(ret));
		return 1;
	}
	if ((ret = ospl_import_photo_t(library, path2)) < 0)
	{
		printf("Failed to import photo: %s", ospl_enum_error(ret));
		return 1;
	}
	stockage_commit(&transaction_db);
	else
		printf("Photo imported successfully");
	return 0;
}
```


## Behavior

This function will extract information about a photo, such as the name and an `md5` hash. It will copy the current time. And insert the photo into the database, if it succeeds, it will copy the photo into the `library/photos/import/` folder with a new name composed of its original name, the import date and time. If this succeeds, it will create a thumbnail into the `library/thumbnails/` folder. And if finally this succeeds, the `id` of the just inserted photo is returned.

If `transaction` is not `NULL`, transaction mode is enabled and you will need to call **[`stockage_init`](/{{ site.baseurl }}/reference/stockage/init)** before and **[`stockage_commit`](/{{ site.baseurl }}/reference/stockage/commit)** after.
If `transaction_db`is `NULL`, the transaction is initiated and closed automatically.


## Changelog

| `version` | `description`                           |
| --------- | --------------------------------------- |
| `v0.2.0`  | the function is introduced              |
