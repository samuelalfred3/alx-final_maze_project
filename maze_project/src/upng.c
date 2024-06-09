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

