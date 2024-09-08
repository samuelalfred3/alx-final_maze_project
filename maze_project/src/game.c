#include "../inc/maze.h"

/**
 * initializeGame - Initializes the game and SDL components.
 * @game: Pointer to the game structure.
 */
void initialize_game(Game *game)
{
	if (SDL_Init(SDL_INIT_VIDEO) != 0)
	{
		fprintf(stderr, "Error initializing SDL: %s\n", SDL_GetError());
		game->is_running = false;
		return;
	}

	game->window = SDL_CreateWindow("3D Maze Game",
			SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
			SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
	if (!game->window)
	{
		fprintf(stderr, "Error creating SDL window: %s\n", SDL_GetError());
		game->is_running = false;
		return;
	}

	game->renderer = SDL_CreateRenderer(game->window, -1, 0);
	if (!game->renderer)
	{
		fprintf(stderr, "Error creating SDL renderer: %s\n", SDL_GetError());
		game->is_running = false;
		return;
	}

	game->is_running = true;

	/* Initialize player */
	player.x = SCREEN_WIDTH / 2;
	player.y = SCREEN_HEIGHT / 2;
	player.width = 10;
	player.height = 10;
	player.rotationAngle = 0;
	player.walkDirection = 0;
	player.turnDirection = 0;
	player.move_speed = PLAYER_MOVE_SPEED;
	player.rotation_speed = PLAYER_TURN_SPEED;
}

/**
 * processInput - Handles player input for movement.
 * @game: Pointer to the game structure.
 */
void process_input(Game *game)
{
	SDL_Event event;

	while (SDL_PollEvent(&event))
	{
		if (event.type == SDL_QUIT)
			game->is_running = false;
		else if (event.type == SDL_KEYDOWN)
		{
			if (event.key.keysym.sym == SDLK_ESCAPE)
				game->is_running = false;
			else if (event.key.keysym.sym == SDLK_UP)
				player.walkDirection = 1;
			else if (event.key.keysym.sym == SDLK_DOWN)
				player.walkDirection = -1;
			else if (event.key.keysym.sym == SDLK_RIGHT) 
				player.turnDirection = 1;
			else if (event.key.keysym.sym == SDLK_LEFT)
				player.turnDirection = -1;
		}
		else if (event.type == SDL_KEYUP)
		{
			if (event.key.keysym.sym == SDLK_UP || event.key.keysym.sym == SDLK_DOWN)
				player.walkDirection = 0;
			if (event.key.keysym.sym == SDLK_RIGHT || event.key.keysym.sym == SDLK_LEFT)
				player.turnDirection = 0;
		}
	}
}

/**
 * renderGame - Renders the player and game components.
 * @game: Pointer to the game structure.
 * @player: Pointer to the player structure.
 */
void render_game(Game *game, Player *player) {
	SDL_SetRenderDrawColor(game->renderer, 0, 0, 0, 255); /* Clear screen */
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

void destroy_game(Game *game) {
	SDL_DestroyRenderer(game->renderer);
	SDL_DestroyWindow(game->window);
	SDL_Quit();
}

