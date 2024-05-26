#include <SDL2/SDL.h>
#include "config.h"
#include "game.h"
#include "graphics.h"
#include "input.h"

/**
 * init_sdl - Initializes SDL and creates a window and renderer.
 * @window: Pointer to the SDL_Window pointer to be created.
 * @renderer: Pointer to the SDL_Renderer pointer to be created.
 *
 * Return: 0 on success, 1 on failure.
 */
int init_sdl(SDL_Window **window, SDL_Renderer **renderer)
{
	if (SDL_Init(SDL_INIT_VIDEO) != 0)
	{
		return (1);
	}

	*window = create_window();
	if (!*window)
	{
		SDL_Quit();
		return (1);
	}

	*renderer = create_renderer(*window);
	if (!*renderer)
	{
		SDL_DestroyWindow(*window);
		SDL_Quit();
		return (1);
	}

	return (0);
}

/**
 * game_loop - Main game loop to handle events and render the game.
 * @renderer: Pointer to the SDL_Renderer.
 * @state: Pointer to the game state.
 */
void game_loop(SDL_Renderer *renderer, GameState *state)
{
	SDL_Event e;
	int quit = 0;

	while (!quit)
	{
		while (SDL_PollEvent(&e))
		{
			if (e.type == SDL_QUIT)
			{
				quit = 1;
			}
			handle_input(&e, state);
		}

		update_game(state);

		SDL_RenderClear(renderer);
		render_game(renderer, state);
		SDL_RenderPresent(renderer);
	}
}

/**
 * main - Entry point of the program.
 *
 * Return: 0 on success, 1 on failure.
 */
int main(void)
{
	SDL_Window *window;
	SDL_Renderer *renderer;
	GameState state;

	if (init_sdl(&window, &renderer) != 0)
	{
		return (1);
	}

	init_game(&state);
	game_loop(renderer, &state);
	clean_up();

	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);
	SDL_Quit();

	return (0);
}

