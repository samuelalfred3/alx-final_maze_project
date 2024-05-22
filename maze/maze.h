#ifndef MAZE_H
#define MAZE_H

#include <stdbool.h>
#include <SDL2/SDL.h>
#include <math.h>

#define WINDOW_WIDTH 640
#define WINDOW_HEIGHT 480
#define FOV_ANGLE (60 * M_PI / 180)
#define NUM_RAYS WINDOW_WIDTH
#define TILE_SIZE 64
#define MAP_WIDTH 24
#define MAP_HEIGHT 7

typedef struct
{
	float x;
	float y;
	float angle;
} Player;

typedef struct
{
	float distance;
	bool hit;
} RayHit;

typedef struct
{
	SDL_Window *window;
	SDL_Renderer *renderer;
	Player player;
} Global;

extern Global g;
extern int worldMap[MAP_WIDTH][MAP_HEIGHT];

/* Function prototypes */
int init(void);
void close(void);
void performRaycasting(void);
void drawWalls(Global *g, int worldMap[MAP_WIDTH][MAP_HEIGHT]);

#endif /* MAZE_H */

