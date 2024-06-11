#ifndef GAME_H
#define GAME_H

#include <stdbool.h>

void setup_game(void);
void update_game(void);
void render_game(void);
void destroy_game(void);
void WallTexturesready(void);
void freeWallTextures(void);

extern bool isRunning;

#endif /* GAME_H */

