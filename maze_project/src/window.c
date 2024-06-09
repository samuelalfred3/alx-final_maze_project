#include "../inc/window.h"
#include <SDL2/SDL.h>

SDL_Window *window = NULL;
SDL_Renderer *renderer = NULL;

/**
 * initWindow - Initializes the SDL window and renderer.
 *
 * Return: true on success, false on failure.
 */
bool initWindow()
{
	if (SDL_Init(SDL_INIT_EVERYTHING) != 0)
	{
		fprintf(stderr, "Error initializing SDL: %s\n", SDL_GetError());
		return (false);
	}

	window = SDL_CreateWindow(
			"Maze Game",
			SDL_WINDOWPOS_CENTERED,
			SDL_WINDOWPOS_CENTERED,
			SCREEN_WIDTH,
			SCREEN_HEIGHT,
			SDL_WINDOW_SHOWN
			);

	if (!window)
	{
		fprintf(stderr, "Error creating SDL window: %s\n", SDL_GetError());
		return (false);
	}

	renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
	if (!renderer)
	{
		fprintf(stderr, "Error creating SDL renderer: %s\n", SDL_GetError());
		SDL_DestroyWindow(window);
		return (false);
	}

	return (true);
}

/**
 * cleanUpWindow - Cleans up the SDL window and renderer.
 */
void cleanUpWindow()
{
	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);
	SDL_Quit();
}

