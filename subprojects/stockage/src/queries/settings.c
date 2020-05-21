#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "include/stockage.h"

static int callback(t_db *param, int argc, char **argv, char **column)
{
	param->param = strdup(argv[1]);
	return 0;
}

int insert_setting(char *dbpath, char *name, char *value)
{
	t_db	db;
	char	query[BUFFER_SIZE] = "insert into settings (name, value) ";
	sprintf(query + 35, "values (\"%s\", \"%s\");", name, value);

	init_connection(&db);
	init_db_transaction_rw(&db, dbpath);
	insert_transaction(query, &db);
	finalize_transaction(&db);
	return 0;
}

int update_setting(char *dbpath, char *name, char *value)
{
	t_db	db;
	char	query[BUFFER_SIZE] = "update settings set value=";

	sprintf(query + 26, "\"%s\" where name=\"%s\";", value, name);
	init_connection(&db);
	init_db_transaction_rw(&db, dbpath);
	insert_transaction(query, &db);
	finalize_transaction(&db);
	return 0;
}

int select_setting(char *dbpath, char *name, char *value)
{
	t_db	db;
	char	query[BUFFER_SIZE] = "select * from settings ";
	
	sprintf(query + 23, "where name = \"%s\"", name);
	init_connection(&db);
	init_db_transaction_rw(&db, dbpath);	
	select_transaction_data(query, &db, callback, &db);
	strcpy(value, db.param);
	free(db.param);
	finalize_transaction(&db);
	return 0;
}

int delete_setting(char *dbpath, char *name)
{
	t_db	db;
	char	query[BUFFER_SIZE] = "delete from settings where name=";
	
	sprintf(query + 32, "%s;", name);
	init_connection(&db);
	init_db_transaction_rw(&db, dbpath);
	insert_transaction(query, &db);
	finalize_transaction(&db);
	return 0;
}
