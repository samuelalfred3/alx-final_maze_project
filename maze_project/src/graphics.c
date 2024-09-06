#include "../inc/graphics_utils.h"
#include "../inc/game_config.h"
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <stdlib.h>
#include <stdio.h>

/* Globals for SDL */
extern SDL_Renderer *renderer;
extern SDL_Window *window;

/* Static variables for color buffer */
static color_t *colorBuffer = NULL;
static SDL_Texture *colorBufferTexture = NULL;

/* Globals for textures */
SDL_Texture *wallTextures[NUM_WALL_TEXTURES];

/* Function prototypes for internal use */
static SDL_Texture *loadTexture(const char *filePath);
static unsigned char *inflate_zlib(const unsigned char *data, unsigned length, unsigned *out_length);

/* Function Definitions */

/**
 * initializeWindow - Initializes the SDL window and renderer.
 *
 * Return: true on success, false on failure.
 */
bool initializeWindow(void)
{
	SDL_DisplayMode display_mode;
	int fullScreenWidth, fullScreenHeight;

	if (SDL_Init(SDL_INIT_EVERYTHING) != 0)
	{
		fprintf(stderr, "Error initializing SDL.\n");
		return (false);
	}

	SDL_GetCurrentDisplayMode(0, &display_mode);
	fullScreenWidth = display_mode.w;
	fullScreenHeight = display_mode.h;
	window = SDL_CreateWindow(
			NULL,
			SDL_WINDOWPOS_CENTERED,
			SDL_WINDOWPOS_CENTERED,
			fullScreenWidth,
			fullScreenHeight,
			SDL_WINDOW_BORDERLESS
			);

	if (!window)
	{
		fprintf(stderr, "Error creating SDL window.\n");
		return (false);
	}

	renderer = SDL_CreateRenderer(window, -1, 0);
	if (!renderer)
	{
		fprintf(stderr, "Error creating SDL renderer.\n");
		return (false);
	}

	SDL_SetRenderDrawBlendMode(renderer, SDL_BLENDMODE_BLEND);

	colorBuffer = (color_t *)malloc(sizeof(color_t) * fullScreenWidth * fullScreenHeight);
	colorBufferTexture = SDL_CreateTexture(
			renderer,
			SDL_PIXELFORMAT_ARGB8888,
			SDL_TEXTUREACCESS_STREAMING,
			fullScreenWidth,
			fullScreenHeight
			);

	return (true);
}

/**
 * destroyWindow - Cleans up and destroys the SDL window and renderer.
 */
void destroyWindow(void)
{
	free(colorBuffer);
	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);
	SDL_Quit();
}

/**
 * clearColorBuffer - Clears the color buffer with a given color.
 * @color: Color to clear the buffer with.
 */
void clearColorBuffer(color_t color)
{
	for (int i = 0; i < SCREEN_WIDTH * SCREEN_HEIGHT; i++)
	{
		colorBuffer[i] = color;
	}
}

/**
 * renderColorBuffer - Renders the color buffer to the screen.
 */
void renderColorBuffer(void)
{
	SDL_UpdateTexture(
			colorBufferTexture,
			NULL,
			colorBuffer,
			SCREEN_WIDTH * sizeof(color_t)
			);
	SDL_RenderCopy(renderer, colorBufferTexture, NULL, NULL);
	SDL_RenderPresent(renderer);
}

/**
 * drawPixel - Draws a pixel on the screen at (x, y) with a given color.
 * @x: The x-coordinate of the pixel.
 * @y: The y-coordinate of the pixel.
 * @color: The color of the pixel.
 */
void drawPixel(int x, int y, color_t color)
{
	if (x >= 0 && x < SCREEN_WIDTH && y >= 0 && y < SCREEN_HEIGHT)
	{
		colorBuffer[(SCREEN_WIDTH * y) + x] = color;
	}
}

/**
 * drawLine - Draws a line from (x0, y0) to (x1, y1) with a given color.
 * @x0: The starting x-coordinate.
 * @y0: The starting y-coordinate.
 * @x1: The ending x-coordinate.
 * @y1: The ending y-coordinate.
 * @color: The color of the line.
 */
void drawLine(int x0, int y0, int x1, int y1, color_t color)
{
	int deltaX = (x1 - x0);
	int deltaY = (y1 - y0);

	int longestSideLength = (abs(deltaX) >= abs(deltaY)) ? abs(deltaX) : abs(deltaY);

	float xIncrement = deltaX / (float)longestSideLength;
	float yIncrement = deltaY / (float)longestSideLength;

	float currentX = x0;
	float currentY = y0;

	for (int i = 0; i <= longestSideLength; i++)
	{
		drawPixel(round(currentX), round(currentY), color);
		currentX += xIncrement;
		currentY += yIncrement;
	}
}

/**
 * renderWall - Renders the walls based on the ray casting results.
 */
void renderWall(void)
{
	for (int i = 0; i < NUM_RAYS; i++)
	{
		int wallStripHeight = (TILE_SIZE / rays[i].distance) * DIST_PROJ_PLANE;
		int wallTopPixel = (SCREEN_HEIGHT / 2) - (wallStripHeight / 2);
		wallTopPixel = wallTopPixel < 0 ? 0 : wallTopPixel;
		int wallBottomPixel = (SCREEN_HEIGHT / 2) + (wallStripHeight / 2);
		wallBottomPixel = wallBottomPixel > SCREEN_HEIGHT ? SCREEN_HEIGHT : wallBottomPixel;
		for (int y = wallTopPixel; y < wallBottomPixel; y++)
		{
			drawPixel(i, y, rays[i].wallHitContent);
		}
	}
}

