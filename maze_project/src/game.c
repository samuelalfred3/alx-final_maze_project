#include "../inc/game.h"
#include "../inc/graphics.h"
#include "../inc/map.h"
#include "../inc/ray.h"
#include "../inc/player.h"
#include "../inc/textures.h"
#include <SDL2/SDL.h>

/* External variables */
bool isRunning = true;
SDL_Renderer *renderer = NULL;
Player player;
int TicksLastFrame;

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

