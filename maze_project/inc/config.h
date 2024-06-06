#ifndef CONFIG_H
#define CONFIG_H

#define MAP_WIDTH 20
#define MAP_HEIGHT 13
#define SCREEN_WIDTH 640
#define SCREEN_HEIGHT 480

#include <SDL2/SDL.h>

typedef struct
{
	Uint8 r;
	Uint8 g;
	Uint8 b;
	Uint8 a;
} color_t;

/* Extern map declaration */
extern char map[MAP_HEIGHT][MAP_WIDTH + 1];

#endif /* CONFIG_H */

