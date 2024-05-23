#ifndef MAZE_H
#define MAZE_H

#include <SDL2/SDL.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>

#define WINDOW_WIDTH 800
#define WINDOW_HEIGHT 600
#define TILE_SIZE 64
#define MAP_WIDTH 24
#define MAP_HEIGHT 24
#define FOV_ANGLE (60 * (M_PI / 180))

typedef struct
{
	double x;
	double y;
	double angle;
} Player;

typedef struct
{
	SDL_Window *window;
	SDL_Renderer *renderer;
	Player player;
} Global;

int init(Global *g);
void close(Global *g);
void performRaycasting(Global *g, int worldMap[MAP_WIDTH][MAP_HEIGHT]);
void getWorldMap(int worldMap[MAP_WIDTH][MAP_HEIGHT]);

#endif /* MAZE_H */

