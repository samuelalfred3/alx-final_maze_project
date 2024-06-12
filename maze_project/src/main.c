#include <SDL2/SDL.h>
#include <stdbool.h>
#include "../inc/game.h"
#include "../inc/input.h"
#include "../inc/graphics.h"
#include "../inc/window.h"
#include "../inc/player.h"
#include "../inc/textures.h"

bool isRunning = false;

/**
 * main - Entry point for the program.
 * @argc: The number of command-line arguments.
 * @argv: The array of command-line arguments.
 *
 * Return: 0 on success, non-zero on failure.
 */
int main(int argc, char* argv[])
{
	isRunning = initWindow();

	setup_game();
	WallTexturesready();

	Player player;
	initPlayer(&player);

	while (isRunning)
	{
		handleInput(&isRunning, &player);
		update_game();
		render_game();
	}

	freeWallTextures();
	destroyWindow();

	return (0);
}

