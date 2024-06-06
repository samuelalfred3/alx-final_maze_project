#include <SDL.h>
#include <SDL_image.h>
#include "../inc/textures.h"
#include "../inc/config.h"

/**
 * load_textures - Load textures.
 * @renderer: Pointer to the SDL renderer.
 * @textures: Array of SDL_Texture pointers.
 * Return: 1 on success, 0 on failure.
 */
int load_textures(SDL_Renderer *renderer, SDL_Texture **textures)
{
	textures[0] = IMG_LoadTexture(renderer, "assets/textures/wall.png");
	textures[1] = IMG_LoadTexture(renderer, "assets/textures/ground.png");
	textures[2] = IMG_LoadTexture(renderer, "assets/textures/ceiling.png");

	for (int i = 0; i < NUM_TEXTURES; i++)
	{
		if (textures[i] == NULL)
		{
			SDL_Log("Failed to load texture %d: %s", i, IMG_GetError());
			return (0);
		}
	}
	return (1);
}

/**
 * free_textures - Free textures.
 * @textures: Array of SDL_Texture pointers.
 */
void free_textures(SDL_Texture **textures)
{
	for (int i = 0; i < NUM_TEXTURES; i++)
	{
		if (textures[i])
		{
			SDL_DestroyTexture(textures[i]);
		}
	}
}

