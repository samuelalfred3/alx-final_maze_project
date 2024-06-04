#ifndef GRAPHICS_H
#define GRAPHICS_H

#include <SDL.h>
#include "game.h"

#define SCREEN_WIDTH 640
#define SCREEN_HEIGHT 480

/* Function prototypes for graphics */
SDL_Window *create_window(void);
SDL_Renderer *create_renderer(SDL_Window *window);
int load_textures(SDL_Renderer *renderer, SDL_Texture **textures);
void render_game(SDL_Renderer *renderer, GameState *state, SDL_Texture **textures);
void draw_walls(SDL_Renderer *renderer, GameState *state, SDL_Texture *wallTexture);
void draw_floor_and_ceiling(SDL_Renderer *renderer, SDL_Texture *groundTexture, SDL_Texture *ceilingTexture);
void clean_up_textures(SDL_Texture **textures);

#endif /* GRAPHICS_H */

