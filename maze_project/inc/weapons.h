#ifndef WEAPONS_H
#define WEAPONS_H

#include <SDL.h>

#define NUM_WEAPONS 2

typedef struct
{
	SDL_Texture *texture;
	int width;
	int height;
} Weapon;

void loadWeapons(Weapon *weapons, SDL_Renderer *renderer);
void freeWeapons(Weapon *weapons);

#endif /* WEAPONS_H */

