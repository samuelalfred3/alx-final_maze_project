#include "../inc/maze.h"
#include <SDL2/SDL.h>
#include <stdlib.h>
#include <stdio.h>

/* Globals for SDL */
extern SDL_Renderer *renderer;
extern SDL_Window *window;

/* Globals for textures */
Texture wallTextures[NUM_WALL_TEXTURES];

/**
 * initializeWindow - Initializes the SDL window and renderer.
 *
 * Return: true on success, false on failure.
 */
bool initializeWindow(void)
{
	SDL_DisplayMode display_mode;
	int fullScreenWidth, fullScreenHeight;

	if (SDL_Init(SDL_INIT_VIDEO) != 0)
	{
		fprintf(stderr, "Error initializing SDL.\n");
		return (false);
	}

	if (SDL_GetCurrentDisplayMode(0, &display_mode) != 0)
	{
		fprintf(stderr, "Error getting display mode. \n");
		return (false);
	}

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
		fprintf(stderr, "Error creating SDL window: %s\n", SDL_GetError());
		return (false);
	}

	renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
	if (!renderer)
	{
		fprintf(stderr, "Error creating SDL window: %s\n", SDL_GetError());
		return (false);
	}

	SDL_SetRenderDrawBlendMode(renderer, SDL_BLENDMODE_BLEND);

	colorBuffer = (uint32_t *)malloc(sizeof(uint32_t) * fullScreenWidth * fullScreenHeight);
	if (!colorBuffer)
	{
		fprintf(stderr, "Error allocating memory for color buffer.\n");
		return (false);
	}

	colorBufferTexture = SDL_CreateTexture(
			renderer,
			SDL_PIXELFORMAT_ARGB8888,
			SDL_TEXTUREACCESS_STREAMING,
			fullScreenWidth,
			fullScreenHeight
			);

	if (!colorBufferTexture)
	{
		fprintf(stderr, "Error creating color buffer texture: %s\n", SDL_GetError());
		free(colorBuffer);
		return (false);
	}

	return (true);
}

/**
 * destroyWindow - Cleans up and destroys the SDL window and renderer.
 */
void destroyWindow(void)
{
	free(colorBuffer);
	SDL_DestroyTexture(colorBufferTexture);
	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);
	SDL_Quit();
}

/**
 * clearColorBuffer - Clears the color buffer with a given color.
 * @color: Color to clear the buffer with.
 */
void clearColorBuffer(uint32_t color)
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
			SCREEN_WIDTH * sizeof(uint32_t)
			);
	SDL_RenderCopy(renderer, colorBufferTexture, NULL, NULL);
	SDL_RenderPresent(renderer);
}

