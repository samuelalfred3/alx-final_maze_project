#include "../inc/input.h"
#include "../inc/game.h"

/**
 * handle_input - Handle user input and update game state accordingly.
 * @state: Pointer to the game state.
 * @event: Pointer to the SDL event.
 */
void handle_input(GameState *state, SDL_Event *event)
{
	while (SDL_PollEvent(event))
	{
		if (event->type == SDL_QUIT)
		{
			state->moveForward = 0;
			state->moveBackward = 0;
			state->rotateLeft = 0;
			state->rotateRight = 0;
		}
		else if (event->type == SDL_KEYDOWN)
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
				default:
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
				default:
					break;
			}
		}
	}
}

