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
#include "subprojects/stockage/include/stockage.h"
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <ctype.h>

char *ARGS[ARGS_COUNT] = {"create", "import", "picture", "export", "album", "folder"};
char *ALBUM_ARGS[ALB_ARG_CNT] = {"list", "create", "rename", "delete", "picadd", "picdel", "piclist", "picmove"};
char *PICTURE_ARGS[PIC_ARG_CNT] = {"list", "info", "delete"};
char *g_library_path = NULL;
char *g_database_path = NULL;
int print_mode = 0; // 0 = normal printing, 1 = verbose printing, 2 = json printing

int isnumeric(char *s)
{
	while (*s)
	{
		if (!isdigit(*s))
			return 0;
		++s;
	}
	return 1;
}

void show_usage()
{
	printf("\nOSPL - Open source picture library v%s.%s.%s\n", VERSION_MAJOR, VERSION_MINOR, VERSION_REVISION);
	printf("Utility to manage an OSPL\n");
	printf("================================================================================\n");
	printf("Usage: ospl <verb> <librarypath> <options>, where <verb> is as follows:\n");
	printf("--------------------------------------------------------------------------------\n");
	printf("ospl create         creating library\n");
	printf("ospl import         importing pictures\n");
	printf("ospl picture        managing pictures\n");
	printf("ospl export         exporting pictures\n");
	printf("ospl album          managing albums\n");
	printf("ospl folder         managing folders\n");
	printf("--------------------------------------------------------------------------------\n");
	printf("ospl <verb> with no options will provide help on that verb\n");
}

void usage_create()
{
	printf("\nCreates a shiny new ospl library at <librarypath>\n");
	printf("--------------------------------------------------------------------------------\n");
	printf("Usage: ospl create <librarypath> [options]\n");
	printf("Options that are not mandatory (only one of these):\n");
	printf("-v verbose printing\n");
}

void usage_import()
{
	printf("\nImport specified pictures into <librarypath>\n");
	printf("--------------------------------------------------------------------------------\n");
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
	printf("\nManages albums at <librarypath>\n");
	printf("--------------------------------------------------------------------------------\n");
	printf("Usage: ospl album <verb> <librarypath> <options>, where <verb> is as follows:\n");
	printf("--------------------------------------------------------------------------------\n");
	printf("ospl album list    <librarypath>                   list albums\n");
	printf("ospl album create  <librarypath> <name>            creating albums\n");
	printf("ospl album rename  <librarypath> <album> <name>    renaming albums\n");
	printf("ospl album delete  <librarypath> <album>           deleting albums\n");
	printf("ospl album picadd  <librarypath> <album> <pic>     add a picture into album\n");
	printf("ospl album picdel  <librarypath> <album> <pic>     delete a picture from album\n");
	printf("ospl album piclist <librarypath> <album>           list pictures inside an album\n");
	printf("ospl album picmove <librarypath> <pic> <old> <new> move picture to another album\n");
	printf("--------------------------------------------------------------------------------\n");
}

void usage_folder(char *arg)
{

}

void usage_picture(char **arg)
{
	printf("\nManages pictures at <librarypath>\n");
	printf("--------------------------------------------------------------------------------\n");
	printf("Usage: ospl picture <verb> <librarypath> <options>, where <verb> is as follows:\n");
	printf("--------------------------------------------------------------------------------\n");
	printf("ospl picture list   <librarypath>             list every picture\n");
	printf("ospl picture info   <librarypath> <id>        show more info about a picture\n");
	printf("ospl picture delete <librarypath> <id>        remove picture from library\n");
	printf("--------------------------------------------------------------------------------\n");

}
/**
  * \brief Returns the index of given arg in available arguments
  *
  * \param arg Argument to get index of
  * \return The index of arg in available arguments
  */
