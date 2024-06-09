#include "../inc/config.h"
#include "../inc/game.h"
#include "../inc/graphics.h"
#include "../inc/player.h"
#include "../inc/ray.h"
#include "../inc/input.h"
#include "../inc/map.h"

Player player;

/**
 * setup_game - Initialize the game setup.
 */
void setup_game(void) {
	player.x = SCREEN_WIDTH / 2;
	player.y = SCREEN_HEIGHT / 2;
	player.width = 32;
	player.height = 32;
	player.walkDirection = 0;
	player.walkSpeed = 100;
	player.turnDirection = 0;
	player.turnSpeed = 45 * (PI / 180);
	player.rotationAngle = PI / 2;

    /* Initialize player */
	initPlayer(&player);
}

/**
 * update_game - Update game state.
 */
void update_game(void) {
	int timeToWait = FRAME_TIME_LENGTH - (SDL_GetTicks() - TicksLastFrame);

	if (timeToWait > 0 && timeToWait <= FRAME_TIME_LENGTH) {
		SDL_Delay(timeToWait);
	}

	float DeltaTime = (SDL_GetTicks() - TicksLastFrame) / 1000.0f;

	TicksLastFrame = SDL_GetTicks();

	handlePlayerInput(&player);
	movePlayer(&player, DeltaTime);
	castAllRays();
}

/**
 * render_game - Render the game.
 */
void render_game(void) {
	clearColorBuffer(0xFF000000);
	renderMap();
	renderRays();
	renderPlayer();
	renderColorBuffer();
}

