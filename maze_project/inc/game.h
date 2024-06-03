#ifndef GAME_H
#define GAME_H

#include <SDL.h>

/* Define the GameState structure */
typedef struct
{
	double playerPosX;
	double playerPosY;
	double playerDirX;
	double playerDirY;
	double planeX;
	double planeY;
	int moveForward;
	int moveBackward;
	int rotateLeft;
	int rotateRight;
} GameState;

/* Function prototypes */
void handle_input(GameState *state, SDL_Event *event);
void init_game(GameState *state);
void update_game(GameState *state);

#endif /* GAME_H */

