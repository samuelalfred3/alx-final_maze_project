#include "../inc/maze.h"
#include <SDL2/SDL.h>
#include <stdbool.h>

/* Global variable for managing game state */
bool isRunning = true;
int ticksLastFrame;

/* Function declarations */
void setup_game(void);
void handleInput(bool *isRunning, Player *player);
void update_game(Player *player);
void renderPlayer(Player *player);
void render_game(Game *game, Player *player);
void destroy_game(Game *game);

/**
 * main - Entry point for the program.
 *
 * Return: 0 on success, non-zero on failure.
 */
int main(void)
{
	/* Initialize SDL and create the window */
	if (!initializeWindow())
	{
		return (1); /* Exit if initialization failed */
	}

	/* Set up the game environment */
	setup_game();

	/* Initialize player */
	Player player;
	initPlayer(&player);

	/* Initialize game state */
	Game game;
	game.window = SDL_CreateWindow("Maze Game", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
	if (!game.window)
	{
		return (1); /* Exit if window creation failed */
	}
	game.renderer = SDL_CreateRenderer(game.window, -1, SDL_RENDERER_ACCELERATED);
	if (!game.renderer)
	{
		SDL_DestroyWindow(game.window);
		return (1); /* Exit if renderer creation failed */
	}

	/* Main game loop */
	while (isRunning)
	{
		handleInput(&isRunning, &player);
		update_game(&player);
		render_game(&game, &player);
	}

	/* Clean up resources */
	destroy_game(&game); /* Pass the Game object here */

	return (0);
}

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

	WallTexturesready(); /* Set default colors for textures */
}

/**
 * update_game - update player movement and game state
 */
void update_game(Player *player)
{
	float deltaTime;
	int timeToWait = FRAME_TIME_LENGTH - (SDL_GetTicks() - ticksLastFrame);

	if (timeToWait > 0 && timeToWait <= FRAME_TIME_LENGTH)
	{
		SDL_Delay(timeToWait);
	}
	deltaTime = (SDL_GetTicks() - ticksLastFrame) / 1000.0f;

	ticksLastFrame = SDL_GetTicks();

	movePlayer(player, deltaTime);
	castRay(player->rotationAngle, 0);
}

/**
 * render_game - calls all functions needed for on-screen rendering
 */
void render_game(Game *game, Player *player)
{
	(void)game;

	clearColorBuffer(0xFF000000); /* Clear screen with black color */

	renderWall();
	renderMap();
	renderRays();
	renderPlayer(player);
	renderColorBuffer();
}

/**
 * destroy_game - free resources and clean up game state
 */
void destroy_game(Game *game)
{
	freeWallTextures();
	SDL_DestroyRenderer(game->renderer);
	SDL_DestroyWindow(game->window);
	SDL_Quit();
}

