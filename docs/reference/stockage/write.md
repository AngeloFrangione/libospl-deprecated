# stockage_write
(since version 0.1.0)  
execute a write query on database


## Description

```c
int stockage_write(t_db *db, char *query);
```

This function is a higher level function that initializes the database connection, executes the query and commits to write the results to the database.


## Parameters

`db`: the database data structure  
`query`: the write query to execute


## Return values

| `value` | `signification`                                   |
| ------- | ------------------------------------------------- |
| `0`     | no errors while executing query                   |
| `-1`    | an error occured while executing query            |


## Behavior

This functions will execute respectively **[`stockage_init`](/{{ site.baseurl }}/reference/stockage/init)** **[`stockage_query_write`](/{{ site.baseurl }}/reference/stockage/query_write)** and **[`stockage_commit`](/{{ site.baseurl }}/reference/stockage/commit)**


## Changelog

| `version` | `description`              |
| --------- | -------------------------- |
| `v0.1.0`  | the function is introduced |


## Note

This function is not meant to be used for massive calling with a while loop. Prefer to use the lower level functions described in behavior, or concatenate the queries to use a single transaction and speed up the process.
