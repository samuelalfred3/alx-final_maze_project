#ifndef GRAPHICS_UTILS_H
#define GRAPHICS_UTILS_H

#include <SDL2/SDL.h>
#include <stdbool.h>
#include <math.h> /* For M_PI */
#include "game_config.h" /* Included game_config.h for Ray struct */

/* Define constants for rendering */
#define MINIMAP_SCALE_FACTOR 0.2f
#define TILE_SIZE 64
#define SCREEN_WIDTH 800
#define SCREEN_HEIGHT 600

/* Function prototypes for rendering */
void drawLine(float x1, float y1, float x2, float y2, Uint32 color);

/* Function prototypes for raycasting */
float normalizeAngle(float angle);
float distanceBetweenPoints(float x1, float y1, float x2, float y2);
void castRay(float rayAngle, int stripId);
void castAllRays(void);
void renderRays(void);

#endif /* GRAPHICS_UTILS_H */

