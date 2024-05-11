#include <stdio.h>
#include <stdbool.h>
#include <math.h>
#include <SDL2/SDL.h>

#define WINDOW_WIDTH 640
#define WINDOW_HEIGHT 480
#define FOV_ANGLE (60 * M_PI / 180)
#define NUM_RAYS WINDOW_WIDTH
#define TILE_SIZE 64

typedef struct {
	float x;
	float y;
	float angle;
} Player;

typedef struct {
	float distance;
	bool hit;
} RayHit;

SDL_Window *window = NULL;
SDL_Renderer *renderer = NULL;
Player player;

void init() {
	SDL_Init(SDL_INIT_VIDEO);
	window = SDL_CreateWindow("Raycasting Demo", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, WINDOW_WIDTH, WINDOW_HEIGHT, 0);
	renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
	player.x = WINDOW_WIDTH / 2;
	player.y = WINDOW_HEIGHT / 2;
	player.angle = 0;
}

void destroy() {
	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);
	SDL_Quit();
}

void draw_rect(int x, int y, int width, int height, Uint8 r, Uint8 g, Uint8 b) {
	SDL_Rect rect = { x, y, width, height };
	SDL_SetRenderDrawColor(renderer, r, g, b, SDL_ALPHA_OPAQUE);
	SDL_RenderFillRect(renderer, &rect);
}

void draw_ray(float ray_angle, RayHit ray_hit) {
	float angle_diff = ray_angle - player.angle;
	float distance_projection = WINDOW_WIDTH / (2 * tan(FOV_ANGLE / 2));
	float ray_height = TILE_SIZE * (distance_projection / ray_hit.distance);
	int wall_top = (WINDOW_HEIGHT - ray_height) / 2;
	int wall_bottom = wall_top + ray_height;
	int color = ray_hit.hit ? 0xFF : 0x88;
	draw_rect(NUM_RAYS * angle_diff / FOV_ANGLE, wall_top, 1, ray_height, color, color, color);
}

RayHit cast_ray(float ray_angle) {
	RayHit hit = { .distance = 0, .hit = false };
	hit.distance = 1000;
	return hit;
}

void update() {
	SDL_SetRenderDrawColor(renderer, 0, 0, 0, SDL_ALPHA_OPAQUE);
	SDL_RenderClear(renderer);
	for (int i = 0; i < NUM_RAYS; i++) {
		float ray_angle = player.angle - FOV_ANGLE / 2 + (FOV_ANGLE * i / NUM_RAYS);
		RayHit ray_hit = cast_ray(ray_angle);
		draw_ray(ray_angle, ray_hit);
	}
	SDL_RenderPresent(renderer);
}

int main() {
	bool running = true;
	SDL_Event event;
	init();
	while (running) {
		while (SDL_PollEvent(&event)) {
			if (event.type == SDL_QUIT) {
				running = false;
			}
			if (event.type == SDL_KEYDOWN) {
				switch (event.key.keysym.sym) {
					case SDLK_LEFT:
						player.angle -= M_PI / 30;
						break;
					case SDLK_RIGHT:
						player.angle += M_PI / 30;
						break;
				}
			}
		}
		update();
		SDL_Delay(16);
	}
	destroy();
	return 0;
}

