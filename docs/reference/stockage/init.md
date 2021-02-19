# stockage_init
(since version 0.1.0)  
initiates a transaction


## Description

```c
int stockage_init(t_db *db);
```

This function initiates a database connection and start the transaction mode. The connection needs to be closed with **[`stockage_commit`](/{{ site.baseurl }}/reference/stockage/commit)** 


## Parameters

`db`: the database data structure  


## Return values

| `value` | `signification`                                   |
| ------- | ------------------------------------------------- |
| `0`     | no errors while executing query                   |
| `> 0`   | an error occured while initiating database        |


## Behavior

This function opens the database file using `sqlite3_open_v2` in `read/write` and `FULLMUTEX` mode, sets the `JOURNAL MODE` to `MEMORY`, disables `SYNCRONOUS` mode and finally begins the transaction mode using `sqlite3_exec`.


## Changelog

| `version` | `description`              |
| --------- | -------------------------- |
| `v0.1.0`  | the function is introduced |
