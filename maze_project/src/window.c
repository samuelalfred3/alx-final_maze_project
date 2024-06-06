#include "../inc/window.h"
#include <stdio.h>

static SDL_Window *window = NULL;
static SDL_Renderer *renderer = NULL;
static SDL_Texture *colorBufferTexture = NULL;
static Uint32 *colorBuffer = NULL;

/**
 * initializeWindow - Initialize the SDL window and renderer.
 * Return: true if successful, false otherwise.
 */
bool initializeWindow(void)
{
	if (SDL_Init(SDL_INIT_VIDEO) < 0)
	{
		fprintf(stderr, "SDL could not initialize: %s\n", SDL_GetError());
		return (false);
	}

	window = SDL_CreateWindow("Raycasting Maze",
			SDL_WINDOWPOS_CENTERED,
			SDL_WINDOWPOS_CENTERED,
			SCREEN_WIDTH,
			SCREEN_HEIGHT,
			SDL_WINDOW_SHOWN);
	if (window == NULL)
	{
		fprintf(stderr, "Window could not be created: %s\n", SDL_GetError());
		return (false);
	}

	renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
	if (renderer == NULL)
	{
		fprintf(stderr, "Renderer could not be created: %s\n", SDL_GetError());
		return (false);
	}

	colorBuffer = (Uint32 *)malloc(sizeof(Uint32) * SCREEN_WIDTH * SCREEN_HEIGHT);
	if (colorBuffer == NULL)
	{
		fprintf(stderr, "Could not allocate color buffer\n");
		return (false);
	}

	colorBufferTexture = SDL_CreateTexture(renderer,
			SDL_PIXELFORMAT_ARGB8888,
			SDL_TEXTUREACCESS_STREAMING,
			SCREEN_WIDTH,
			SCREEN_HEIGHT);
	if (colorBufferTexture == NULL)
	{
		fprintf(stderr, "Could not create color buffer texture: %s\n", SDL_GetError());
		return (false);
	}

	return (true);
}

/**
 * destroyWindow - Clean up and destroy the SDL window and renderer.
 */
void destroyWindow(void)
{
	if (colorBufferTexture)
	{
		SDL_DestroyTexture(colorBufferTexture);
		colorBufferTexture = NULL;
	}

	if (colorBuffer)
	{
		free(colorBuffer);
		colorBuffer = NULL;
	}

	if (renderer)
	{
		SDL_DestroyRenderer(renderer);
		renderer = NULL;
	}

	if (window)
	{
		SDL_DestroyWindow(window);
		window = NULL;
	}

	SDL_Quit();
}

/**
 * clearColorBuffer - Clear the color buffer with a specific color.
 * @color: The color to clear the buffer with.
 */
void clearColorBuffer(color_t color)
{
	Uint32 clearColor = (color.a << 24) | (color.r << 16) | (color.g << 8) | color.b;
	for (int y = 0; y < SCREEN_HEIGHT; y++)
	{
		for (int x = 0; x < SCREEN_WIDTH; x++)
		{
			colorBuffer[(SCREEN_WIDTH * y) + x] = clearColor;
		}
	}
}

/**
 * renderColorBuffer - Render the color buffer to the screen.
 */
void renderColorBuffer(void)
{
	SDL_UpdateTexture(colorBufferTexture, NULL, colorBuffer, SCREEN_WIDTH * sizeof(Uint32));
	SDL_RenderCopy(renderer, colorBufferTexture, NULL, NULL);
	SDL_RenderPresent(renderer);
}

/**
 * drawPixel - Draw a pixel on the color buffer.
 * @x: The x coordinate of the pixel.
 * @y: The y coordinate of the pixel.
 * @color: The color of the pixel.
 */
void drawPixel(int x, int y, color_t color)
{
	if (x < 0 || x >= SCREEN_WIDTH || y < 0 || y >= SCREEN_HEIGHT)
	{
		return;
	}
	Uint32 pixelColor = (color.a << 24) | (color.r << 16) | (color.g << 8) | color.b;
	colorBuffer[(SCREEN_WIDTH * y) + x] = pixelColor;
}

