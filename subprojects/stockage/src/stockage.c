/*	libospl - Open Source Photo Library
	an opensource and multiplateform photo library management that can be used
	to store and sort all your pictures.
	Copyright (C) 2019-2020 Angelo Frangione

	This program is free software; you can redistribute it and/or modify
	it under the terms of the GNU General Public License as published by
	the Free Software Foundation; either version 2 of the License, or
	(at your option) any later version.

	This program is distributed in the hope that it will be useful,
	but WITHOUT ANY WARRANTY; without even the implied warranty of
	MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
	GNU General Public License for more details.

	You should have received a copy of the GNU General Public License along
	with this program; if not, write to the Free Software Foundation, Inc.,
	51 Franklin Street, Fifth Floor, Boston, MA 02110-1301 USA.
*/

/**
 * \file sqlitewrapper.c
 * \brief This file contains the sqlite3 wrapper
 * \author Angelo Frangione
 *
 * the sqlite3 wrapper for ospl contains all functions needed
 * for communicating with the sqlit3 database
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <strings.h>
#include <sqlite3.h>
#include "stockage.h"

int get_last_insert_rowid(sqlite3 *sqlite)
{
	return sqlite3_last_insert_rowid(sqlite);
}

/**
 * \brief Checks sqlite return
 *
 * Checks whether db or query execution is OK or not. 
 * If not,prints the error message to stderr and returns error code 1
 * \param rc return code to check
 * \param db database data structur
 * \return 0 if success, or the sqlite error code if failed
 */
int check_sqlite_return(int rc, t_db *db, char *query)
{
	if (rc != SQLITE_OK && rc != SQLITE_ROW && rc != SQLITE_DONE)
	{
		fprintf(stderr, "Error %d: %s | query: {%s}\n", rc, sqlite3_errmsg(db->db),
				query);
		sqlite3_close(db->db);
		return rc;
	}
	return 0;
}

/**
 * \brief Create connection to the database in read write / transaction mode
 *
 * Create connection to the database in read and write mode.
 * This start a sql transaction, need to be closed with stockage_commit()
 * \param db database data structur
 * \return the sqlite return code;
 */
int stockage_init(t_db *db)
{
	int rc;

	rc = sqlite3_open_v2(db->path, &db->db, SQLITE_OPEN_READWRITE | 
							SQLITE_OPEN_FULLMUTEX, NULL);
	check_sqlite_return(rc, db, "empty");
	rc = sqlite3_exec(db->db, JOURNAL_MODE_MEMORY, 0, 0, NULL);
	check_sqlite_return(rc, db, "empty");
	rc = sqlite3_exec(db->db, SYNCRONOUS_OFF, 0, 0, NULL);
	check_sqlite_return(rc, db, "empty");
	rc = sqlite3_exec(db->db, "BEGIN TRANSACTION", NULL, NULL, NULL);
	return check_sqlite_return(rc, db, "BEGIN TRANSACTION");
}

/**
 * \brief Create an empty ospl databse
 *
 * Creates the whole tables needed for ospl into the databases.
 * Creates the database file if it doesn't exists
 * \param path path to the db file
 * \return the sqlite return code;
 */
int create_database(char *path)
{
	sqlite3 		*db;
	int				rc;
	char			*vacuum = "PRAGMA auto_vacuum = FULL;";

	rc = sqlite3_open_v2(path, &db, SQLITE_OPEN_READWRITE | 
							SQLITE_OPEN_FULLMUTEX | SQLITE_OPEN_CREATE, NULL);
	rc = sqlite3_exec(db, vacuum, 0, 0, NULL);
	rc = sqlite3_exec(db, TABLE, 0, 0, NULL);
	rc = sqlite3_close(db);
	return rc;
}

/**
 * \brief executes any writing query
 *
 * executes any query that writes into an initiated database
 * insert, delete, update...
 *
 * \param query pointer to the SQL query
 * \param db database data structure
 * \return the sqlite return code;
 */
