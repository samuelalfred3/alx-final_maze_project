#include "../inc/upng.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

/**
 * inflate_zlib - Stub function for zlib inflation (not implemented).
 * @data: The compressed data.
 * @length: The length of the compressed data.
 * @out_length: The length of the decompressed data.
 * Return: Pointer to the decompressed data.
 */
static unsigned char* inflate_zlib(const unsigned char* data, unsigned length, unsigned* out_length)
{
	(void)data;
	(void)length;
	(void)out_length;
	return (NULL);
}

/**
 * upng_new_from_bytes - Create a new UPNG object from a byte buffer.
 * @buffer: The byte buffer containing the PNG data.
 * @size: The size of the buffer.
 * Return: Pointer to the UPNG object.
 */
upng_t* upng_new_from_bytes(const unsigned char* buffer, unsigned long size)
{
	upng_t* upng = (upng_t*)malloc(sizeof(upng_t));
	if (upng == NULL)
	{
		return (NULL);
	}

	/* Initialize UPNG object properties */
	upng->buffer = buffer;
	upng->size = size;
	upng->error = UPNG_EOK;
	upng->width = 0;
	upng->height = 0;
	upng->bpp = 0;
	upng->bitdepth = 0;
	upng->pixelsize = 0;
	upng->rowbytes = 0;
	upng->format = UPNG_BADFORMAT;

	upng_error error = upng_header(upng);
	if (error != UPNG_EOK)
	{
		free(upng);
		return (NULL);
	}

	return (upng);
}

/**
 * upng_new_from_file - Create a new UPNG object from a file.
 * @path: The path to the PNG file.
 * Return: Pointer to the UPNG object.
 */
upng_t* upng_new_from_file(const char* path)
{
	FILE* file = fopen(path, "rb");
	if (file == NULL)
	{
		return (NULL);
	}

	fseek(file, 0, SEEK_END);
	long size = ftell(file);
	fseek(file, 0, SEEK_SET);

	unsigned char* buffer = (unsigned char*)malloc(size);
	if (buffer == NULL)
	{
		fclose(file);
		return (NULL);
	}

	fread(buffer, 1, size, file);
	fclose(file);

	upng_t* upng = upng_new_from_bytes(buffer, size);
	free(buffer);

	return (upng);
}

void upng_free(upng_t* upng)
{
	if (upng != NULL)
	{
		free(upng);
	}
}

upng_error upng_header(upng_t* upng)
{
	(void)upng;
	return (UPNG_EOK);
}

upng_error upng_decode(upng_t* upng)
{
	(void)upng;
	return (UPNG_EOK);
}

upng_error upng_get_error(const upng_t* upng)
{
	return (upng->error);
}

unsigned upng_get_error_line(const upng_t* upng)
{
	(void)upng;
	return (0);
}

unsigned upng_get_width(const upng_t* upng)
{
	return (upng->width);
}

unsigned upng_get_height(const upng_t* upng)
{
	return (upng->height);
}

unsigned upng_get_bpp(const upng_t* upng)
{
	return (upng->bpp);
}

unsigned upng_get_bitdepth(const upng_t* upng)
{
	return (upng->bitdepth);
}

unsigned upng_get_pixelsize(const upng_t* upng)
{
	return (upng->pixelsize);
}

unsigned upng_get_rowbytes(const upng_t* upng)
{
	return (upng->rowbytes);
}

upng_format upng_get_format(const upng_t* upng)
{
	return (upng->format);
}

const unsigned char* upng_get_buffer(const upng_t* upng)
{
	return (upng->buffer);
}

