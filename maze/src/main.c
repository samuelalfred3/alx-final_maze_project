#include <stdio.h>
#include "maze.h"

/* Function prototypes */
int init(Global *g);
void close(Global *g);

int worldMap[MAP_WIDTH][MAP_HEIGHT] = {
	{1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
	{1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
	{1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
	{1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
	{1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
	{1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
	{1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1}
};

int init(Global *g)
{
	if (SDL_Init(SDL_INIT_VIDEO) < 0)
	{
		printf("SDL could not initialize! SDL_Error: %s\n", SDL_GetError());
		return (0);
	}

	g->window = SDL_CreateWindow("Maze Project", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, WINDOW_WIDTH, WINDOW_HEIGHT, SDL_WINDOW_SHOWN);
	if (g->window == NULL)
	{
		printf("Window could not be created! SDL_Error: %s\n", SDL_GetError());
		return (0);
	}

	g->renderer = SDL_CreateRenderer(g->window, -1, SDL_RENDERER_ACCELERATED);
	if (g->renderer == NULL)
	{
		printf("Renderer could not be created! SDL_Error: %s\n", SDL_GetError());
		return (0);
	}

	g->player.x = WINDOW_WIDTH / 2;
	g->player.y = WINDOW_HEIGHT / 2;
	g->player.angle = 0.0;

	return (1);
}

void close(Global *g)
{
	SDL_DestroyRenderer(g->renderer);
	SDL_DestroyWindow(g->window);
	g->window = NULL;
	g->renderer = NULL;

	SDL_Quit();
}

int main(int argc, char *args[])
{
	Global g;

	if (!init(&g))
	{
		printf("Failed to initialize!\n");
		return (1);
	}
	else
	{
		int quit = 0;
		SDL_Event e;

		while (!quit)
		{
			while (SDL_PollEvent(&e) != 0)
			{
				if (e.type == SDL_QUIT)
				{
					quit = 1;
				}
			}

			SDL_SetRenderDrawColor(g.renderer, 0xFF, 0xFF, 0xFF, 0xFF);
			SDL_RenderClear(g.renderer);

			performRaycasting(&g);

			SDL_RenderPresent(g.renderer);
		}
	}

	close(&g);
	return (0);
}

