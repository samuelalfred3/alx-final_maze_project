#include <stdio.h>
#include <SDL2/SDL.h>

#define WINDOW_WIDTH 640
#define WINDOW_HEIGHT 480

int main(void)
{
	SDL_Init(SDL_INIT_VIDEO);
	
	SDL_Window *window = SDL_CreateWindow("Maze Project", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, WINDOW_WIDTH, WINDOW_HEIGHT, SDL_WINDOW_SHOWN);
	if (window == NULL)
	{
		printf("SDL Window creation failed: %s\n", SDL_GetError());
		return (1);
	}

	SDL_Renderer *renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
	SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
	SDL_RenderClear(renderer);

	SDL_RenderPresent(renderer);

	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);
	SDL_Quit();

	return (0);
}

