#include "maze.h"

void performRaycasting(Global *g, int worldMap[MAP_WIDTH][MAP_HEIGHT])
{
	int x;
	for (x = 0; x < WINDOW_WIDTH; x++)
	{
		double cameraX = 2 * x / (double)WINDOW_WIDTH - 1;
		double rayDirX = cos(g->player.angle + cameraX * FOV_ANGLE);
		double rayDirY = sin(g->player.angle + cameraX * FOV_ANGLE);

		int mapX = (int)g->player.x / TILE_SIZE;
		int mapY = (int)g->player.y / TILE_SIZE;

		double sideDistX;
		double sideDistY;

		double deltaDistX = fabs(1 / rayDirX);
		double deltaDistY = fabs(1 / rayDirY);
		double perpWallDist;

		int stepX;
		int stepY;

		int hit = 0;
		int side;

		if (rayDirX < 0)
		{
			stepX = -1;
			sideDistX = (g->player.x / TILE_SIZE - mapX) * deltaDistX;
		}
		else
		{
			stepX = 1;
			sideDistX = (mapX + 1.0 - g->player.x / TILE_SIZE) * deltaDistX;
		}
		if (rayDirY < 0)
		{
			stepY = -1;
			sideDistY = (g->player.y / TILE_SIZE - mapY) * deltaDistY;
		}
		else
		{
			stepY = 1;
			sideDistY = (mapY + 1.0 - g->player.y / TILE_SIZE) * deltaDistY;
		}
		while (hit == 0)
		{
			if (sideDistX < sideDistY)
			{
				sideDistX += deltaDistX;
				mapX += stepX;
				side = 0;
			}
			else
			{
				sideDistY += deltaDistY;
				mapY += stepY;
				side = 1;
			}
			if (worldMap[mapX][mapY] > 0)
				hit = 1;
		}

		if (side == 0)
			perpWallDist = (mapX - g->player.x / TILE_SIZE + (1 - stepX) / 2) / rayDirX;
		else
			perpWallDist = (mapY - g->player.y / TILE_SIZE + (1 - stepY) / 2) / rayDirY;

		int lineHeight = (int)(WINDOW_HEIGHT / perpWallDist);

		int drawStart = -lineHeight / 2 + WINDOW_HEIGHT / 2;
		if (drawStart < 0)
			drawStart = 0;
		int drawEnd = lineHeight / 2 + WINDOW_HEIGHT / 2;
		if (drawEnd >= WINDOW_HEIGHT)
			drawEnd = WINDOW_HEIGHT - 1;

		if (side == 0)
			SDL_SetRenderDrawColor(g->renderer, 0xFF, 0x00, 0x00, 0xFF);
		else
			SDL_SetRenderDrawColor(g->renderer, 0x00, 0x00, 0xFF, 0xFF);

		SDL_RenderDrawLine(g->renderer, x, drawStart, x, drawEnd);
	}
}

