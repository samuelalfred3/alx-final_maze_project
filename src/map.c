#include "../inc/maze.h"

static const int map[MAP_NUM_ROWS][MAP_NUM_COLS] = {
	{6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6},
	{6, 0, 0, 0, 6, 0, 0, 0, 0, 0, 0, 6, 0, 0, 0, 0, 0, 0, 0, 6},
	{6, 0, 0, 0, 0, 0, 1, 1, 1, 1, 0, 6, 0, 0, 0, 6, 0, 0, 0, 6},
	{6, 0, 1, 0, 1, 0, 1, 0, 0, 1, 0, 6, 0, 7, 7, 0, 0, 0, 0, 6},
	{6, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 6, 0, 0, 0, 0, 0, 7, 0, 6},
	{6, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 7, 0, 6},
	{6, 0, 0, 0, 0, 0, 7, 7, 7, 0, 0, 1, 0, 0, 0, 0, 7, 7, 0, 6},
	{6, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 6},
	{6, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 7, 0, 0, 0, 0, 1, 0, 6},
	{6, 0, 0, 1, 0, 1, 1, 1, 0, 0, 0, 0, 7, 0, 0, 0, 0, 1, 0, 6},
	{6, 0, 0, 6, 6, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 6},
	{6, 0, 0, 0, 6, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 6},
	{6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6}
};

/**
 * DetectCollision - Checks if there could be a collision
 * with the wall in the next player advance.
 * @x: Next x coordinate.
 * @y: Next y coordinate.
 * Return: true if collision is detected, false otherwise.
 */
bool DetectCollision(float x, float y)
{
	if (x < 0 || x >= MAP_NUM_COLS * TILE_SIZE ||
			y < 0 || y >= MAP_NUM_ROWS * TILE_SIZE)
	{
		return (true);
	}

	int mapGridX = floor(x / TILE_SIZE);
	int mapGridY = floor(y / TILE_SIZE);

	return (map[mapGridY][mapGridX] != 0); /* Collision detected if not 0 */
}

/**
 * isInsideMap - Check if we continue within the map.
 * @x: Next x coordinate.
 * @y: Next y coordinate.
 * Return: true if it is within the map, false otherwise.
 */
bool isInsideMap(float x, float y)
{
	return ((x >= 0 && x < MAP_NUM_COLS * TILE_SIZE &&
			y >= 0 && y < MAP_NUM_ROWS * TILE_SIZE));
}

/**
 * getMapValue - Get the value at a specific position in the map.
 * @row: Row to check.
 * @col: Column to check.
 * Return: The position value in the map.
 */
int getMapValue(int row, int col)
{
	return (map[row][col]);
}

/**
 * renderMap - Render the map.
 */
void renderMap(void)
{
	for (int i = 0; i < MAP_NUM_ROWS; i++)
	{
		for (int j = 0; j < MAP_NUM_COLS; j++)
		{
			int tileX = j * TILE_SIZE;
			int tileY = i * TILE_SIZE;
			color_t tileColor = map[i][j] != 0 ? 0xFFFFFFFF : 0x00000000;

			drawRect(
					tileX * MINIMAP_SCALE_FACTOR,
					tileY * MINIMAP_SCALE_FACTOR,
					TILE_SIZE * MINIMAP_SCALE_FACTOR,
					TILE_SIZE * MINIMAP_SCALE_FACTOR,
					tileColor
					);
		}
	}
}

