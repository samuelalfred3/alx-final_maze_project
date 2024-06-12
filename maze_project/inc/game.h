#ifndef GAME_H
#define GAME_H

#include <SDL2/SDL.h>
#include <stdbool.h>
#include "player.h"

/* External variables */
extern bool isRunning;
extern SDL_Renderer *renderer;
extern Player player;
extern int TicksLastFrame;

/* Function prototypes */
void setup_game(void);
void render_game(void);
void update_game(void);
void destroy_game(void);

#endif /* GAME_H */

