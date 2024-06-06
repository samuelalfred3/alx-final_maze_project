#include "../inc/weapons.h"
#include <SDL_image.h>
#include "../inc/game.h"

static const char *weaponFileNames[NUM_WEAPONS] = {
	"assets/weapons/pistol.png",
	"assets/weapons/rifle.png"
};

void loadWeapons(Weapon *weapons, SDL_Renderer *renderer)
{
	for (int i = 0; i < NUM_WEAPONS; i++)
	{
		/* Load weapon texture from file */
		SDL_Surface *surface = IMG_Load(weaponFileNames[i]);
		if (surface == NULL)
		{
			fprintf(stderr, "Error loading weapon texture %s: %s\n", weaponFileNames[i], IMG_GetError());
			continue;
		}
		/* Convert surface to texture */
		weapons[i].texture = SDL_CreateTextureFromSurface(renderer, surface);
		if (weapons[i].texture == NULL)
		{
			fprintf(stderr, "Error creating texture from %s: %s\n", weaponFileNames[i], SDL_GetError());
			SDL_FreeSurface(surface);
			continue;
		}
		/* Get texture dimensions */
		weapons[i].width = surface->w;
		weapons[i].height = surface->h;
		/* Free surface since texture is created */
		SDL_FreeSurface(surface);
	}
}

void freeWeapons(Weapon *weapons)
{
	for (int i = 0; i < NUM_WEAPONS; i++)
	{
		if (weapons[i].texture != NULL) {
			SDL_DestroyTexture(weapons[i].texture);
			weapons[i].texture = NULL;
		}
	}
}

