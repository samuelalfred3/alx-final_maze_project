#include "../inc/game.h"
#include "../inc/ray.h"
#include "../inc/player.h"
#include "../inc/input.h"
#include "../inc/window.h"
#include "../inc/graphics.h"
#include "../inc/map.h"
#include "../inc/config.h"
#include "../inc/textures.h"
#include <SDL2/SDL_image.h>

#define NUM_WALL_TEXTURES 4

extern SDL_Texture* wallTextures[NUM_WALL_TEXTURES];

/* External variables */
bool isRunning = true;
Player player;
int TicksLastFrame;
SDL_Renderer* renderer;

/**
 * setup_game - Initialize the game setup.
 */
void setup_game(void)
{
	player.x = SCREEN_WIDTH / 2;
	player.y = SCREEN_HEIGHT / 2;
	player.width = 32;
	player.height = 32;
	player.walkDirection = 0;
	player.walkSpeed = 100;
	player.turnDirection = 0;
	player.turnSpeed = 45 * (PI / 180);
	player.rotationAngle = PI / 2;

	initPlayer(&player);
}

/**
 * update_game - Update game state.
 */
void update_game(void)
{
	int timeToWait = FRAME_TIME_LENGTH - (SDL_GetTicks() - TicksLastFrame);

	if (timeToWait > 0 && timeToWait <= FRAME_TIME_LENGTH)
	{
		SDL_Delay(timeToWait);
	}

	float deltaTime = (SDL_GetTicks() - TicksLastFrame) / 1000.0f;
	TicksLastFrame = SDL_GetTicks();

	handlePlayerInput(&player);
	movePlayer(&player, deltaTime);
	castAllRays();
}

/**
 * render_game - Render the game.
 */
void render_game(void)
{
	clearColorBuffer(0xFF000000);
	renderMap();
	renderRays();
	renderPlayer(&player);
	renderColorBuffer();
}

/**
 * destroy_game - Cleanup and free resources.
 */
void destroy_game(void)
{
	freeWallTextures();
}

/**
 * freeWallTextures - Free wall textures.
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

/**
 * WallTexturesready - Load wall textures.
 */
void WallTexturesready(void)
{
	const char* textureFiles[NUM_WALL_TEXTURES] = {
		"path/to/wall_texture1.png",
		"path/to/wall_texture2.png",
		"path/to/wall_texture3.png",
		"path/to/wall_texture4.png"
	};

	for (int i = 0; i < NUM_WALL_TEXTURES; i++)
	{
		SDL_Surface* surface = IMG_Load(textureFiles[i]);
		if (!surface)
		{
			printf("Failed to load texture %s: %s\n", textureFiles[i], IMG_GetError());
			continue;
		}
		wallTextures[i] = SDL_CreateTextureFromSurface(renderer, surface);
		SDL_FreeSurface(surface);

		if (!wallTextures[i])
		{
			printf("Failed to create texture from %s: %s\n", textureFiles[i], SDL_GetError());
		}
	}
}

