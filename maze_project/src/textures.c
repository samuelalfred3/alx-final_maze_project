#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include "../inc/textures.h"

SDL_Texture* wallTextures[NUM_WALL_TEXTURES];

/**
 * WallTexturesready - Loads wall textures into the wallTextures array.
 */
void WallTexturesready()
{
	wallTextures[0] = loadTexture("images/wall.png");
	wallTextures[1] = loadTexture("images/ground.png");
	wallTextures[2] = loadTexture("images/ceiling.png");
	wallTextures[3] = loadTexture("images/character.png");
}

/**
 * loadTexture - Loads an image file as an SDL texture.
 * @file: Path to the image file.
 *
 * Return: Pointer to the SDL texture, or NULL on failure.
 */
SDL_Texture* loadTexture(const char* file)
{
	SDL_Surface* surface = IMG_Load(file);
	if (!surface)
	{
		fprintf(stderr, "Error creating SDL surface: %s\n", SDL_GetError());
		return (NULL);
	}
	SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, surface);
	SDL_FreeSurface(surface);
	if (!texture)
	{
		fprintf(stderr, "Error creating SDL texture: %s\n", SDL_GetError());
	}
	return (texture);
}

/**
 * freeWallTextures - Frees all loaded wall textures.
 */
void freeWallTextures()
{
	for (int i = 0; i < NUM_WALL_TEXTURES; i++)
	{
		if (wallTextures[i])
		{
			SDL_DestroyTexture(wallTextures[i]);
			wallTextures[i] = NULL;
		}
	}
}

