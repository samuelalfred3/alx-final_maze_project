#include "../inc/input.h"
#include "../inc/game.h"
#include "../inc/player.h"
#include <SDL2/SDL.h>

/**
 * handleInput - Handles user input events.
 * @isRunning: Pointer to the game's running state.
 */
void handleInput(bool *isRunning)
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
				movePlayerForward();
			}
			if (event.key.keysym.sym == SDLK_s)
			{
				movePlayerBackward();
			}
			if (event.key.keysym.sym == SDLK_a)
			{
				movePlayerLeft();
			}
			if (event.key.keysym.sym == SDLK_d)
			{
				movePlayerRight();
			}
		}
	}
}

