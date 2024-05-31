#ifndef GAME_H
#define GAME_H

#include <SDL.h>
#include "config.h"

typedef struct
{
	double playerPosX, playerPosY;   /* Player's position */
	double playerDirX, playerDirY;   /* Player's direction */
	double planeX, planeY;           /* Camera plane */
	int moveForward, moveBackward;   /* Movement flags */
	int rotateLeft, rotateRight;     /* Rotation flags */
} GameState;

void init_game(GameState *state);
void update_game(GameState *state);

#endif /* GAME_H */

