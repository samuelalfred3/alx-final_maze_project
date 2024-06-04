#include "textures.h"
#include <SDL_image.h>
#include "../inc/game.h"

static const char *textureFileNames[NUM_TEXTURES] = {
    "assets/textures/wall.png",
    "assets/textures/ground.png",
    "assets/textures/ceiling.png"
};

/**
 * load_textures - Loads textures into an array.
 * @renderer: The SDL_Renderer to use.
 * @textures: The array to store the loaded textures.
 * Return: 1 on success, 0 on failure.
 */
int load_textures(SDL_Renderer *renderer, SDL_Texture **textures)
{
	for (int i = 0; i < NUM_TEXTURES; i++)
	{
		/* Load texture from file */
		SDL_Surface *surface = IMG_Load(textureFileNames[i]);
		if (surface == NULL)
		{
			SDL_Log("Error loading texture %s: %s\n", textureFileNames[i], IMG_GetError());
			return (0);  /* Return 0 on failure */
		}

		/* Convert surface to texture */
		textures[i] = SDL_CreateTextureFromSurface(renderer, surface);
		if (textures[i] == NULL)
		{
			SDL_Log("Error creating texture from %s: %s\n", textureFileNames[i], SDL_GetError());
			SDL_FreeSurface(surface);
			return (0);  /* Return 0 on failure */
		}

		/* Free surface since texture is created */
		SDL_FreeSurface(surface);
	}

	return (1);  /* Return 1 on success */
}

void free_textures(SDL_Texture **textures)
{
	for (int i = 0; i < NUM_TEXTURES; i++)
	{
		SDL_DestroyTexture(textures[i]);
	}
}

