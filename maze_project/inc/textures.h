#ifndef TEXTURES_H
#define TEXTURES_H

#include <SDL.h>

#define NUM_TEXTURES 3

typedef struct
{
	SDL_Texture *texture;
	int width;
	int height;
} Texture;

int load_textures(SDL_Renderer *renderer, SDL_Texture **textures);
void free_textures(SDL_Texture **textures);

#endif /* TEXTURES_H */
