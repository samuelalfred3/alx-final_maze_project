#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include "graphics.h"
#include "game.h"

/* Global texture variables */
SDL_Texture *wallTexture = NULL;
SDL_Texture *groundTexture = NULL;
SDL_Texture *ceilingTexture = NULL;
SDL_Texture *characterTexture = NULL;
SDL_Texture *pistolTexture = NULL;
SDL_Texture *rifleTexture = NULL;

SDL_Window *create_window(void)
{
	return SDL_CreateWindow("Maze Game", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
}

SDL_Renderer *create_renderer(SDL_Window *window)
{
	return SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
}

void load_textures(SDL_Renderer *renderer)
{
	wallTexture = IMG_LoadTexture(renderer, "assets/textures/wall.png");
	groundTexture = IMG_LoadTexture(renderer, "assets/textures/ground.png");
	ceilingTexture = IMG_LoadTexture(renderer, "assets/textures/ceiling.png");
	characterTexture = IMG_LoadTexture(renderer, "assets/character/character.png");
	pistolTexture = IMG_LoadTexture(renderer, "assets/weapons/pistol.png");
	rifleTexture = IMG_LoadTexture(renderer, "assets/weapons/rifle.png");

	if (!wallTexture || !groundTexture || !ceilingTexture || !characterTexture || !pistolTexture || !rifleTexture)
	{
		SDL_Log("Failed to load textures: %s", SDL_GetError());
	}
}

void render_game(SDL_Renderer *renderer, GameState *state)
{
	/* Clear screen */
	SDL_RenderClear(renderer);

	/* Draw the scene */
	draw_walls(renderer, state);
	draw_floor_and_ceiling(renderer, state);
	draw_character(renderer, state);
	draw_weapons(renderer, state);

	/* Present the back buffer */
	SDL_RenderPresent(renderer);
}

void draw_walls(SDL_Renderer *renderer, GameState *state)
{
	/* Raycasting logic and wall rendering */
	/* Example rendering */
	SDL_Rect wallRect = { 100, 100, 50, 50 };
	SDL_RenderCopy(renderer, wallTexture, NULL, &wallRect);
}

void draw_floor_and_ceiling(SDL_Renderer *renderer, GameState *state)
{
	/* Example rendering */
	SDL_Rect groundRect = { 0, SCREEN_HEIGHT / 2, SCREEN_WIDTH, SCREEN_HEIGHT / 2 };
	SDL_RenderCopy(renderer, groundTexture, NULL, &groundRect);

	SDL_Rect ceilingRect = { 0, 0, SCREEN_WIDTH, SCREEN_HEIGHT / 2 };
	SDL_RenderCopy(renderer, ceilingTexture, NULL, &ceilingRect);
}

void draw_character(SDL_Renderer *renderer, GameState *state)
{
	/* Example rendering */
	SDL_Rect characterRect = { (int)state->playerPosX, (int)state->playerPosY, 32, 32 };
	SDL_RenderCopy(renderer, characterTexture, NULL, &characterRect);
}

void draw_weapons(SDL_Renderer *renderer, GameState *state)
{
	/* Example rendering */
	SDL_Rect pistolRect = { SCREEN_WIDTH - 100, SCREEN_HEIGHT - 100, 64, 64 };
	SDL_RenderCopy(renderer, pistolTexture, NULL, &pistolRect);
}

void clean_up_textures(void)
{
	SDL_DestroyTexture(wallTexture);
	SDL_DestroyTexture(groundTexture);
	SDL_DestroyTexture(ceilingTexture);
	SDL_DestroyTexture(characterTexture);
	SDL_DestroyTexture(pistolTexture);
	SDL_DestroyTexture(rifleTexture);
}

