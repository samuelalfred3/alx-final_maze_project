#ifndef MAZE_H
#define MAZE_H

#include <SDL2/SDL.h>
#include <stdint.h>
#include <math.h>
#include <limits.h>
#include <stdio.h>
#include <stdbool.h>

/* Window and screen dimensions */
#define SCREEN_WIDTH (MAP_NUM_COLS * TILE_SIZE)
#define SCREEN_HEIGHT (MAP_NUM_ROWS * TILE_SIZE)

/* Map dimensions */
#define PI 3.14159265
#define MAP_NUM_ROWS 13
#define MAP_NUM_COLS 20
#define TWO_PI 6.28318530
#define TILE_SIZE 64
#define MINIMAP_SCALE_FACTOR 0.25

/* Raycasting constants */
#define FOV_ANGLE (60 * (PI / 180))
#define NUM_RAYS SCREEN_WIDTH
#define PROJ_PLANE ((SCREEN_WIDTH / 2) / tan(FOV_ANGLE / 2))
#define FPS 30
#define FRAME_TIME_LENGTH (1000 / FPS)

/* Number of wall textures */
#define NUM_TEXTURES 8

/* Structure for player */
typedef struct player_s
{
    float x;
    float y;
    float width;
    float height;
    int turnDirection;
    int walkDirection;
    float rotationAngle;
    float walkSpeed;
    float turnSpeed;
} player_t;

extern player_t player;

/* Structure for rays */
typedef struct ray_s
{
    float rayAngle;
    float wallHitX;
    float wallHitY;
    float distance;
    bool wasHitVertical;
    int wallHitContent;
} ray_t;

extern ray_t rays[NUM_RAYS];

/* Structure for textures */
typedef struct texture_s
{
    int width;
    int height;
    color_t *texture_buffer;
    upng_t *upngTexture;
} texture_t;

extern texture_t wallTextures[NUM_TEXTURES];

/* UPNG functionality */
typedef enum upng_error
{
    UPNG_EOK            = 0,
    UPNG_ENOMEM         = 1,
    UPNG_ENOTFOUND      = 2,
    UPNG_ENOTPNG        = 3,
    UPNG_EMALFORMED     = 4,
    UPNG_EUNSUPPORTED   = 5,
    UPNG_EUNINTERLACED  = 6,
    UPNG_EUNFORMAT      = 7,
    UPNG_EPARAM         = 8
} upng_error;

typedef enum upng_format
{
	UPNG_BADFORMAT,
	UPNG_RGB8,
	UPNG_RGB16,
	UPNG_RGBA8,
	UPNG_RGBA16,
	UPNG_LUMINANCE1,
	UPNG_LUMINANCE2,
	UPNG_LUMINANCE4,
	UPNG_LUMINANCE8,
	UPNG_LUMINANCE_ALPHA1,
	UPNG_LUMINANCE_ALPHA2,
	UPNG_LUMINANCE_ALPHA4,
	UPNG_LUMINANCE_ALPHA8
} upng_format;

typedef struct upng_t upng_t;

upng_t *upng_new_from_bytes(const unsigned char *buffer, unsigned long size);
upng_t *upng_new_from_file(const char *path);
void upng_free(upng_t *upng);
upng_error upng_header(upng_t *upng);
upng_error upng_decode(upng_t *upng);
upng_error upng_get_error(const upng_t *upng);
unsigned int upng_get_error_line(const upng_t *upng);
unsigned int upng_get_width(const upng_t *upng);
unsigned int upng_get_height(const upng_t *upng);
unsigned int upng_get_bpp(const upng_t *upng);
unsigned int upng_get_bitdepth(const upng_t *upng);
unsigned int upng_get_components(const upng_t *upng);
unsigned int upng_get_pixelsize(const upng_t *upng);
upng_format upng_get_format(const upng_t *upng);
const unsigned char *upng_get_buffer(const upng_t *upng);
unsigned int upng_get_size(const upng_t *upng);

typedef uint32_t color_t;

/**** FUNCTIONS ****/
void handleInput(void);
extern bool GameRunning;
void WallTexturesready(void);                                   void freeWallTextures(void);
void renderWall(void);
bool initializeWindow(void);
void destroyWindow(void);
void clearColorBuffer(color_t color);
void render_game(void);
void renderColorBuffer(void);
void drawPixel(int x, int y, color_t color);
void drawRect(int x, int y, int width, int height, color_t color);
void drawLine(int x0, int y0, int x1, int y1, color_t color);
bool DetectCollision(float x, float y);
bool isInsideMap(float x, float y);
void renderMap(void);
int getMapValue(int row, int col);
void movePlayer(float DeltaTime);
void renderPlayer(void);
float distanceBetweenPoints(float x1, float y1, float x2, float y2);
bool isRayFacingUp(float angle);
bool isRayFacingDown(float angle);
bool isRayFacingLeft(float angle);
bool isRayFacingRight(float angle);
void castAllRays(void);
void castRay(float rayAngle, int stripId);
void renderRays(void);

#endif /* MAZE_H */

