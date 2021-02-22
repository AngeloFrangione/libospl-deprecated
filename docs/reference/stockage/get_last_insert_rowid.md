# stockage_get_last_insert_rowid 
(since version 0.1.0)  
returns the last insert row id


## Description

```c
int stockage_get_last_insert_rowid(sqlite3 *sqlite);
```

This function returns the last inserted row id; Works with transaction mode.


## Parameters

`sqlite`: the sqlite3 database pointer


## Return values

Returns the last inserted row id.

## Behavior

This functions calls `sqlite3_last_insert_rowid()`

## Changelog

| `version` | `description`              |
| ----------- | ------------------------ |
| `v0.1.0`  | the function is introduced |

