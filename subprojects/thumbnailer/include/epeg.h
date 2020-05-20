#ifndef EPEG_H
# define EPEG_H
# ifdef EAPI
#  undef EAPI
# endif
# ifdef WIN32
#  ifdef BUILDING_DLL
#   define EAPI __declspec(dllexport)
#  else
#   define EAPI __declspec(dllimport)
#  endif
# else
#  ifdef __GNUC__
#   if __GNUC__ >= 4
#    define EAPI __attribute__ ((visibility("default")))
#   else
#    define EAPI
#   endif
#  else
#   define EAPI
#  endif
# endif
# ifdef __cplusplus
extern "C" 
{
# endif

typedef enum _Epeg_Colorspace
{	
												EPEG_GRAY8,
												EPEG_YUV8,
												EPEG_RGB8,
												EPEG_BGR8,
												EPEG_RGBA8,
												EPEG_BGRA8,
												EPEG_ARGB32,
												EPEG_CMYK
} Epeg_Colorspace;

typedef struct _Epeg_Image						Epeg_Image;
typedef struct _Epeg_Thumbnail_Info				Epeg_Thumbnail_Info;

struct _Epeg_Thumbnail_Info
{
	char										*uri;
	unsigned long long int						mtime;
	int											w, h;
	char										*mimetype;
};

EAPI Epeg_Image	*epeg_file_open					(const char *file);
EAPI Epeg_Image	*epeg_memory_open				(unsigned char *data, int size);
EAPI Epeg_Image	*epeg_memory_open				(unsigned char *data, int size);
EAPI void		epeg_size_get					(Epeg_Image *im, int *w, int *h);
EAPI void		epeg_decode_size_set			(Epeg_Image *im, int w, int h);
EAPI void		epeg_colorspace_get				(Epeg_Image *im, int *space);
EAPI void		epeg_decode_colorspace_set		(Epeg_Image *im, Epeg_Colorspace colorspace);
EAPI const void	*epeg_pixels_get				(Epeg_Image *im, int x, int y, int w, int h);
EAPI void		epeg_pixels_free				(Epeg_Image *im, const void *data);
EAPI const char	*epeg_comment_get				(Epeg_Image *im);
EAPI void		epeg_thumbnail_comments_get		(Epeg_Image *im, Epeg_Thumbnail_Info *info);
EAPI void		epeg_comment_set				(Epeg_Image *im, const char *comment);
EAPI void		epeg_quality_set				(Epeg_Image *im, int quality);
EAPI void		epeg_thumbnail_comments_enable	(Epeg_Image *im, int onoff);
EAPI void		epeg_file_output_set			(Epeg_Image *im, const char *file);
EAPI void		epeg_memory_output_set			(Epeg_Image *im, unsigned char **data, int *size);
EAPI int		epeg_encode						(Epeg_Image *im);
EAPI int		epeg_trim						(Epeg_Image *im);
EAPI void		epeg_close						(Epeg_Image *im);

# ifdef __cplusplus
}
# endif

#endif


#ifndef EPEG_PRIVATE_H
#define EPEG_PRIVATE_H

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>
#include <time.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <setjmp.h>
#include <jpeglib.h>
#include <libexif/exif-data.h>

typedef struct _epeg_error_mgr		*emptr;

struct _epeg_error_mgr
{
	struct							jpeg_error_mgr pub;
	jmp_buf							setjmp_buffer;
};

struct _Epeg_Image
{
	struct _epeg_error_mgr			jerr;
	struct stat						stat_info;
	unsigned char					*pixels;
	unsigned char					**lines;
	char							scaled : 1;
	int								error;
	Epeg_Colorspace					color_space;

struct 
{
	char							*file;
	struct
	{
		unsigned char				**data;
		int							size;
	} mem;
	int								w, h;
	char							*comment;
	FILE							*f;
	J_COLOR_SPACE					color_space;
	int								orientation;  /* Exif orientation values 0-8 */
	struct jpeg_decompress_struct	jinfo;
	struct
	{
		char						*uri;
		unsigned long long int		mtime;
		int							w, h;
		char						*mime;
	} thumb_info;
} in;

struct 
{
	char							*file;
	struct
	{
		unsigned char				**data;
		int							*size;
	} mem;
	int								x, y;
	int								w, h;
	char							*comment;
	FILE							*f;
	struct jpeg_compress_struct		jinfo;
	int								quality;
	char							thumbnail_info : 1;
	} out;
};

// METHODDEF(void)						_jpeg_decompress_error_exit(j_common_ptr cinfo);
void 					_jpeg_init_source(j_decompress_ptr cinfo);
boolean					_jpeg_fill_input_buffer(j_decompress_ptr cinfo);
void 					_jpeg_skip_input_data(j_decompress_ptr cinfo, long num_bytes);
void					_jpeg_term_source(j_decompress_ptr cinfo);

void					_jpeg_init_destination(j_compress_ptr cinfo);
boolean					_jpeg_empty_output_buffer (j_compress_ptr cinfo);
void					_jpeg_term_destination (j_compress_ptr cinfo);
	
// METHODDEF(void)						_emit_message (j_common_ptr cinfo, int msg_level);
// METHODDEF(void)						_output_message (j_common_ptr cinfo);
// METHODDEF(void)						_format_message (j_common_ptr cinfo, char * buffer);

#endif
