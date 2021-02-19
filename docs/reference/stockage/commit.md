# stockage_commit
(since version 0.1.0)  
finalizes a transaction


## Description

```c
int stockage_commit(t_db *db);
```

This function ends the transaction mode and closes a database connection previously opened with **[`stockage_init`](/{{ site.baseurl }}/reference/stockage/init)**.


## Parameters

`db`: the database data structure  


## Return values

| `value` | `signification`                                   |
| ------- | ------------------------------------------------- |
| `0`     | no errors while executing query                   |
| `> 0`   | an error occured while closing the database       |


## Behavior

This function ends the transaction with `sqlite3_exec` and closes the database connection.
In a sqlite transaction, if the commit fails because of any reason (such as power loss, system crash) no previous query will be saved.


## Changelog

| `version` | `description`              |
| --------- | -------------------------- |
| `v0.1.0`  | the function is introduced |
