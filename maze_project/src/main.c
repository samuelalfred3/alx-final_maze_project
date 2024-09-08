#include "../inc/maze.h"
#include <SDL2/SDL.h>
#include <stdbool.h>

/* Global variable for managing game state */
bool isRunning = true;

/**
 * main - Entry point for the program.
 *
 * Return: 0 on success, non-zero on failure.
 */
int main(void)
{
	/* Initialize SDL and create the window */
	if (!initializeWindow())
	{
		return (1); /* Exit if initialization failed */
	}

	/* Set up the game environment */
	setup_game();

	/* Initialize player */
	Player player;
	initPlayer(&player);

	/* Main game loop */
	while (isRunning)
	{
		handleInput(&isRunning, &player);
		update_game(NULL, &player);
		renderPlayer(&player);
	}

	/* Clean up resources */
	SDL_DestroyWindow(window); /* Clean up SDL window */

	return (0);
}

