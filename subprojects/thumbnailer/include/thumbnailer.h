#include "epeg.h"

#ifndef H_THUMBNAILER
# define H_THUMBNAILER
# define SUPPORTED_IMAGES (char *[]) {"image/jpeg"}
# define NB_SUPPORTED_IMAGES 1

enum {JPEG = 0, PNG = 1};

enum {E_PATH = 50, E_ENCODE = 51, E_NOSUPPORT = 52};

// Create thumbnail from jpeg
int create_thumbnail_jpeg(char *src, char *dst, int width);
// Create thumbnail and guess the type of the file returns 0 if success
int create_thumbnail(char *src, char *dst, int width);

#endif