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

#include "includes/ospl.h"
#include "includes/ospl_cli.h"
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>

char *ARGS[ARGS_COUNT] = {"create", "import", "export", "album", "folder"};
char *g_library_path = NULL;
char *g_database_path = NULL;
int print_mode = 0; // 0 = normal printing, 1 = verbose printing, 2 = json printing

void show_usage()
{
	printf("OSPL - Open source picture library v%d.%d\n", VERSION_MAJOR, VERSION_MINOR);
	printf("Utility to manage an OSPL\n");
	printf("=========================================================================\n");
	printf("Usage: ospl <verb> <librarypath> <options>, where <verb> is as follows:\n");
	printf("-------------------------------------------------------------------------\n");
	printf("ospl  create         creating library\n");
	printf("ospl  import         importing pictures\n");
	printf("ospl  export         exporting pictures\n");
	printf("ospl  album          managing albums\n");
	printf("ospl  folder         managing folders\n");
	printf("-------------------------------------------------------------------------\n");
	printf("ospl <verb> with no options will provide help on that verb\n");
}

void usage_create()
{
	printf("Creates a shiny new ospl library at <librarypath>\n");
	printf("-------------------------------------------------------------------------\n");
	printf("Usage: ospl create <librarypath> [options]\n");
	printf("Options that are not mandatory (only one of these):\n");
	printf("-v verbose printing\n");
}

void usage_import()
{
	printf("Import specified pictures into <librarypath>\n");
	printf("-------------------------------------------------------------------------\n");
	printf("Usage: ospl import <librarypath> <options>\n");
	printf("OPTIONS:\n");
	printf("At least one of the following :\n");
	printf("    -f <path> : specifies a file to import\n");
	printf("    -F <path> : specifies a folder to import\n");
	printf("Options that are not mandatory :\n");
	printf("    -v : human readable maximum verbosity\n");
	printf("//  -a <album_id> : import into album_id album (not implemented yet)\n");
}

void usage_export(char *arg)
{

}

void usage_album(char *arg)
{

}

void usage_folder(char *arg)
{

}

/**
  * \brief Returns the index of given arg in available arguments
  *
  * \param arg Argument to get index of
  * \return The index of arg in available arguments
  */
static int indexof_arg(char *arg)
{
	for (int i = 0; i < ARGS_COUNT; i++)
		if (!strcmp(ARGS[i], arg))
			return (i + 1);
	return 0;
}

/**
  * \brief Initiate the cli global variables
  *
  * \param av library path
  * \return 0 with success and 1 when an error occurs
  */
static int initiate_path(char *path)
{
	int path_len = strlen(path);

	g_library_path = calloc(sizeof(char), (path_len + 2));
	if (!g_library_path)
		return 1;
	g_database_path = calloc(sizeof(char), (path_len + DATABASE_NAME_LEN + 1));
	if (!g_database_path)
		return 1;
	strcat(g_library_path, path);
	if (g_library_path[path_len - 1] != '/')
		strcat(g_library_path, "/");
	strcat(g_database_path, g_library_path);
	strcat(g_database_path, DATABASE_FILENAME);
	return 0;
}

void usage_unrecognized(char *arg)
{
	printf("ospl: did not recognize verb '%s' type \"ospl\" for a list\n", arg);
}

static int return_1()
{
	return 1;
}

static int import(int ac, char **av)
{
	printf("create/ (args: %d) 1: %s 2: %s\n", ac, av[0], av[1]);
	if (ac < 5)
	{
		usage_import();
		return 0;
	}
	if (!strcmp(av[1], "-f"))
	{
		initiate_path(av[0]);
		if (library_exists(av[0]))
			ospl_import_picture(av[0], av[2]);
		else
			printf("Library not found: %s\n", av[0]);
	}
	return 0;
}

static int export(int ac, char **av)
{
	printf("export/ (args: %d) 1: %s 2: %s\n", ac, av[0], av[1]);
	return 0;
}

static int create(int ac, char **av)
{
	initiate_path(av[0]);
	if (av[1] && !strcmp(av[1], "-v"))
	{
		printf("g_library_path: {%s}\ng_database_path: {%s}\n",
				g_library_path, g_database_path);
	}
	if (ospl_create_library(g_library_path))
		perror(NULL);
	printf("created library at path: %s\n", av[0]);
	return 0;
}

int main(int ac, char *av[])
{
if (ac == 1)
		show_usage();
	else if (ac == 2)
	{
		void (*usage_launcher[1 + ARGS_COUNT])() = {usage_unrecognized, usage_create, usage_import, usage_export, usage_album, usage_folder};
		usage_launcher[indexof_arg(av[1])](av[1]);
	}
	else
	{
		void (*usage_launcher[1 + ARGS_COUNT])() = {usage_unrecognized, usage_create, usage_import, usage_export};
		int (*function_launcher[1 + ARGS_COUNT])() = {return_1, create, import, export};
		if (function_launcher[indexof_arg(av[1])](ac, &av[2]) == 1)
			usage_launcher[indexof_arg(av[1])](av[2]);
	}
	free(g_library_path);
	free(g_database_path);
}