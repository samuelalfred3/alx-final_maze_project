#include "../inc/maze.h"

/**
 * handleKeyDown - process input when a key is pressed
 * @event: the SDL event containing key press information
 *
 * This function adjusts the player's walk and turn direction based
 * on the key pressed (WASD or arrow keys) and exits the game
 * when the ESC key is pressed.
 */
void handleKeyDown(SDL_Event event)
{
	switch (event.key.keysym.sym)
	{
		case SDLK_ESCAPE:
			GameRunning = false;
			break;
		case SDLK_UP:
		case SDLK_w:
			player.walkDirection = +1;
			break;
		case SDLK_DOWN:
		case SDLK_s:
			player.walkDirection = -1;
			break;
		case SDLK_RIGHT:
		case SDLK_d:
			player.turnDirection = +1;
			break;
		case SDLK_LEFT:
		case SDLK_a:
			player.turnDirection = -1;
			break;
	}
}

/**
 * handleKeyUp - process input when a key is released
 * @event: the SDL event containing key release information
 *
 * This function resets the player's walk and turn direction
 * to zero when the key (WASD or arrow keys) is released.
 */
void handleKeyUp(SDL_Event event)
{
	switch (event.key.keysym.sym)
	{
		case SDLK_UP:
		case SDLK_DOWN:
		case SDLK_w:
		case SDLK_s:
			player.walkDirection = 0;
			break;
		case SDLK_LEFT:
		case SDLK_RIGHT:
		case SDLK_a:
		case SDLK_d:
			player.turnDirection = 0;
			break;
	}
}

/**
 * handleInput - process input from the keyboard
 *
 * This function processes input by polling SDL events.
 * It handles quitting the game, key presses, and key releases.
 */
void handleInput(void)
{
	SDL_Event event;

	while (SDL_PollEvent(&event))
	{
		if (event.type == SDL_QUIT)
		{
			GameRunning = false;
		}
		else if (event.type == SDL_KEYDOWN)
		{
			handleKeyDown(event);
		}
		else if (event.type == SDL_KEYUP)
		{
			handleKeyUp(event);
		}
	}
}

