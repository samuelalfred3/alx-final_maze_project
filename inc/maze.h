#ifndef MAZE_H
#define MAZE_H

#include <SDL2/SDL.h>
#include <stdint.h>
#include <math.h>
#include <limits.h>
#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <time.h>
#include "upng.h"

/* Window and screen dimensions */
#define SCREEN_WIDTH (MAP_NUM_COLS * TILE_SIZE)
#define SCREEN_HEIGHT (MAP_NUM_ROWS * TILE_SIZE)

/* Map dimensions */
#define PI 3.14159265
#define TWO_PI 6.28318530
#define TILE_SIZE 64
#define MINIMAP_SCALE_FACTOR 0.25
#define MAP_NUM_ROWS 13
#define MAP_NUM_COLS 20
#define NUM_TEXTURES 8

/* Raycasting constants */
#define FOV_ANGLE (60 * (PI / 180))
#define NUM_RAYS SCREEN_WIDTH
#define PROJ_PLANE ((SCREEN_WIDTH / 2) / tan(FOV_ANGLE / 2))
#define FPS 30
#define FRAME_TIME_LENGTH (1000 / FPS)

/* Rain constants */
#define RAIN_DROP_COUNT 100
#define RAIN_DROP_LENGTH 10
#define RAIN_DROP_COLOR 0x00BFFF
#define RAIN_SPEED_MIN 50
#define RAIN_SPEED_MAX 100

/* Type definitions */
typedef uint32_t color_t;  /* Define a type for colors */

/* Game state management */
extern bool GameRunning;
void handleInput(void);

/* Game structure */
typedef struct game_s
{
	SDL_Window *window;
	SDL_Renderer *renderer;
} Game;

/* Rendering functions */
bool initializeWindow(void);
void destroyWindow(void);
void clearColorBuffer(color_t color);
void render_game(Game *game);
void renderColorBuffer(void);
void drawPixel(int x, int y, color_t color);
void drawRect(int x, int y, int width, int height, color_t color);
void drawLine(int x0, int y0, int x1, int y1, color_t color);

/* Struct for individual raindrop particles */
typedef struct particle_s
{
	int x;
	int y;
	float speed;
} particle_t;

/* Struct for rain effect */
typedef struct rain_s
{
	particle_t particles[RAIN_DROP_COUNT];
	bool enabled;
} rain_t;

/* Function declarations */
void initRain(rain_t *rain);
void updateRain(rain_t *rain, float deltaTime);
void renderRain(rain_t *rain, SDL_Renderer *renderer);

extern rain_t rain;

/* Map functions */
bool DetectCollision(float x, float y);
bool isInsideMap(float x, float y);
void renderMap(void);
int getMapValue(int row, int col);

/* Texture structures and functions */
typedef struct texture_s
{
	int width;                /* Texture width */
	int height;               /* Texture height */
	color_t *texture_buffer;  /* Pointer to texture buffer */
	upng_t *upngTexture;      /* Pointer to uPNG texture */
} texture_t;

extern texture_t wallTextures[NUM_TEXTURES]; /* Array of wall textures */

void WallTexturesready(void);
void freeWallTextures(void);

/* Wall rendering functions */
void renderWall(void);

/* Player structure and functions */
typedef struct player_s
{
	float x;               /* Player's x coordinate */
	float y;               /* Player's y coordinate */
	float width;           /* Player's width */
	float height;          /* Player's height */
	int turnDirection;     /* Direction to turn */
	int walkDirection;     /* Direction to walk */
	float rotationAngle;   /* Player's rotation angle */
	float walkSpeed;       /* Player's walking speed */
	float turnSpeed;       /* Player's turning speed */
} player_t;

extern player_t player;  /* Player instance */

void movePlayer(float deltaTime);
void renderPlayer(void);

/* Raycasting structures and functions */
typedef struct ray_s
{
	float rayAngle;        /* Angle of the ray */
	float wallHitX;       /* X coordinate of wall hit */
	float wallHitY;       /* Y coordinate of wall hit */
	float distance;        /* Distance to the wall */
	bool wasHitVertical;   /* Whether the hit was vertical */
	int wallHitContent;    /* Content of the wall hit */
} ray_t;

extern ray_t rays[NUM_RAYS];  /* Array of rays */
float distanceBetweenPoints(float x1, float y1, float x2, float y2);
bool isRayFacingUp(float angle);
bool isRayFacingDown(float angle);
bool isRayFacingLeft(float angle);
bool isRayFacingRight(float angle);
void castAllRays(void);
void castRay(float rayAngle, int stripId);
void renderRays(void);
void horzIntersection(float rayAngle);
void vertIntersection(float rayAngle);

#endif /* MAZE_H */

