# stockage_read
(since version 0.1.0)  
execute a read query on database


## Description

```c
int stockage_read(t_db *db, char *query, int callback(), void *value);
```

This function is a higher level function that initializes the database connection, executes the query and commits to get the results from the databae.


## Parameters

`db`: the database data structure  
`query`: the read query to execute  
`callback()`: callback function called by sqlite3  
`value`: the parameter given to the callback function  


## Return values

| `value` | `signification`                                   |
| ------- | ------------------------------------------------- |
| `0`     | no errors while executing query                   |
| `-1`    | an error occured while executing query            |


## Behavior

This functions will execute respectively  `stockage_init()` `stockage_query_read()` and `stockage_commit()`


## Changelog

| `version` | `description`              |
| --------- | -------------------------- |
| `v0.1.0`  | the function is introduced |


## Note

This function is not meant to be used for massive calling with a while loop. Prefer to use the lower level functions described in behavior, or concatenate the queries to use a single transaction and speed up the process.
