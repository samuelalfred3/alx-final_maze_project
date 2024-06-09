#ifndef GAME_H
#define GAME_H

#include <stdbool.h>

extern bool GameRunning;
extern int TicksLastFrame;

void setup_game(void);
void update_game(void);
void render_game(void);

#endif

