#include "../inc/graphics_utils.h"
#include "../inc/game_config.h"
#include <SDL2/SDL.h>

/**
 * processInput - Processes user input to update player state.
 */
void processInput(void)
{
	SDL_Event event;

	while (SDL_PollEvent(&event))
	{
		if (event.type == SDL_QUIT)
		{
			exitGame();
		}
		else if (event.type == SDL_KEYDOWN)
		{
			switch (event.key.keysym.sym)
			{
				case SDLK_UP:
					player.moveForward = true;
					break;
				case SDLK_DOWN:
					player.moveBackward = true;
					break;
				case SDLK_LEFT:
					player.turnLeft = true;
					break;
				case SDLK_RIGHT:
					player.turnRight = true;
					break;
			}
		}
		else if (event.type == SDL_KEYUP)
		{
			switch (event.key.keysym.sym)
			{
				case SDLK_UP:
					player.moveForward = false;
					break;
				case SDLK_DOWN:
					player.moveBackward = false;
					break;
				case SDLK_LEFT:
					player.turnLeft = false;
					break;
				case SDLK_RIGHT:
					player.turnRight = false;
					break;
			}
		}
	}
}

