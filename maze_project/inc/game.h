#ifndef GAME_H
#define GAME_H

typedef struct
{
	double playerPosX;
	double playerPosY;
	double playerDirX;
	double playerDirY;
	double planeX;
	double planeY;
	double player_angle;
} GameState;

void init_game(GameState *state);
void update_game(GameState *state);
void clean_up(void);

#endif /* GAME_H */

