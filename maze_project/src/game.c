#include "game.h"
#include "config.h"

/**
 * init_game - Initializes the game state.
 * @state: Pointer to the game state.
 */
void init_game(GameState *state)
{
	state->playerPosX = 5.0;
	state->playerPosY = 5.0;
	state->playerDirX = -1.0;
	state->playerDirY = 0.0;
	state->planeX = 0.0;
	state->planeY = 0.66;
	state->player_angle = 0.0;
}

/**
 * update_game - Updates the game state.
 * @state: Pointer to the game state.
 */
void update_game(GameState *state)
{
	state->playerDirX = cos(state->player_angle);
	state->playerDirY = sin(state->player_angle);
	state->planeX = -0.66 * state->playerDirY;
	state->planeY = 0.66 * state->playerDirX;
}

/**
 * clean_up - Cleans up the game resources.
 */
void clean_up(void)
{
	/* Placeholder for any future clean-up logic */
}

