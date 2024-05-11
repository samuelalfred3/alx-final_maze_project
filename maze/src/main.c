#include <stdio.h>
#include <SDL2/SDL.h>

int main(void)
{
	SDL_Init(SDL_INIT_VIDEO);

	SDL_Window *window = SDL_CreateWindow("Maze Project",
			SDL_WINDOWPOS_UNDEFINED,
			SDL_WINDOWPOS_UNDEFINED,
			640, 480,
			SDL_WINDOW_SHOWN);

	if (window == NULL)
	{
		printf("SDL Window creation failed: %s\n", SDL_GetError());
		return (1);
	}

	SDL_Delay(3000);

	SDL_DestroyWindow(window);
	SDL_Quit();

	return (0);
}

