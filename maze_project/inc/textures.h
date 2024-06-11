#ifndef TEXTURES_H
#define TEXTURES_H

#include <SDL2/SDL.h>

#define NUM_WALL_TEXTURES 4

extern SDL_Texture* wallTextures[NUM_WALL_TEXTURES];

void WallTexturesready(void);
void freeWallTextures(void);
SDL_Texture* loadTexture(const char *file);

#endif /* TEXTURES_H */

