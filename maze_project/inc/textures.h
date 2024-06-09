#ifndef TEXTURES_H
#define TEXTURES_H

#include <SDL2/SDL.h>

void WallTexturesready();
SDL_Texture* loadTexture(const char* file);
void freeWallTextures();

#endif

