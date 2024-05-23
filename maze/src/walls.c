#include "maze.h"

void drawWalls(Global *g, int worldMap[MAP_WIDTH][MAP_HEIGHT])
{
	int x, y;

	for (x = 0; x < MAP_WIDTH; x++)
	{
		for (y = 0; y < MAP_HEIGHT; y++)
		{
			if (worldMap[x][y] > 0)
			{
				SDL_Rect wallRect;

				wallRect.x = x * TILE_SIZE;
				wallRect.y = y * TILE_SIZE;
				wallRect.w = TILE_SIZE;
				wallRect.h = TILE_SIZE;

				if (worldMap[x][y] == 1)
				{
					SDL_SetRenderDrawColor(g->renderer, 0xFF, 0x00, 0x00, 0xFF);
				} else if (worldMap[x][y] == 2)
				{
					SDL_SetRenderDrawColor(g->renderer, 0x00, 0x00, 0xFF, 0xFF);
				}

				SDL_RenderFillRect(g->renderer, &wallRect);
			}
		}
	}
}

