# stockage_create_db
(since version 0.1.0)  
creates an empty ospl database file


## Description

```c
int stockage_create_db(char *path);
```

This function will create the ospl database file and create the whole tables needed for ospl.

## Parameters

`path`: the path where the database file will be created  


## Return values

| `value`   | `signification`                                 |
| --------- | ----------------------------------------------- |
| `0`     | no errors while executing query                   |
| `-1`    | an error occured while executing query            |


## Behavior

This function opens the database using `sqlite3_open_v2` at `path` using `SQLITE_OPEN_CREATE` to create the file. Then it sets the `auto_vacuum` to `FULL`, and finally adds the tables to the database.

## Changelog

| `version` | `description`              |
| ----------- | ------------------------ |
| `v0.1.0`  | the function is introduced |

