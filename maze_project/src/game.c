#include "../inc/game.h"
#include "../inc/config.h"
#include <math.h>
#include "../inc/map.h"

/**
 * init_game - Initialize game state.
 * @state: Pointer to the game state structure.
 */
void init_game(GameState *state)
{
	state->playerPosX = 2.0;
	state->playerPosY = 2.0;
	state->playerDirX = -1.0;
	state->playerDirY = 0.0;
	state->planeX = 0.0;
	state->planeY = 0.66;
	state->moveForward = 0;
	state->moveBackward = 0;
	state->rotateLeft = 0;
	state->rotateRight = 0;
}

/**
 * update_game - Update game state based on input.
 * @state: Pointer to the game state structure.
 */
void update_game(GameState *state)
{
	double moveSpeed = 0.05;
	double rotSpeed = 0.05;

	if (state->moveForward)
	{
		if (get_map_value((int)(state->playerPosX + state->playerDirX * moveSpeed), (int)state->playerPosY) == '0')
			state->playerPosX += state->playerDirX * moveSpeed;
		if (get_map_value((int)state->playerPosX, (int)(state->playerPosY + state->playerDirY * moveSpeed)) == '0')
			state->playerPosY += state->playerDirY * moveSpeed;
	}
	if (state->moveBackward)
	{
		if (get_map_value((int)(state->playerPosX - state->playerDirX * moveSpeed), (int)state->playerPosY) == '0')
			state->playerPosX -= state->playerDirX * moveSpeed;
		if (get_map_value((int)state->playerPosX, (int)(state->playerPosY - state->playerDirY * moveSpeed)) == '0')
			state->playerPosY -= state->playerDirY * moveSpeed;
	}
	if (state->rotateLeft)
	{
		double oldDirX = state->playerDirX;
		state->playerDirX = state->playerDirX * cos(-rotSpeed) - state->playerDirY * sin(-rotSpeed);
		state->playerDirY = oldDirX * sin(-rotSpeed) + state->playerDirY * cos(-rotSpeed);
		double oldPlaneX = state->planeX;
		state->planeX = state->planeX * cos(-rotSpeed) - state->planeY * sin(-rotSpeed);
		state->planeY = oldPlaneX * sin(-rotSpeed) + state->planeY * cos(-rotSpeed);
	}
	if (state->rotateRight)
	{
		double oldDirX = state->playerDirX;
		state->playerDirX = state->playerDirX * cos(rotSpeed) - state->playerDirY * sin(rotSpeed);
		state->playerDirY = oldDirX * sin(rotSpeed) + state->playerDirY * cos(rotSpeed);
		double oldPlaneX = state->planeX;
		state->planeX = state->planeX * cos(rotSpeed) - state->planeY * sin(rotSpeed);
		state->planeY = oldPlaneX * sin(rotSpeed) + state->planeY * cos(rotSpeed);
	}
}