int stockage_query_write(char *query, t_db *db)
{
	int rc;

	rc = sqlite3_exec(db->db, query, 0, 0, NULL);
	return check_sqlite_return(rc, db, query);
}

/**
 * \brief executes any reading query
 *
 * executes any reading query and sends the rows to a callback function
 * Additionally this function takes a data parameter for storing the result
 * (select...)
 *
 * \param query pointer to the SQL query
 * \param db database data structure
 * \param callback callback function should be prototyped with these arguments:
 * callback(void *data, int argc, char **argv, char **column_name)
 * \param data data that will be passed to the callback function
 * \return the sqlite return code;
 */
int stockage_query_read(char *query, t_db *db, int callback(), void *data)
{
	int rc;

	rc = sqlite3_exec(db->db, query, callback, data, NULL);
	return check_sqlite_return(rc, db, query);
}

/**
 * \brief finalizes a transaction connection and writes data to the disk
 *
 * this function should be called after every use of stockage_init();
 * and of course after you read and wrote all necessary data.
 * In a sqlite transaction, if the commit fails because of any reason (such as
 * power loss, system crash) no previous query will be saved.
 *
 * \param db database data structure
 * \return the sqlite return code;
 */
int stockage_commit(t_db *db)
{
	int rc;

	rc = sqlite3_exec(db->db, "END TRANSACTION", NULL, NULL, NULL);
	check_sqlite_return(rc, db, "END TRANSACTION");
	rc = sqlite3_close_v2(db->db);
	return check_sqlite_return(rc, db, "empty");
}

/**
 * \brief high level interface for reading data from db
 *
 * this function is a wrapper of the wrapper, by default it will commit every
 * query. if you don't want this behavior you need to set the transaction 
 * variable into the t_db structure to 1; it will be set to two after first 
 * transaction sucessfully sent. to commit you will need to set the commit 
 * variable to 1 in the t_db parameter.
 * 
 * \param db database data structure
 * \param query read query (select...)
 * \param callback callback function should be prototyped with these arguments:
 * callback(void *data, int argc, char **argv, char **column_name)
 * \param value the data argument passed to the callback function
 */
int stockage_read(t_db *db, char *query, int callback(), void *value)
{
	int rc;

	if (db->transaction > 1 && !db->commit)
	{
		rc = stockage_query_read(query, db, callback, value);
	}
	else if (!db->transaction && !db->commit)
	{
		rc = stockage_init(db);
		rc = stockage_query_read(query, db, callback, value);
		rc = stockage_commit(db);
	}
	else if (db->transaction == 1 && !db->commit)
	{
		rc = stockage_init(db);
		rc = stockage_query_read(query, db, callback, value);
		rc = db->transaction++;
	}
	else if (db->commit && db->transaction)
	{
		rc = stockage_query_read(query, db, callback, value);
		rc = stockage_commit(db);
		rc = db->transaction = 0;
	}
	return check_sqlite_return(rc, db, query);
}

/**
 * \brief high level interface for writing data in db
 *
 * this function is a wrapper of the wrapper, by default it will commit every
 * query. if you don't want this behavior you need to set the transaction 
 * variable into the t_db structure to 1; it will be set to two after first 
 * transaction sucessfully sent. to commit you will need to set the commit 
 * variable to 1 in the t_db parameter.
 * 
 * \param db database data structure
 * \param query read query (insert, update, delete...)
 */
int stockage_write(t_db *db, char *query)
{
	int rc;

	if (db->transaction > 1 && !db->commit)
	{
		rc = stockage_query_write(query, db);
	}
	else if (!db->transaction && !db->commit)
	{
		rc = stockage_init(db);
		rc = stockage_query_write(query, db);
		rc = stockage_commit(db);
	}
	else if (db->transaction == 1 && !db->commit)
	{
		rc = stockage_init(db);
		rc = stockage_query_write(query, db);
		rc = db->transaction++;
	}
	else if (db->commit && db->transaction)
	{
		rc = stockage_query_write(query, db);
		rc = stockage_commit(db);
		rc = db->transaction = 0;
	}
	return check_sqlite_return(rc, db, query);
}
