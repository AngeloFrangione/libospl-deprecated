#include <thumbnailer.h>
#include "includes/ospl.h"
#include <string.h>
#include <stdlib.h>
#include <errno.h>

void show_usage()
{
	printf("OSPL - Open source picture library v%d.%d\n", VERSION_MAJOR, VERSION_MINOR);
	printf("Utility to manage an OSPL\n");
	printf("=========================================================================\n");
	printf("Usage :  ospl <verb> <librarypath> <options>, where <verb> is as follows:\n");
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
	printf("Usage :  ospl create [options] <librarypath>\n");
	printf("Options that are not mandatory (only one of these):\n");
	printf("-v verbose printing\n");
}

void usage_import()
{
	printf("Import specified pictures into <librarypath>\n");
	printf("-------------------------------------------------------------------------\n");
	printf("Usage:  ospl import <librarypath> <options>\n");
	printf("OPTIONS:\n");
	printf("At least one of the following :\n");
	printf("    -f <path> : specifies a file to import\n");
	printf("    -F <path> : specifies a folder to import\n");
	printf("Options that are not mandatory :\n");
	printf("    -v : human readable maximum verbosity\n");
	printf("//  -a <album_id> : import into album_id album (not implemented yet)\n");
}

/**
  * \brief Checks if libarary exists
  *
  * \param path location to test
  * \return 1 if the library exists
  * \return 0 if the library does not exists
  */
static int library_exists()
{
	if (folder_exists(g_library_path) && file_exists(g_database_path))
		return 1;
	else
		return 0;
}

/**
  * \brief Returns the index of given arg in available arguments
  *
  * \param arg Argument to get index of
  * \return The index of arg in available arguments
  */
static int indexof_arg(const char *arg)
{
	for (int i = 0; i < ARGS_COUNT; i++)
		if (!strcmp(ARGS[i], arg))
			return (i + 1);
	return 0;
}


/**
  * \brief Initiate the library global variables
  *
  * \param av library path
  * \return 0 with success and 1 when an error occurs
  */
static int initiate_path(const char *path)
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

void usage_export(char *arg)
{

}

void usage_album(char *arg)
{

}

void usage_folder(char *arg)
{

}

void usage_unrecognized(char *arg)
{
	printf("ospl: did not recognize verb '%s' type \"ospl\" for a list\n", arg);
}


char *ARGS[ARGS_COUNT] = {"create", "import", "export", "album", "folder"};
char *g_library_path = NULL;
char *g_database_path = NULL;
int print_mode = 0; // 0 = normal printing, 1 = verbose printing, 2 = json printing


static int return_1()
{
	return 1;
}

static int import(const char **av)
{
	printf("c/ 1: %s 2: %s\n", av[0], av[1]);
	return 0;
}

static int export(const char **av)
{
	printf("e/ 1: %s 2: %s\n", av[0], av[1]);
	return 0;
}

static int create(const char **av)
{
	int ret;
	initiate_path(av[0]);
	if (av[1] && !strcmp(av[1], "-v"))
	{
		printf("g_library_path: {%s}\ng_database_path: {%s}\n",
				g_library_path, g_database_path);
	}
	if (ospl_create_library(g_library_path))
	{
		perror(NULL);
	}
	return 0;
}

int main(int ac, char const *av[])
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
		if (function_launcher[indexof_arg(av[1])](&av[2]) == 1)
			usage_launcher[indexof_arg(av[1])](av[2]);
	}
	free(g_library_path);
	free(g_database_path);
}