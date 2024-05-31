#include <SDL.h>
#include <SDL_image.h>
#include "game.h"
#include "graphics.h"
#include "input.h"
#include "config.h"

int main(int argc, char *argv[])
{
	SDL_Init(SDL_INIT_VIDEO);

	/* Initialize SDL_image with PNG support */
	if (IMG_Init(IMG_INIT_PNG) == 0)
	{
		SDL_Log("Failed to initialize SDL_image: %s", IMG_GetError());
		return (1);
	}

	SDL_Window *window = create_window();
	SDL_Renderer *renderer = create_renderer(window);

	GameState state;
	init_game(&state);

	SDL_Texture *textures[NUM_TEXTURES];
	load_textures(renderer, textures);

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

	clean_up_textures(textures);
	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);

	IMG_Quit();
	SDL_Quit();

	return (0);
}

