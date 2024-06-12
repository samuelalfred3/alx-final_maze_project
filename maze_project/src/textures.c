#include "../inc/textures.h"
#include "../inc/graphics.h"
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

extern SDL_Renderer *renderer;

SDL_Texture* wallTextures[NUM_WALL_TEXTURES];

/**
 * WallTexturesready - Loads wall textures into the wallTextures array.
 */
void WallTexturesready(void)
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
SDL_Texture* loadTexture(const char* filePath)
{
	SDL_Surface* surface = IMG_Load(filePath);
	if (!surface)
	{
		fprintf(stderr, "Error loading texture: %s\n", IMG_GetError());
		return (NULL);
	}
	SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, surface);
	SDL_FreeSurface(surface);
	return texture;
}

/**
 * freeWallTextures - Frees all loaded wall textures.
 */
void freeWallTextures(void)
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

