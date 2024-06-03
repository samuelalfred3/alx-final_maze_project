#include <SDL.h>
#include <SDL_image.h>
#include "../inc/game.h"
#include "../inc/graphics.h"
#include "../inc/config.h"
#include "../inc/input.h"
#include "../inc/textures.h"

int main(int argc, char *argv[])
{
	(void)argc;
	(void)argv;

	if (SDL_Init(SDL_INIT_VIDEO) < 0)
	{
		SDL_Log("Failed to initialize SDL: %s", SDL_GetError());
		return (1);
	}

	/* Initialize SDL_image with PNG support */
	if (IMG_Init(IMG_INIT_PNG) == 0)
	{
		SDL_Log("Failed to initialize SDL_image: %s", IMG_GetError());
		SDL_Quit();
		return (1);
	}

	SDL_Window *window = create_window();
	SDL_Renderer *renderer = create_renderer(window);

	GameState state;
	init_game(&state);

	SDL_Texture * textures[NUM_TEXTURES];
	if (!load_textures(renderer, textures))
	{
		SDL_Log("Failed to load textures");
		SDL_DestroyRenderer(renderer);
		SDL_DestroyWindow(window);
		IMG_Quit();
		SDL_Quit();
		return (1);
	}

	int running = 1;
	while (running)
	{
		SDL_Event event;
		while (SDL_PollEvent(&event))
		{
			if (event.type == SDL_QUIT)
			{
				running = 0;
			}
			handle_input(&state, &event);
		}

		update_game(&state);
		render_game(renderer, &state, textures);
	}

	free_textures(textures);
	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);

	IMG_Quit();
	SDL_Quit();

	return (0);
}

