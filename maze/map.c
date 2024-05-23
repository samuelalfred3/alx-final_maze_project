#include "maze.h"

void getWorldMap(int worldMap[MAP_WIDTH][MAP_HEIGHT])
{
	int map[MAP_WIDTH][MAP_HEIGHT] = {
		{1, 1, 1, 1, 1, 1, 1},
		{1, 0, 0, 0, 0, 0, 1},
		{1, 0, 0, 0, 0, 0, 1},
		{1, 0, 0, 0, 0, 0, 1},
		{1, 0, 0, 0, 0, 0, 1},
		{1, 0, 0, 0, 0, 0, 1},
		{1, 1, 1, 1, 1, 1, 1}
	};

	for (int i = 0; i < MAP_WIDTH; i++)
	{
		for (int j = 0; j < MAP_HEIGHT; j++)
		{
			worldMap[i][j] = map[i][j];
		}
	}
}

