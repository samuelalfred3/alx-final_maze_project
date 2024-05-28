#ifndef GRAPHICS_H
#define GRAPHICS_H

#include <SDL2/SDL.h>
#include "game.h"

#define NUM_TEXTURES 3

SDL_Window *create_window(void);
SDL_Renderer *create_renderer(SDL_Window *window);
void load_textures(SDL_Renderer *renderer, SDL_Texture **textures);
void render_game(SDL_Renderer *renderer, GameState *state, SDL_Texture **textures);
void draw_walls(SDL_Renderer *renderer, GameState *state, SDL_Texture *wallTexture);
void clean_up_textures(SDL_Texture **textures);

#endif /* GRAPHICS_H */

