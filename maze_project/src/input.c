#include "input.h"
#include "game.h"
#include "config.h"

void handle_input(SDL_Event *event, GameState *state)
{
	if (event->type == SDL_KEYDOWN)
	{
		switch (event->key.keysym.sym)
		{
			case SDLK_LEFT:
				state->player_angle -= ROT_SPEED;
				break;
			case SDLK_RIGHT:
				state->player_angle += ROT_SPEED;
				break;
			case SDLK_UP:
				state->playerPosX += state->playerDirX * MOVE_SPEED;
				state->playerPosY += state->playerDirY * MOVE_SPEED;
				break;
			case SDLK_DOWN:
				state->playerPosX -= state->playerDirX * MOVE_SPEED;
				state->playerPosY -= state->playerDirY * MOVE_SPEED;
				break;
			case SDLK_a:
				state->playerPosX -= state->planeX * MOVE_SPEED;
				state->playerPosY -= state->planeY * MOVE_SPEED;
				break;
			case SDLK_d:
				state->playerPosX += state->planeX * MOVE_SPEED;
				state->playerPosY += state->planeY * MOVE_SPEED;
				break;
		}
	}
}

