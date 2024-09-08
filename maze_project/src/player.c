#include "../inc/maze.h"
#include <SDL2/SDL_image.h>
#include <math.h>

static SDL_Texture *playerTexture;

/**
 * initPlayer - Initializes the player and loads the texture.
 * @player: Pointer to the Player structure.
 */
void initPlayer(Player *player)
{
	SDL_Surface *surface = IMG_Load("images/character.png");

	if (!surface)
	{
		fprintf(stderr, "Error loading player texture: %s\n", IMG_GetError());
		exit(EXIT_FAILURE);
	}

	playerTexture = SDL_CreateTextureFromSurface(renderer, surface);
	SDL_FreeSurface(surface);

	if (!playerTexture)
	{
		fprintf(stderr, "Error creating player texture: %s\n", SDL_GetError());
		exit(EXIT_FAILURE);
	}

	/* Initialize player properties */
	player->x = SCREEN_WIDTH / 2;
	player->y = SCREEN_HEIGHT / 2;
	player->width = 32;
	player->height = 32;
	player->rotationAngle = 0;
	player->walkSpeed = 200.0;
	player->turnSpeed = 90.0 * (M_PI / 180); /* Convert degrees to radians */
}

/**
 * handlePlayerInput - Handles player input for movement.
 * @player: Pointer to the Player structure.
 */
void handlePlayerInput(Player *player)
{
	SDL_Event event;

	while (SDL_PollEvent(&event))
	{
		if (event.type == SDL_QUIT)
		{
			isGameRunning = false;
		}
		if (event.type == SDL_KEYDOWN)
		{
			switch (event.key.keysym.sym)
			{
				case SDLK_ESCAPE:
					isGameRunning = false;
					break;
				case SDLK_UP:
					player->walkDirection = +1;
					break;
				case SDLK_DOWN:
					player->walkDirection = -1;
					break;
				case SDLK_LEFT:
					player->turnDirection = -1;
					break;
				case SDLK_RIGHT:
					player->turnDirection = +1;
					break;
			}
		}
		else if (event.type == SDL_KEYUP)
		{
			switch (event.key.keysym.sym)
			{
				case SDLK_UP:
				case SDLK_DOWN:
					player->walkDirection = 0;
					break;
				case SDLK_LEFT:
				case SDLK_RIGHT:
					player->turnDirection = 0;
					break;
			}
		}
	}
}

/**
 * movePlayer - Updates player position based on input and time.
 * @player: Pointer to the Player structure.
 * @deltaTime: Time elapsed since the last update.
 */
void movePlayer(Player *player, float deltaTime)
{
	/* Update rotation */
	player->rotationAngle += player->turnDirection * player->turnSpeed * deltaTime;

	/* Keep rotation between 0 and 2*PI */
	if (player->rotationAngle < 0)
		player->rotationAngle += 2 * M_PI;
	else if (player->rotationAngle > 2 * M_PI)
		player->rotationAngle -= 2 * M_PI;

    /* Calculate step for movement */
	float moveStep = player->walkDirection * player->walkSpeed * deltaTime;

	/* Calculate new player position */
	float newPlayerX = player->x + cos(player->rotationAngle) * moveStep;
	float newPlayerY = player->y + sin(player->rotationAngle) * moveStep;

	/* Check for collision before updating position */
	if (!DetectCollision(newPlayerX, newPlayerY))
	{
		player->x = newPlayerX;
		player->y = newPlayerY;
	}
}

/**
 * renderPlayer - Renders the player on the screen.
 * @player: Pointer to the Player structure.
 */
void renderPlayer(Player *player)
{
	SDL_Rect playerRect = {
		.x = (int)(player->x - player->width / 2),
		.y = (int)(player->y - player->height / 2),
		.w = player->width,
		.h = player->height
	};

	SDL_RenderCopyEx(renderer, playerTexture, NULL, &playerRect,
			player->rotationAngle * (180.0 / M_PI), NULL, SDL_FLIP_NONE);
}

/**
 * cleanUpPlayer - Cleans up resources associated with the player.
 */
void cleanUpPlayer(void)
{
	SDL_DestroyTexture(playerTexture);
}
