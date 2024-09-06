#include <SDL2/SDL.h>
#include <stdbool.h>
#include "../inc/game_config.h"   /* Include game configuration settings */
#include "../inc/graphics_utils.h" /* Include graphics-related functions and constants */

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
	if (!initWindow())
	{
		return (1); /* Exit if initialization failed */
	}

	/* Load wall textures */
	loadWallTextures();

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
		render_game(NULL, &player);
	}

	/* Clean up resources */
	freeWallTextures();
	SDL_DestroyWindow(window); /* Clean up SDL window */

	return (0);
}

