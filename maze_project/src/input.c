#include <SDL2/SDL.h>
#include <stdbool.h>
#include "../inc/input.h"
#include "../inc/game.h"
#include "../inc/player.h"

/**
 * handleInput - Handles user input events.
 * @isRunning: Pointer to the game's running state.
 * @player: Pointer to the Player structure.
 */
void handleInput(bool *isRunning, Player *player)
{
	SDL_Event event;

	while (SDL_PollEvent(&event))
	{
		if (event.type == SDL_QUIT)
		{
			*isRunning = false;
		}
		if (event.type == SDL_KEYDOWN)
		{
			if (event.key.keysym.sym == SDLK_ESCAPE)
			{
				*isRunning = false;
			}
			if (event.key.keysym.sym == SDLK_w)
			{
				movePlayerForward(player);
			}
			if (event.key.keysym.sym == SDLK_s)
			{
				movePlayerBackward(player);
			}
			if (event.key.keysym.sym == SDLK_a)
			{
				movePlayerLeft(player);
			}
			if (event.key.keysym.sym == SDLK_d)
			{
				movePlayerRight(player);
			}
		}
	}
}