/**
 * loadTexture - Loads an image file as an SDL texture.
 * @filePath: Path to the image file.
 *
 * Return: Pointer to the SDL texture, or NULL on failure.
 */
static SDL_Texture *loadTexture(const char *filePath)
{
	SDL_Surface *surface = IMG_Load(filePath);
	if (!surface)
	{
		fprintf(stderr, "Error loading texture: %s\n", IMG_GetError());
		return (NULL);
	}
	SDL_Texture *texture = SDL_CreateTextureFromSurface(renderer, surface);
	SDL_FreeSurface(surface);
	return (texture);
}

/**
 * WallTexturesready - Loads wall textures into the wallTextures array.
 */
void WallTexturesready(void)
{
	wallTextures[0] = loadTexture("images/wall.png");
	wallTextures[1] = loadTexture("images/ground.png");
	wallTextures[2] = loadTexture("images/ceiling.png");
	wallTextures[3] = loadTexture("images/character.png");
}

/**
 * freeWallTextures - Frees all loaded wall textures.
 */
void freeWallTextures(void)
{
	for (int i = 0; i < NUM_WALL_TEXTURES; i++)
	{
		if (wallTextures[i])
		{
			SDL_DestroyTexture(wallTextures[i]);
			wallTextures[i] = NULL;
		}
	}
}

/**
 * inflate_zlib - Stub function for zlib inflation (not implemented).
 * @data: The compressed data.
 * @length: The length of the compressed data.
 * @out_length: The length of the decompressed data.
 * Return: Pointer to the decompressed data.
 */
static unsigned char *inflate_zlib(const unsigned char *data, unsigned length, unsigned *out_length)
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
upng_t *upng_new_from_bytes(const unsigned char *buffer, unsigned long size)
{
	upng_t *upng = (upng_t *)malloc(sizeof(upng_t));
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
upng_t *upng_new_from_file(const char *path)
{
	FILE *file = fopen(path, "rb");
	if (file == NULL)
	{
		return (NULL);
	}
	fseek(file, 0, SEEK_END);
	long size = ftell(file);
	fseek(file, 0, SEEK_SET);

	unsigned char *buffer = (unsigned char *)malloc(size);
	if (buffer == NULL)
	{
		fclose(file);
		return (NULL);
	}

	fread(buffer, 1, size, file);
	fclose(file);

	upng_t *upng = upng_new_from_bytes(buffer, size);
	free(buffer);

	return (upng);
}

/**
 * upng_free - Frees a UPNG object.
 * @upng: Pointer to the UPNG object.
 */
void upng_free(upng_t *upng)
{
	if (upng != NULL)
	{
		free(upng);
	}
}

/**
 * upng_header - Stub function for UPNG header processing (not implemented).
 * @upng: Pointer to the UPNG object.
 * Return: UPNG error code.
 */
upng_error upng_header(upng_t *upng)
{
	(void)upng;
	return (UPNG_EOK);
}

/**
 * upng_decode - Stub function for UPNG decoding (not implemented).
 * @upng: Pointer to the UPNG object.
 * Return: UPNG error code.
 */
upng_error upng_decode(upng_t *upng)
{
	(void)upng;
	return (UPNG_EOK);
}

/**
 * upng_get_error - Retrieves the error code from a UPNG object.
 * @upng: Pointer to the UPNG object.
 * Return: UPNG error code.
 */
upng_error upng_get_error(const upng_t *upng)
{
	return (upng->error);
}

/**
 * upng_get_error_line - Retrieves the error line from a UPNG object.
 * @upng: Pointer to the UPNG object.
 * Return: Error line number.
 */
unsigned upng_get_error_line(const upng_t *upng)
{
	(void)upng;
	return (0);
}

/**
 * upng_get_width - Retrieves the width of the UPNG image.
 * @upng: Pointer to the UPNG object.
 * Return: Width of the image.
 */
unsigned upng_get_width(const upng_t *upng)
{
	return (upng->width);
}

/**
 * upng_get_height - Retrieves the height of the UPNG image.
 * @upng: Pointer to the UPNG object.
 * Return: Height of the image.
 */
unsigned upng_get_height(const upng_t *upng)
{
	return (upng->height);
}

/**
 * upng_get_bpp - Retrieves the bytes per pixel of the UPNG image.
 * @upng: Pointer to the UPNG object.
 * Return: Bytes per pixel.
 */
unsigned upng_get_bpp(const upng_t *upng)
{
	return (upng->bpp);
}

/**
 * upng_get_bitdepth - Retrieves the bit depth of the UPNG image.
 * @upng: Pointer to the UPNG object.
 * Return: Bit depth.
 */
unsigned upng_get_bitdepth(const upng_t *upng)
{
	return (upng->bitdepth);
}

/**
 * upng_get_pixelsize - Retrieves the pixel size of the UPNG image.
 * @upng: Pointer to the UPNG object.
 * Return: Pixel size.
 */
unsigned upng_get_pixelsize(const upng_t *upng)
{
	return (upng->pixelsize);
}

/**
 * upng_get_rowbytes - Retrieves the row bytes of the UPNG image.
 * @upng: Pointer to the UPNG object.
 * Return: Row bytes.
 */
unsigned upng_get_rowbytes(const upng_t *upng)
{
	return (upng->rowbytes);
}

/**
 * upng_get_format - Retrieves the format of the UPNG image.
 * @upng: Pointer to the UPNG object.
 * Return: UPNG format.
 */
upng_format upng_get_format(const upng_t *upng)
{
	return (upng->format);
}

/**
 * upng_get_buffer - Retrieves the buffer of the UPNG image.
 * @upng: Pointer to the UPNG object.
 * Return: Pointer to the buffer.
 */
const unsigned char *upng_get_buffer(const upng_t *upng)
{
	return (upng->buffer);
}

