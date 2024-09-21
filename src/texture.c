#include "../inc/maze.h"

texture_t wallTextures[NUM_TEXTURES];

static const char *textureFileNames[NUM_TEXTURES] = {
	"./images/purple.png",
	"./images/redwall.png",
	"./images/mossystonewall.png",
	"./images/grassstone.png",
	"./images/colorstone.png",
	"./images/bluewall.png",
	"./images/woodtexture.png",
	"./images/Character.png",
};

/**
 * WallTexturesready - load textures in the respective position
 */
void WallTexturesready(void)
{
	int i;

	for (i = 0; i < NUM_TEXTURES; i++)
	{
		upng_t *upng;

		upng = upng_new_from_file(textureFileNames[i]);

		if (upng != NULL)
		{
			upng_decode(upng);
			if (upng_get_error(upng) == UPNG_EOK)
			{
				wallTextures[i].upngTexture = upng;
				wallTextures[i].width = upng_get_width(upng);
				wallTextures[i].height = upng_get_height(upng);
				wallTextures[i].texture_buffer = (color_t *)upng_get_buffer(upng);
			}
			else
			{
				fprintf(stderr, "Failed to load texture: %s\n", textureFileNames[i]);
			}
		}
		else
		{
			fprintf(stderr, "Failed to create texture from file: %s\n", textureFileNames[i]);
		}
	}
}

/**
 * freeWallTextures - free wall textures
 */

void freeWallTextures(void)
{
	int i;

	for (i = 0; i < NUM_TEXTURES; i++)
		upng_free(wallTextures[i].upngTexture);
}
