#include "../inc/maze.h"

/**
 * drawRect - Draws a rectangle on the screen.
 * @x: X coordinate of the rectangle's top-left corner.
 * @y: Y coordinate of the rectangle's top-left corner.
 * @width: Width of the rectangle.
 * @height: Height of the rectangle.
 * @color: Color of the rectangle (in color_t format).
 */
void drawRect(int x, int y, int width, int height, color_t color)
{
	int i, j;

	/* Loop through each pixel inside the rectangle */
	for (i = x; i <= (x + width); i++)
	{
		for (j = y; j <= (y + height); j++)
		{
			drawPixel(i, j, color);  /* Draw individual pixels */
		}
	}
}

/**
 * drawLine - Draws a line between two points.
 * @x0: Starting X coordinate.
 * @y0: Starting Y coordinate.
 * @x1: Ending X coordinate.
 * @y1: Ending Y coordinate.
 * @color: Color of the line (in color_t format).
 */
void drawLine(int x0, int y0, int x1, int y1, color_t color)
{
	float xIncrement, yIncrement, currentX, currentY;
	int i, longestSideLength, deltaX, deltaY;

	deltaX = (x1 - x0);
	deltaY = (y1 - y0);

    /* Determine the longest side to decide the number of iterations */
	longestSideLength = (abs(deltaX) >= abs(deltaY)) ? abs(deltaX) : abs(deltaY);

	xIncrement = deltaX / (float)longestSideLength;
	yIncrement = deltaY / (float)longestSideLength;

	currentX = x0;
	currentY = y0;

	/* Loop through and plot each point of the line */
	for (i = 0; i < longestSideLength; i++)
	{
		drawPixel(round(currentX), round(currentY), color);
		currentX += xIncrement;
		currentY += yIncrement;
	}
}

