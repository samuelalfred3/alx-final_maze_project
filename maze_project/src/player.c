#include "../inc/player.h"
#include "../inc/map.h"
#include "../inc/input.h"
#include "../inc/graphics.h"
#include "../inc/config.h"
#include <SDL2/SDL_image.h>
#include <math.h>

extern bool isRunning;

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
			isRunning = false;
		}
		if (event.type == SDL_KEYDOWN)
		{
			if (event.key.keysym.sym == SDLK_ESCAPE)
			{
				isRunning = false;
			}
			if (event.key.keysym.sym == SDLK_UP)
			{
				player->walkDirection = +1;
			}
			if (event.key.keysym.sym == SDLK_DOWN)
			{
				player->walkDirection = -1;
			}
			if (event.key.keysym.sym == SDLK_RIGHT)
			{
				player->turnDirection = +1;
			}
			if (event.key.keysym.sym == SDLK_LEFT)
			{
				player->turnDirection = -1;
			}
		}
		if (event.type == SDL_KEYUP)
		{
			if (event.key.keysym.sym == SDLK_UP || event.key.keysym.sym == SDLK_DOWN)
			{
				player->walkDirection = 0;
			}
			if (event.key.keysym.sym == SDLK_RIGHT || event.key.keysym.sym == SDLK_LEFT)
			{
				player->turnDirection = 0;
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
	player->rotationAngle += player->turnDirection * player->turnSpeed * deltaTime;
	float moveStep = player->walkDirection * player->walkSpeed * deltaTime;

	float newPlayerX = player->x + cos(player->rotationAngle) * moveStep;
	float newPlayerY = player->y + sin(player->rotationAngle) * moveStep;

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
		.x = player->x - player->width / 2,
		.y = player->y - player->height / 2,
		.w = player->width,
		.h = player->height
	};

	SDL_RenderCopyEx(renderer, playerTexture, NULL, &playerRect, player->rotationAngle * (180.0 / PI), NULL, SDL_FLIP_NONE);
}

/**
 * cleanUpPlayer - Cleans up resources associated with the player.
 */
void cleanUpPlayer(void)
{
	SDL_DestroyTexture(playerTexture);
}

/**
 * movePlayerForward - Move the player forward.
 * @player: Pointer to the Player structure.
 */
void movePlayerForward(Player *player)
{
	player->x += cos(player->rotationAngle) * player->walkSpeed;
	player->y += sin(player->rotationAngle) * player->walkSpeed;
}

/**
 * movePlayerBackward - Move the player backward.
 * @player: Pointer to the Player structure.
 */
void movePlayerBackward(Player *player)
{
	player->x -= cos(player->rotationAngle) * player->walkSpeed;
	player->y -= sin(player->rotationAngle) * player->walkSpeed;
}

/**
 * movePlayerLeft - Move the player left.
 * @player: Pointer to the Player structure.
 */
void movePlayerLeft(Player *player)
{
	player->x -= cos(player->rotationAngle + PI / 2) * player->walkSpeed;
	player->y -= sin(player->rotationAngle + PI / 2) * player->walkSpeed;
}

/**
 * movePlayerRight - Move the player right.
 * @player: Pointer to the Player structure.
 */
void movePlayerRight(Player *player)
{
	player->x += cos(player->rotationAngle + PI / 2) * player->walkSpeed;
	player->y += sin(player->rotationAngle + PI / 2) * player->walkSpeed;
}

