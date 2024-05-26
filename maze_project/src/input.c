#include "input.h"
#include "game.h"
#include "config.h"

/**
 * handle_input - Handles keyboard input.
 * @event: Pointer to the SDL event.
 * @state: Pointer to the game state.
 */
void handle_input(SDL_Event *event, GameState *state)
{
	if (event->type == SDL_KEYDOWN)
	{
		switch (event->key.keysym.sym)
		{
			case SDLK_LEFT:
				/* Rotate player to the left */
				state->player_angle -= ROT_SPEED;
				break;
			case SDLK_RIGHT:
				/* Rotate player to the right */
				state->player_angle += ROT_SPEED;
				break;
			case SDLK_UP:
				/* Move player forward */
				state->playerPosX += state->playerDirX * MOVE_SPEED;
				state->playerPosY += state->playerDirY * MOVE_SPEED;
				break;
			case SDLK_DOWN:
				/* Move player backward */
				state->playerPosX -= state->playerDirX * MOVE_SPEED;
				state->playerPosY -= state->playerDirY * MOVE_SPEED;
				break;
			case SDLK_a:
				/* Move player left */
				state->playerPosX -= state->planeX * MOVE_SPEED;
				state->playerPosY -= state->planeY * MOVE_SPEED;
				break;
			case SDLK_d:
				/* Move player right */
				state->playerPosX += state->planeX * MOVE_SPEED;
				state->playerPosY += state->planeY * MOVE_SPEED;
				break;
		}
	}
}

