#include "../inc/maze.h"
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>"
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

