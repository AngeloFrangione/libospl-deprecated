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

/**
 * \brief Checks sqlite return
 *
 * Checks whether db or query execution is OK or not. If not, prints the error message to stderr and returns error code 1
 * \param rc Return code
 * \param db database data structur
 */

int check_sqlite_return(int rc, t_db *db)
{
	if (rc != SQLITE_OK)
	{
		fprintf(stderr, "Error: %s\n", sqlite3_errmsg(db->db));
		sqlite3_close(db->db);
		return 1;
	}
	return 0;
}

/**
 * \brief Create connection to the database in read write mode
 *
 * This function is not used.
 * Create connection to the database in read and write mode.
 * Creates the database file if it doesn't exists
 * \param path path to the db file
 * \param db database data structur
 */

int init_db_rw(t_db *db, char *path)
{
	int rc;

	rc = sqlite3_open_v2(path, &db->db, SQLITE_OPEN_READWRITE | SQLITE_OPEN_FULLMUTEX | SQLITE_OPEN_CREATE, NULL);
	return check_sqlite_return(rc, db);
}

/**
 * \brief Create connection to the database in read write mode and start a transaction
 *
 * Create connection to the database in read and write mode.
 * Creates the database file if it doesn't exists
 * This start a sql transaction, need to be closed with finalize_transaction()
 * Use this if there is multiples queries (speed's up the process)
 * \param path path to the db file
 * \param db database data structur
 */

int init_db_transaction_rw(t_db *db, char *path)
{
	int rc;

	db->transaction = 1;
	rc = sqlite3_open_v2(path, &db->db, SQLITE_OPEN_READWRITE | SQLITE_OPEN_FULLMUTEX | SQLITE_OPEN_CREATE, NULL);
	check_sqlite_return(rc, db);
	rc = sqlite3_exec(db->db, JOURNAL_MODE_MEMORY, 0, 0, NULL);
	check_sqlite_return(rc, db);
	rc = sqlite3_exec(db->db, SYNCRONOUS_OFF, 0, 0, NULL);
	check_sqlite_return(rc, db);
	rc = sqlite3_exec(db->db, "BEGIN TRANSACTION", NULL, NULL, NULL);
	check_sqlite_return(rc, db);
	return check_sqlite_return(rc, db);
}

/**
 * \brief Create an empty ospl databse
 *
 * Creates the whole tables needed for ospl into the databases.
 * Creates the database file if it doesn't exists
 * \param path path to the db file
 */

int create_database(char *path)
{
	t_db	db;
	int				rc;
	char			*vacuum = "PRAGMA auto_vacuum = FULL;";

	init_connection(&db);
	init_db_rw(&db, path);
	rc = sqlite3_exec(db.db, vacuum, 0, 0, NULL);
	check_sqlite_return(rc, &db);
	rc = sqlite3_exec(db.db, TABLE, 0, 0, NULL);
	check_sqlite_return(rc, &db);
	rc = sqlite3_close(db.db);
	return check_sqlite_return(rc, &db);
}

/**
 * \brief Executes the INSERT query
 * This function executes the INSERT query into the initiated database
 *
 *
 * \param query the SQL query (ex: "INSERT INTO library (hash) VALUES ('hash');")
 * \param db database data structure
 */

int insert_transaction(char *query, t_db *db)
{
	int rc;

	if (!db->transaction)
	{
		printf("Using insert_transaction without an transaction initiated db\n");
		exit(0);
	}
	rc = sqlite3_exec(db->db, query, 0, 0, NULL);
	check_sqlite_return(rc, db);
	return check_sqlite_return(rc, db);
}

/**
 * \brief Executes the SELECT query
 * This function executes the SELECT query and sends the rows to a callback function
 *
 * \param query the SQL query (ex: "INSERT INTO library (hash) VALUES ('hash');")
 * \param db database data structure
 * \param callback callback function should be prototyped with these arguments callback(void *unused, int argc, char **argv, char **column_name)
 */

int select_transaction(char *query, t_db *db, int callback())
{
	int rc;

	if (!db->transaction)
	{
		printf("Using select_transaction without an transaction initiated db\n");
		exit(0);
	}
	rc = sqlite3_exec(db->db, query, callback, 0, NULL);
	check_sqlite_return(rc, db);
	return check_sqlite_return(rc, db);
}

/**
 * \brief Executes the SELECT query
 * This function executes the SELECT query and sends the rows to a callback function
 * Additionally this function takes a data parameter for storing the result
 *
 * \param query the SQL query (ex: "INSERT INTO library (hash) VALUES ('hash');")
 * \param db database data structure
 * \param callback callback function should be prototyped with these arguments callback(void *data, int argc, char **argv, char **column_name)
 * \param data data that will be passed to the callback function
 */

int select_transaction_data(char *query, t_db *db, int callback(), void *data)
{
	int rc;

	if (!db->transaction)
	{
		printf("Using select_transaction_data without an transaction initiated db\n");
		exit(0);
	}
	rc = sqlite3_exec(db->db, query, callback, data, NULL);
	check_sqlite_return(rc, db);
	return check_sqlite_return(rc, db);
}

/**
 * \brief finalizes a transaction connection
 * This function should be called after every use of init_db_transaction_rw();
 *
 * \param db database data structure
 */

int finalize_transaction(t_db *db)
{
	int rc;

	rc = sqlite3_exec(db->db, "END TRANSACTION", NULL, NULL, NULL);
	check_sqlite_return(rc, db);
	sqlite3_close(db->db);
	return check_sqlite_return(rc, db);
}

/**
 * \brief initiate the db data structure
 * This function should be called before the use of init_db_transaction_rw();
 *
 * \param db database data structure
 */

int init_connection(t_db *db)
{
	memset(db, 0, sizeof(t_db));
	return 0;
}
