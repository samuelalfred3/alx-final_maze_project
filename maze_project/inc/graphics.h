#ifndef GRAPHICS_H
#define GRAPHICS_H

#include <SDL2/SDL.h>
#include "game.h"

SDL_Window *create_window(void);
SDL_Renderer *create_renderer(SDL_Window *window);
void render_game(SDL_Renderer *renderer, GameState *state);
void draw_walls(SDL_Renderer *renderer, GameState *state);

#endif /* GRAPHICS_H */
