#include "../inc/maze.h"
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

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
 * loadTexture - Loads an image file as an SDL texture.
 * @filePath: Path to the image file.
 *
 * Return: Pointer to the SDL texture, or NULL on failure.
 */
SDL_Texture *loadTexture(const char *filePath)
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

