#ifndef INPUT_H
#define INPUT_H

#include <SDL2/SDL.h>
#include "game.h"

/* Function prototype for handling input */
void handle_input(SDL_Event *event, GameState *state);

#endif /* INPUT_H */

