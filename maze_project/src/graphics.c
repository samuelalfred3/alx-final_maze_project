#include <math.h>
#include <SDL.h>
#include <SDL_image.h>
#include "graphics.h"
#include "game.h"
#include "config.h"

SDL_Window *create_window(void)
{
	return SDL_CreateWindow("Maze Game", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
}

SDL_Renderer *create_renderer(SDL_Window *window)
{
	return SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
}

void load_textures(SDL_Renderer *renderer, SDL_Texture **textures)
{
	textures[0] = IMG_LoadTexture(renderer, "assets/textures/wall.png");
	textures[1] = IMG_LoadTexture(renderer, "assets/textures/ground.png");
	textures[2] = IMG_LoadTexture(renderer, "assets/textures/ceiling.png");

	if (!textures[0] || !textures[1] || !textures[2])
	{
		SDL_Log("Failed to load textures: %s", SDL_GetError());
	}
}

void render_game(SDL_Renderer *renderer, GameState *state, SDL_Texture **textures)
{
	SDL_RenderClear(renderer);

	draw_walls(renderer, state, textures[0]);
	draw_floor_and_ceiling(renderer, textures[1], textures[2]);

	SDL_RenderPresent(renderer);
}

void draw_walls(SDL_Renderer *renderer, GameState *state, SDL_Texture *wallTexture)
{
	for (int x = 0; x < SCREEN_WIDTH; x++)
	{
		double cameraX = 2 * x / (double)SCREEN_WIDTH - 1;
		double rayDirX = state->playerDirX + state->planeX * cameraX;
		double rayDirY = state->playerDirY + state->planeY * cameraX;

		int mapX = (int)state->playerPosX;
		int mapY = (int)state->playerPosY;

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
			sideDistX = (state->playerPosX - mapX) * deltaDistX;
		}
		else
		{
			stepX = 1;
			sideDistX = (mapX + 1.0 - state->playerPosX) * deltaDistX;
		}
		if (rayDirY < 0)
		{
			stepY = -1;
			sideDistY = (state->playerPosY - mapY) * deltaDistY;
		}
		else
		{
			stepY = 1;
			sideDistY = (mapY + 1.0 - state->playerPosY) * deltaDistY;
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
			if (map[mapY][mapX] == '#') hit = 1;
		}

		if (side == 0) perpWallDist = (mapX - state->playerPosX + (1 - stepX) / 2) / rayDirX;
		else perpWallDist = (mapY - state->playerPosY + (1 - stepY) / 2) / rayDirY;

		int lineHeight = (int)(SCREEN_HEIGHT / perpWallDist);

		int drawStart = -lineHeight / 2 + SCREEN_HEIGHT / 2;
		if (drawStart < 0) drawStart = 0;
		int drawEnd = lineHeight / 2 + SCREEN_HEIGHT / 2;
		if (drawEnd >= SCREEN_HEIGHT) drawEnd = SCREEN_HEIGHT - 1;

		SDL_Rect wallRect = {x, drawStart, 1, drawEnd - drawStart};
		SDL_RenderCopy(renderer, wallTexture, NULL, &wallRect);
	}
}

void draw_floor_and_ceiling(SDL_Renderer *renderer, SDL_Texture *groundTexture, SDL_Texture *ceilingTexture)
{
	SDL_Rect floorRect = {0, SCREEN_HEIGHT / 2, SCREEN_WIDTH, SCREEN_HEIGHT / 2};
	SDL_RenderCopy(renderer, groundTexture, NULL, &floorRect);

	SDL_Rect ceilingRect = {0, 0, SCREEN_WIDTH, SCREEN_HEIGHT / 2};
	SDL_RenderCopy(renderer, ceilingTexture, NULL, &ceilingRect);
}

void clean_up_textures(SDL_Texture **textures)
{
	for (int i = 0; i < NUM_TEXTURES; i++)
	{
		if (textures[i])
		{
			SDL_DestroyTexture(textures[i]);
		}
	}
}

