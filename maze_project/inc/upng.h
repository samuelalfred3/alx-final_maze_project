#ifndef UPNG_H
#define UPNG_H

#include <stddef.h>

typedef enum upng_error {
	UPNG_EOK            = 0, /* success (no error) */
	UPNG_ENOMEM         = 1, /* memory allocation failed */
	UPNG_ENOTFOUND      = 2, /* resource not found */
	UPNG_EMALFORMED     = 3, /* image data is malformed */
	UPNG_EUNSUPPORTED   = 4, /* image format is not supported */
	UPNG_EUNINTERLACED  = 5, /* image is not interlaced */
	UPNG_EUNKNOWN       = 6  /* unknown error */
} upng_error;

typedef enum upng_format {
	UPNG_BADFORMAT,
	UPNG_RGB8,
	UPNG_RGBA8
} upng_format;

typedef struct upng_t upng_t;

upng_t* upng_new_from_bytes(const unsigned char* buffer, unsigned long size);
upng_t* upng_new_from_file(const char* path);
void upng_free(upng_t* upng);

upng_error upng_header(upng_t* upng);
upng_error upng_decode(upng_t* upng);

upng_error upng_get_error(const upng_t* upng);
unsigned upng_get_error_line(const upng_t* upng);

unsigned upng_get_width(const upng_t* upng);
unsigned upng_get_height(const upng_t* upng);
unsigned upng_get_bpp(const upng_t* upng);
unsigned upng_get_bitdepth(const upng_t* upng);
unsigned upng_get_pixelsize(const upng_t* upng);
unsigned upng_get_rowbytes(const upng_t* upng);
upng_format upng_get_format(const upng_t* upng);
const unsigned char* upng_get_buffer(const upng_t* upng);

#endif /*defined(UPNG_H)*/

