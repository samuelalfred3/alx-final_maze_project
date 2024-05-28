#include <math.h>
#include "graphics.h"
#include "game.h"
#include "config.h"

/* Function to create the SDL window */
SDL_Window *create_window(void)
{
	return SDL_CreateWindow("Maze Game", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
}

/* Function to create the SDL renderer */
SDL_Renderer *create_renderer(SDL_Window *window)
{
	return SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
}

/* Function to load textures */
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

/* Function to render the game */
void render_game(SDL_Renderer *renderer, GameState *state, SDL_Texture **textures)
{
	/* Clear screen */
	SDL_RenderClear(renderer);

	/* Draw the scene */
	draw_walls(renderer, state, textures[0]);
	draw_floor_and_ceiling(renderer, textures[1], textures[2]);

	/* Present the back buffer */
	SDL_RenderPresent(renderer);
}

/* Function to draw walls using raycasting */
void draw_walls(SDL_Renderer *renderer, GameState *state, SDL_Texture *wallTexture)
{
	for (int x = 0; x < SCREEN_WIDTH; x++)
	{
		/* Calculate ray position and direction */
		double cameraX = 2 * x / (double)SCREEN_WIDTH - 1;
		double rayDirX = state->playerDirX + state->planeX * cameraX;
		double rayDirY = state->playerDirY + state->planeY * cameraX;

		/* Which box of the map we're in */
		int mapX = (int)state->playerPosX;
		int mapY = (int)state->playerPosY;

		/* Length of ray from current position to next x or y-side */
		double sideDistX;
		double sideDistY;

		/* Length of ray from one x or y-side to next x or y-side */
		double deltaDistX = fabs(1 / rayDirX);
		double deltaDistY = fabs(1 / rayDirY);
		double perpWallDist;

		/* Direction to go in x and y */
		int stepX;
		int stepY;

		int hit = 0; /* Was there a wall hit? */
		int side; /* Was a NS or a EW wall hit? */

		/* Calculate step and initial sideDist */
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

		/* Perform DDA */
		while (hit == 0)
		{
			/* Jump to next map square, OR in x-direction, OR in y-direction */
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
			/* Check if ray has hit a wall */
			if (map[mapY][mapX] == '#') hit = 1;
		}

		/* Calculate distance projected on camera direction */
		if (side == 0)
			perpWallDist = (mapX - state->playerPosX + (1 - stepX) / 2) / rayDirX;
		else
			perpWallDist = (mapY - state->playerPosY + (1 - stepY) / 2) / rayDirY;

		/* Calculate height of line to draw on screen */
		int lineHeight = (int)(SCREEN_HEIGHT / perpWallDist);

		/* Calculate lowest and highest pixel to fill in current stripe */
		int drawStart = -lineHeight / 2 + SCREEN_HEIGHT / 2;
		if (drawStart < 0) drawStart = 0;
		int drawEnd = lineHeight / 2 + SCREEN_HEIGHT / 2;
		if (drawEnd >= SCREEN_HEIGHT) drawEnd = SCREEN_HEIGHT - 1;

		/* Draw the pixels of the stripe as a vertical line */
		SDL_Rect wallRect = { x, drawStart, 1, drawEnd - drawStart };
		SDL_RenderCopy(renderer, wallTexture, NULL, &wallRect);
	}
}

/* Function to draw floor and ceiling */
void draw_floor_and_ceiling(SDL_Renderer *renderer, SDL_Texture *groundTexture, SDL_Texture *ceilingTexture)
{
	SDL_Rect groundRect = { 0, SCREEN_HEIGHT / 2, SCREEN_WIDTH, SCREEN_HEIGHT / 2 };
	SDL_RenderCopy(renderer, groundTexture, NULL, &groundRect);

	SDL_Rect ceilingRect = { 0, 0, SCREEN_WIDTH, SCREEN_HEIGHT / 2 };
	SDL_RenderCopy(renderer, ceilingTexture, NULL, &ceilingRect);
}

/* Function to clean up textures */
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

