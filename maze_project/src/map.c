#include "../inc/map.h"
#include "../inc/graphics.h"
#include "../inc/config.h"
#include "../inc/game.h"
#include "../inc/textures.h"

const int map[MAP_NUM_ROWS][MAP_NUM_COLS] = {
	/* map layout */
	{1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
	{1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
	{1, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 1},
	{1, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 1},
	{1, 0, 1, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0, 1, 0, 1},
	{1, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 1, 0, 1, 0, 1},
	{1, 1, 1, 0, 1, 0, 1, 1, 1, 1, 1, 1, 0, 1, 0, 1, 0, 1, 0, 1},
	{1, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1},
	{1, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 1, 0, 1, 0, 1, 0, 1},
	{1, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1},
	{1, 0, 1, 1, 1, 1, 1, 1, 1, 1, 0, 1, 0, 1, 0, 0, 0, 1, 0, 1},
	{1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
	{1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1}
};

/**
 * DetectCollision - Detects collision at given coordinates.
 * @x: X-coordinate to check.
 * @y: Y-coordinate to check.
 *
 * Return: true if there is a collision, false otherwise.
 */
bool DetectCollision(float x, float y)
{
	if (x < 0 || x >= SCREEN_WIDTH || y < 0 || y >= SCREEN_HEIGHT)
	{
		return (true);
	}
	int mapX = floor(x / TILE_SIZE);
	int mapY = floor(y / TILE_SIZE);
	return (map[mapY][mapX] != 0);
}

/**
 * getMapValue - Gets the value at a specific row and column in the map.
 * @row: Row index.
 * @col: Column index.
 *
 * Return: Value at the specified row and column, or -1 if out of bounds.
 */
int getMapValue(int row, int col)
{
	if (row >= 0 && row < MAP_NUM_ROWS && col >= 0 && col < MAP_NUM_COLS)
	{
		return (map[row][col]);
	}
	return (-1);
}

