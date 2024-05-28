#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include "config.h"
#include "game.h"
#include "graphics.h"
#include "input.h"

int main(void)
{
	if (SDL_Init(SDL_INIT_VIDEO) != 0)
	{
		SDL_Log("Unable to initialize SDL: %s", SDL_GetError());
		return (1);
	}

	SDL_Window *window = create_window();
	if (!window)
	{
		SDL_Log("Failed to create window: %s", SDL_GetError());
		SDL_Quit();
		return (1);
	}

	SDL_Renderer *renderer = create_renderer(window);
	if (!renderer)
	{
		SDL_Log("Failed to create renderer: %s", SDL_GetError());
		SDL_DestroyWindow(window);
		SDL_Quit();
		return (1);
	}

	if (IMG_Init(IMG_INIT_PNG) == 0)
	{
		SDL_Log("Failed to initialize SDL_image: %s", SDL_GetError());
		SDL_DestroyRenderer(renderer);
		SDL_DestroyWindow(window);
		SDL_Quit();
		return (1);
	}

	GameState state;
	init_game(&state);

	SDL_Texture *textures[NUM_TEXTURES];
	load_textures(renderer, textures);

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
			handle_input(&e, &state);
		}

		update_game(&state);

		SDL_RenderClear(renderer);
		render_game(renderer, &state, textures);
		SDL_RenderPresent(renderer);
	}

	clean_up_textures(textures);
	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);
	IMG_Quit();
	SDL_Quit();

	return (0);
}

