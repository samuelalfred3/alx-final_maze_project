#include "../inc/game_config.h"
#include "../inc/graphics_utils.h"
#include <math.h>
#include <stdio.h>

/* Global variables for game state */
static Player player;

void initialize_game(Game* game) {
	if (SDL_Init(SDL_INIT_VIDEO) != 0) {
		printf("Error initializing SDL: %s\n", SDL_GetError());
		game->is_running = false;
		return;
	}

	game->window = SDL_CreateWindow(
			"3D Maze Game",
			SDL_WINDOWPOS_CENTERED,
			SDL_WINDOWPOS_CENTERED,
			WINDOW_WIDTH,
			WINDOW_HEIGHT,
			SDL_WINDOW_SHOWN
			);

	if (!game->window) {
		printf("Error creating SDL window: %s\n", SDL_GetError());
		game->is_running = false;
		return;
	}

	game->renderer = SDL_CreateRenderer(game->window, -1, 0);
	if (!game->renderer) {
		printf("Error creating SDL renderer: %s\n", SDL_GetError());
		game->is_running = false;
		return;
	}

	game->is_running = true;

	/* Initialize player */
	player.x = WINDOW_WIDTH / 2;
	player.y = WINDOW_HEIGHT / 2;
	player.width = 10;
	player.height = 10;
	player.rotation_angle = 0;
	player.walk_direction = 0;
	player.turn_direction = 0;
	player.move_speed = PLAYER_SPEED;
	player.rotation_speed = PLAYER_ROTATION_SPEED;
}

void process_input(Game* game) {
	SDL_Event event;
	SDL_PollEvent(&event);

	switch (event.type) {
		case SDL_QUIT:
			game->is_running = false;
			break;
		case SDL_KEYDOWN:
			if (event.key.keysym.sym == SDLK_ESCAPE) {
				game->is_running = false;
			}
			if (event.key.keysym.sym == SDLK_UP) {
				player.walk_direction = 1;
			}
			if (event.key.keysym.sym == SDLK_DOWN) {
				player.walk_direction = -1;
			}
			if (event.key.keysym.sym == SDLK_RIGHT) {
				player.turn_direction = 1;
			}
			if (event.key.keysym.sym == SDLK_LEFT) {
				player.turn_direction = -1;
			}
			break;
		case SDL_KEYUP:
			if (event.key.keysym.sym == SDLK_UP || event.key.keysym.sym == SDLK_DOWN) {
				player.walk_direction = 0;
			}
			if (event.key.keysym.sym == SDLK_RIGHT || event.key.keysym.sym == SDLK_LEFT) {
				player.turn_direction = 0;
			}
			break;
	}
}

void render_game(Game* game, Player* player) {
	SDL_SetRenderDrawColor(game->renderer, 0, 0, 0, 255); /* Black background */
	SDL_RenderClear(game->renderer);

	/* Render player */
	SDL_Rect player_rect = {
		(int)player->x,
		(int)player->y,
		(int)player->width,
		(int)player->height
	};

	SDL_SetRenderDrawColor(game->renderer, 255, 255, 255, 255); /* White player */
	SDL_RenderFillRect(game->renderer, &player_rect);

	SDL_RenderPresent(game->renderer);
}

void destroy_game(Game* game) {
	SDL_DestroyRenderer(game->renderer);
	SDL_DestroyWindow(game->window);
	SDL_Quit();
}

