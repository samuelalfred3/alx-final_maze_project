#include <SDL.h>
#include <SDL_image.h>
#include "../inc/game.h"
#include "../inc/window.h"
#include "../inc/config.h"
#include "../inc/graphics.h"
#include "../inc/textures.h"
#include "../inc/map.h"

int main(int argc, char *argv[])
{
	GameState state;
	SDL_Texture *textures[NUM_TEXTURES];

	if (!initializeWindow())
	{
		fprintf(stderr, "Failed to initialize window.\n");
		return (1);
	}

	init_game(&state);

	/* Load textures */
	textures[0] = load_texture(renderer, "assets/textures/wall.png");
	if (!textures[0])
	{
		fprintf(stderr, "Failed to load wall texture\n");
		destroyWindow();
		return (1);
	}
	textures[1] = load_texture(renderer, "assets/textures/floor.png");
	if (!textures[1])
	{
		fprintf(stderr, "Failed to load floor texture\n");
		destroyWindow();
		return (1);
	}
	textures[2] = load_texture(renderer, "assets/textures/ceiling.png");
	if (!textures[2])
	{
		fprintf(stderr, "Failed to load ceiling texture\n");
		destroyWindow();
		return (1);
	}

	SDL_Event e;
	int quit = 0;

	while (!quit)
	{
		while (SDL_PollEvent(&e) != 0)
		{
			if (e.type == SDL_QUIT)
			{
				quit = 1;
			} else if (e.type == SDL_KEYDOWN) {
				switch (e.key.keysym.sym) {
					case SDLK_w:
						state.moveForward = 1;
						break;
					case SDLK_s:
						state.moveBackward = 1;
						break;
					case SDLK_a:
						state.rotateLeft = 1;
						break;
					case SDLK_d:
						state.rotateRight = 1;
						break;
				}
			} else if (e.type == SDL_KEYUP) {
				switch (e.key.keysym.sym) {
					case SDLK_w:
						state.moveForward = 0;
						break;
					case SDLK_s:
						state.moveBackward = 0;
						break;
					case SDLK_a:
						state.rotateLeft = 0;
						break;
					case SDLK_d:
						state.rotateRight = 0;
						break;
				}
			}
		}

		update_game(&state);
		render_game(renderer, &state, textures);
	}

	destroyWindow();
	return (0);
}

