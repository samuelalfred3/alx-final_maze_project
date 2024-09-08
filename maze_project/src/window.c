#include "../inc/maze.h"
#include <SDL2/SDL.h>

SDL_Window *window = NULL;
SDL_Renderer *renderer = NULL;

/**
 * initSDL - Initializes SDL and creates a window and renderer.
 * Return: true if successful, false otherwise.
 */
bool initSDL(void)
{
	if (SDL_Init(SDL_INIT_VIDEO) < 0)
		return (false);

	window = SDL_CreateWindow("Maze Game",
			SDL_WINDOWPOS_CENTERED,
			SDL_WINDOWPOS_CENTERED,
			SCREEN_WIDTH, SCREEN_HEIGHT,
			SDL_WINDOW_SHOWN);
	if (!window)
	{
		SDL_Quit();
		return (false);
	}

	renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
	if (!renderer)
	{
		SDL_DestroyWindow(window);
		SDL_Quit();
		return (false);
	}

	return (true);
}

/**
 * clearScreen - Clears the screen with the background color.
 */
void clearScreen(void)
{
	SDL_SetRenderDrawColor(renderer, 0x00, 0x00, 0x00, 0xFF); /* Black */
	SDL_RenderClear(renderer);
}

/**
 * renderScreen - Updates the screen by presenting the renderer.
 */
void renderScreen(void)
{
	SDL_RenderPresent(renderer);
}

/**
 * closeWindow - Closes SDL, destroying the window and renderer.
 */
void closeWindow(void)
{
	if (renderer)
	{
		SDL_DestroyRenderer(renderer);
		renderer = NULL;
	}
	if (window)
	{
		SDL_DestroyWindow(window);
		window = NULL;
	}
	SDL_Quit();
}

