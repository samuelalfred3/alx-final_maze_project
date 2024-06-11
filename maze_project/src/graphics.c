#include "../inc/game.h"
#include "../inc/upng.h"
#include "../inc/window.h"
#include "../inc/graphics.h"
#include "../inc/map.h"
#include "../inc/textures.h"
#include "../inc/ray.h"
#include "../inc/player.h"
#include "../inc/config.h"
#include <SDL2/SDL.h>
#include <stdlib.h>

SDL_Renderer *renderer;
static color_t *colorBuffer;
static SDL_Texture *colorBufferTexture;

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
	colorBuffer = (color_t*)malloc(sizeof(color_t) * fullScreenWidth * fullScreenHeight);
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

