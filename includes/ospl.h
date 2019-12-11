#ifndef OSPL_H
#define OSPL_H

# define ARGS_COUNT 5
# define DATABASE_FILENAME "database.db"
# define DATABASE_NAME_LEN 12
# define LIBRARY_EXTENTION_LEN 5
# define LIBRARY_EXTENTION ".ospl"
# define VERSION_MAJOR 0
# define VERSION_MINOR 1
# define CREATE_OPTS "v"
# define IMPORT_OPTS "vfF"

/*
 * 
 * Library related functions
 * 
 */
int ospl_create_library(char *library);

int ospl_import_picture(char *library, char *path);
int ospl_import_folder(char *library, char *path);

int ospl_export_picture(char *library);
int ospl_export_album(char *library);

int ospl_album_create(char *library, int id);
int ospl_album_rename(char *library, int id, char *name);
int ospl_album_remove(char *library, int id);
char *ospl_album_getname(char *library, int id);

/*
 * 
 * Common usage functions
 * 
 */
int create_directory(char *path);
int file_exists(char *path);
int folder_exists(char *path);
int indexof(char *s, char c);

#endif