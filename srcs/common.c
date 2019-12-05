#include <sys/stat.h>
#include <dirent.h>
#include "ospl.h"

/**
  * \brief Creates a directory for windows and UNIX
  *
  * \param path the path were to create new folder
  * \return the return of the system mkdir function
  */
int create_directory(char *path)
{
	#if defined(_WIN32)
	return mkdir(path);
	#else
	return mkdir(path, 0777);
	#endif
}

/**
  * \brief Checks if file given in parameter exists
  *
  * \param path location to test
  * \return 1 if the file exists
  * \return 0 if the file does not exists
  */
int file_exists(char *path)
{
	struct stat buffer;
	int exist = stat(path, &buffer);

	if(exist == 0)
		return 1;
	else
		return 0;
}

/**
  * \brief Checks if folder exists
  *
  * \param path location to check
  * \return 1 if the folder exists 
  * \return 0 if the folder does not exists
  */
int folder_exists(char *path)
{
	DIR* dir = opendir(path);
	if (dir)
	{
		closedir(dir);
		return 1;
	}
	else
		return 0;
}

/**
  * \brief Get the index of a character in a string
  *
  * \param s string to search in
  * \param c character to search with
  * \return the index from c in s
  * \return if c was not found in s returns -1
  */
int indexof(char *s, char c)
{
	int i;

	i = 0;
	if (!s)
		return (-1);
	while (s[i])
	{
		if (s[i] == c)
			return (i);
		++i;
	}
	return (-1);
}
