#include <SDL2/SDL.h>
#include <stdbool.h>
#include "../inc/game.h"
#include "../inc/input.h"
#include "../inc/window.h"

bool isRunning = false;

/**
 * main - Entry point for the program.
 * @argc: The number of command-line arguments.
 * @argv: The array of command-line arguments.
 * Return: 0 on success, non-zero on failure.
 */
int main(int argc, char* argv[])
{
	isRunning = initializeWindow();
	setup_game();
	/* Ensure that WallTexturesready() is defined and included */
	WallTexturesready();

	while (isRunning)
	{
		handleInput(&isRunning);
		update_game();
		render_game();
	}

	/* Ensure that freeWallTextures() is defined and included */
	freeWallTextures();
	return (0);
}

