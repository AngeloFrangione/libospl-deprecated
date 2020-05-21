#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "include/stockage.h"

static int callback(t_db *param, int argc, char **argv, char **column)
{
	param->param = strdup(argv[1]);
	return 0;
}

int insert_setting(char *name, int value)
{
	t_db	db;
	char	query[BUFFER_SIZE] = "insert into settings (name, value) ";

	init_connection(&db);
	init_db_transaction_rw(&db, "test.db");
	sprintf(query + 35, "values (\"%s\", %d);", name, value);
	insert_transaction(query, &db);
	finalize_transaction(&db);
	return 0;
}

int select_setting(char *name, int *value)
{
	t_db	db;
	char	query[BUFFER_SIZE] = "select * from settings ";

	init_connection(&db);
	init_db_transaction_rw(&db, "test.db");
	sprintf(query + 23, "where name = \"%s\"", name);
	select_transaction_data(query, &db, callback, &db);
	*value = atoi((char*)db.param);
	free(db.param);
	finalize_transaction(&db);
	return 0;
}
