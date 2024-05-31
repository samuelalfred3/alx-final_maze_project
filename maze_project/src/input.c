#include <SDL.h>
#include "input.h"

/* Handle keyboard input */
void handle_input(GameState *state, SDL_Event *event)
{
	if (event->type == SDL_KEYDOWN)
	{
		switch (event->key.keysym.sym)
		{
			case SDLK_w:
				state->moveForward = 1;
				break;
			case SDLK_s:
				state->moveBackward = 1;
				break;
			case SDLK_a:
				state->rotateLeft = 1;
				break;
			case SDLK_d:
				state->rotateRight = 1;
				break;
		}
	}
	else if (event->type == SDL_KEYUP)
	{
		switch (event->key.keysym.sym)
		{
			case SDLK_w:
				state->moveForward = 0;
				break;
			case SDLK_s:
				state->moveBackward = 0;
				break;
			case SDLK_a:
				state->rotateLeft = 0;
				break;
			case SDLK_d:
				state->rotateRight = 0;
				break;
		}
	}
}

