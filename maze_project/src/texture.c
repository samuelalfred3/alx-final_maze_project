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
 * WallTexturesready - Sets default colors for the walls and character.
 */
void WallTexturesready(void)
{
	wallColors[0] = 0xFF0000FF; /* Red walls */
	wallColors[1] = 0x00FF00FF; /* Green ground */
	wallColors[2] = 0x0000FFFF; /* Blue ceiling */
	wallColors[3] = 0xFFFFFFFF; /* White character */
}

/**
 * drawWall - Draws a wall with a specific color based on wall type.
 * @x: The x-coordinate.
 * @y: The y-coordinate.
 * @wallType: The type of the wall.
 */
void drawWall(int x, int y, int wallType)
{
	if (wallType >= 0 && wallType < 4)
	{
		color_t color = wallColors[wallType];
		drawPixel(x, y, color);
	}
}

