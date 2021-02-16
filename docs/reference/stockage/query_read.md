# stockage_query_read
(since version 0.1.0)  
executes any reading query


## Description

```c
int stockage_query_read(t_db *db, char *query, int callback(), void *data);
```

Executes any reading query and sends the rows to a callback function (select...)
Additionally this function takes a data parameter to store the result.
You need to call `stockage_init()` before calling this function to start the transaction. And you also need to call `stockage_commit()` to apply the changes from the transaction.


## Parameters

`db`: the database data structure  
`query`: the read query to execute  
`callback()`: callback function called by sqlite3  
`value`: the parameter given to the callback function  


## Return values

| `value` | `signification`                                   |
| ------- | ------------------------------------------------- |
| `0`     | no errors while executing query                   |
| `> 0`   | an sqlite error occured while executing query     |


## Behavior

This function executes sqlite3_exec and checks the return value. If an error occured, it is printed and returned. The printing is always on because if an error occurs, it means the query passed is wrong and debugging is needed.


## Changelog

| `version` | `description`              |
| --------- | -------------------------- |
| `v0.1.0`  | the function is introduced |
