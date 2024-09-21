#include "../inc/maze.h"

bool GameRunning = false;
int TicksLastFrame;
player_t player;
rain_t rain;
Game game;

/**
 * setup_game - initialize player variables and load wall textures
 */
void setup_game(void)
{
	player.x = SCREEN_WIDTH / 2;
	player.y = SCREEN_HEIGHT / 2;
	player.width = 1;
	player.height = 30;
	player.walkDirection = 0;
	player.walkSpeed = 100;
	player.turnDirection = 0;
	player.turnSpeed = 45 * (PI / 180);
	player.rotationAngle = PI / 2;

	WallTexturesready();
	initRain(&rain);
}

/**
 * update_game - Update delta time, ticks last frame,
 *               player movement, and ray casting.
 */
void update_game(void)
{
	float deltaTime;
	int timeToWait = FRAME_TIME_LENGTH - (SDL_GetTicks() - TicksLastFrame);

	if (timeToWait > 0 && timeToWait <= FRAME_TIME_LENGTH)
	{
		SDL_Delay(timeToWait);
	}

	deltaTime = (SDL_GetTicks() - TicksLastFrame) / 1000.0f;
	TicksLastFrame = SDL_GetTicks();

	movePlayer(deltaTime);
	castAllRays();
	updateRain(&rain, deltaTime);
}

/**
 * render_game - calls all functions needed for on-screen rendering
 */
void render_game(Game *game)
{
	clearColorBuffer(0xFF000000);
	renderRain(&rain, game->renderer);
	renderWall();
	renderMap();
	renderRays();
	renderPlayer();
	renderColorBuffer();
}

/**
 * destroy_game - free wall textures and destroy window
 */
void destroy_game(void)
{
	freeWallTextures();
	destroyWindow();
}

/**
 * main - main function
 * Return: 0
 */
int main(void)
{
	GameRunning = initializeWindow();

	if (!GameRunning)
	{
		return (1);
	}

	setup_game();

	while (GameRunning)
	{
		handleInput();
		update_game();
		render_game(&game);
	}

	destroy_game();
	return (0);
}