static int indexof_arg(char *arg, char **args, int count)
{
	for (int i = 0; i < count; i++)
		if (!strcmp(args[i], arg))
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
	printf("create/ (args: %d) 1: %s 2: %s 3: %s\n", ac, av[0], av[1], av[2]);
	if (ac < 5)
	{
		usage_import();
		return 0;
	}
	else if (!strcmp(av[1], "-f"))
	{
		initiate_path(av[0]);
		if (library_exists(av[0]))
			ospl_import_picture(av[0], av[2]);
		else
			printf("Library not found: %s\n", av[0]);
	}
	else if (!strcmp(av[1], "-F"))
	{
		initiate_path(av[0]);
		if (library_exists(av[0]))
			ospl_import_folder(av[0], av[2]);
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

static int album (int ac, char **av)
{
	int r;
	printf("album/ (args: %d) 0: %s 1: %s\n", ac, av[0], av[1]);
	if (ac < 4)
	{
		usage_album(NULL);
		return 0;
	}
	else if ((r = indexof_arg(av[0], ALBUM_ARGS, ALB_ARG_CNT)))
	{
		if(!library_exists(av[1]))
		{
			printf("Library not found: %s\n", av[1]);
			return 0;
		}
		switch(r)
		{
			case 1 :
				printf("Album list:\n=================\n");
				printf("%3s | %10s\n", "id", "name");
				printf("----------------\n");
				t_album alb_list[ALB_LIMITS] = { 0 };
				ospl_list_albums(av[1], alb_list);
				for(int i = 0; alb_list[i].id; i++)
					printf("%3d | %10s\n", alb_list[i].id, alb_list[i].name);
				break;
			case 2 :
				if (ac < 5)
				{
					usage_album(NULL);
					return 0;
				}
				ospl_create_album(av[1], av[2]);
				printf("album %s created\n", av[2]);
				break;
			case 3 :
				if (ac < 6 || !isnumeric(av[2]))
				{
					usage_album(NULL);
					return 0;
				}
				ospl_rename_album(av[1], atoi(av[2]), av[3]);
				printf("album %d renamed to %s\n", atoi(av[2]), av[3]);
				break;
			case 4 :
				if (ac < 5 || !isnumeric(av[2]))
				{
					usage_album(NULL);
					return 0;
				}
				ospl_delete_album(av[1], atoi(av[2]));
				printf("deleted album %s\n", av[2]);
				break;
			case 5 :
				if (ac < 6 || !isnumeric(av[2]) || !isnumeric(av[3]))
				{
					usage_album(NULL);
					return 0;
				}
				ospl_album_addpic(av[1], atoi(av[2]), atoi(av[3]));
				printf("picture %d added to album %d\n", atoi(av[2]), atoi(av[3]));
				break;
			case 6 :
				if (ac < 6 || !isnumeric(av[2]) || !isnumeric(av[3]))
				{
					usage_album(NULL);
					return 0;
				}
				ospl_album_delpic(av[1], atoi(av[2]), atoi(av[3]));
				printf("picutre %d deleted from album %d\n", atoi(av[2]), atoi(av[3]));
				break;
			case 7 :
				if (ac < 5 || !isnumeric(av[2]))
				{
					usage_album(NULL);
					return 0;
				}
				uint32_t pic_list[6500];
				memset(pic_list, 0, sizeof(uint32_t) * 6500);
				ospl_album_listpic(av[1], atoi(av[2]), pic_list);
				
				printf("Picture inside album %d:\n", atoi(av[2]));
				printf("----------------------\n");
				// printf("%d\n", pic_list[0]);
				int i = 0;
				while(pic_list[i])
				{
					printf("%d\n", pic_list[i]);
					++i;
				}
				break;
			case 8 :
				if (ac < 7 || !isnumeric(av[2]) || !isnumeric(av[3]) || !isnumeric(av[4]))
				{
					usage_album(NULL);
					return 0;
				}
				ospl_album_movepic(av[1], atoi(av[2]), atoi(av[3]), atoi(av[4]));
				printf("picture %d moved from album %d to album %d\n", atoi(av[2]), atoi(av[3]), atoi(av[4]));
				break;
		}
	}
	else
		usage_album(NULL);
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

static int picture(int ac, char **av)
{
	int r;
	
	printf("picture/ (args: %d) 1: %s 2: %s\n", ac, av[1], av[2]);
	if (ac < 4)
	{
		usage_picture(NULL);
		return 0;
	}
	else if ((r = indexof_arg(av[0], PICTURE_ARGS, PIC_ARG_CNT)))
	{
		if(!library_exists(av[1]))
		{
			printf("Library not found: %s\n", av[1]);
			return 0;
		}
		switch(r)
		{
			case 1 :
				printf("list\n");
				t_photos pic_list[6500] = { 0 };
				ospl_picture_list(av[1], pic_list);
				printf("%5s|%32s|%52s|%24s|%11s|%10s\n",
					"id", "hash", "original_name", "import_datetime",
					"exif_height", "exif_width");
				for(int i = 0; pic_list[i].import_year; i++)
					printf("%5d|%32s|%52s|%24s|%11d|%10d\n",
						pic_list[i].id, pic_list[i].hash,
						pic_list[i].original_name, pic_list[i].import_datetime,
						pic_list[i].exif_height, pic_list[i].exif_width);
				break;
				break;
			case 2:
				printf("info\n");
				if (ac < 5 || !isnumeric(av[2]))
				{
					usage_picture(NULL);
					return 0;
				}
				t_photos pic = { 0 };
				ospl_picture_get(av[1], atoi(av[2]), &pic);
				printf("%5s|%32s|%52s|%24s|%11s|%10s\n",
					"id", "hash", "original_name", "import_datetime",
					"exif_height", "exif_width");
				printf("%5d|%32s|%52s|%24s|%11d|%10d\n",
					pic.id, pic.hash, pic.original_name, pic.import_datetime,
					pic.exif_height, pic.exif_width);
				break;
			case 3:
				if (ac < 5 || !isnumeric(av[2]))
				{
					usage_picture(NULL);
					return 0;
				}
				ospl_picture_delete(av[1], atoi(av[2]));
				printf("deleted picture %s from library\n", av[2]);
				break;
		}
	}
	else
		usage_picture(NULL);
	return 0;
}
int main(int ac, char *av[])
{
if (ac == 1)
		show_usage();
	else if (ac == 2)
	{
		printf("index of %s: %d\n", av[1], indexof_arg(av[1], ARGS, ARGS_COUNT));
		void (*usage_launcher[1 + ARGS_COUNT])() = {usage_unrecognized, usage_create, usage_import, usage_picture, usage_export, usage_album, usage_folder};
		usage_launcher[indexof_arg(av[1], ARGS, ARGS_COUNT)](av[1]);
	}
	else
	{
		printf("index of %s: %d\n", av[1], indexof_arg(av[1], ARGS, ARGS_COUNT));
		void (*usage_launcher[1 + ARGS_COUNT])() = {usage_unrecognized, usage_create, usage_import, usage_picture, usage_export, usage_album};
		int (*function_launcher[1 + ARGS_COUNT])() = {return_1, create, import, picture, export, album};
		if (function_launcher[indexof_arg(av[1], ARGS, ARGS_COUNT)](ac, &av[2]) == 1)
			usage_launcher[indexof_arg(av[1], ARGS, ARGS_COUNT)](av[2]);
	}
	free(g_library_path);
	free(g_database_path);
}