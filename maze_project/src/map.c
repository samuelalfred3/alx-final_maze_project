#include <stdio.h>
#include <string.h>
#include "../inc/config.h"
#include "../inc/game.h"

char map[MAP_HEIGHT][MAP_WIDTH + 1] = {
	"66666666666666666666",
	"60000060000600000006",
	"60000000011110000006",
	"60101010001000770006",
	"60000000000000700006",
	"60000000000000070006",
	"60000777700011077006",
	"60000000000000000006",
	"60001000000000010006",
	"60001010000000710006",
	"60006600000000000006",
	"60000060000000000006",
	"66666666666666666666"
};

/**
 * get_map_value - Get map value at specific position.
 * @x: X-coordinate on the map.
 * @y: Y-coordinate on the map.
 * Return: The value at the given coordinates or -1 if out of bounds.
 */
int get_map_value(int x, int y)
{
	if (x < 0 || x >= MAP_WIDTH || y < 0 || y >= MAP_HEIGHT)
		return -1; /* Out of bounds */
	return map[y][x];
}

