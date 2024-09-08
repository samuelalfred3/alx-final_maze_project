#ifndef MAZE_H
#define MAZE_H

#include <SDL2/SDL.h>
#include <stdbool.h>
#include <stdint.h>
#include <string.h>
#include <math.h>

/* Window and screen dimensions */
#define SCREEN_WIDTH 800
#define SCREEN_HEIGHT 600

/* Map dimensions */
#define MAP_NUM_ROWS 20
#define MAP_NUM_COLS 20
#define TILE_SIZE 32
#define MAP_WIDTH (MAP_NUM_COLS * TILE_SIZE)
#define MAP_HEIGHT (MAP_NUM_ROWS * TILE_SIZE)

/* Player constants */
#define PLAYER_MOVE_SPEED 5
#define PLAYER_TURN_SPEED 0.05

/* Raycasting constants */
#define FOV (60 * (M_PI / 180))  /* Field of view in radians */
#define NUM_RAYS SCREEN_WIDTH     /* One ray per column of the screen */

/* Number of wall textures */
#define NUM_WALL_TEXTURES 4

#define PI 3.141592653589793

/* Color buffer to store pixel data */
extern uint32_t *colorBuffer;
extern SDL_Texture *colorBufferTexture;

/* Structure for player */
typedef struct
{
	float x;
	float y;
	float width;
	float height;
	float turnDirection;  /* -1 for left, +1 for right */
	float walkDirection;  /* -1 for back, +1 for forward */
	float rotationAngle;
	float walkSpeed;
	float turnSpeed;
	float move_speed;
	float rotation_speed;
	bool moveForward;
	bool moveBackward;
	bool turnLeft;
	bool turnRight;
} Player;

/* Structure for game */
typedef struct
{
	SDL_Window *window;
	SDL_Renderer *renderer;
	bool is_running;
} Game;

/* Structure for a ray */
typedef struct
{
	float rayAngle;
	float wallHitX;
	float wallHitY;
	float distance;
	int wasHitVertical;
	int isRayFacingUp;
	int isRayFacingDown;
	int isRayFacingLeft;
	int isRayFacingRight;
	int wallHitContent;
} Ray;

/* Texture structure */
typedef struct
{
	SDL_Surface *surface;
	SDL_Texture *texture;
	int width;
	int height;
} Texture;

typedef uint32_t color_t;

/* Function declarations */
void setup(void);
void update(void);
void render(void);
void handleInput(bool *isRunning, Player *player);
void destroyWindow(void);
bool initializeWindow(void);
void clearColorBuffer(uint32_t color);
void renderColorBuffer(void);
void drawPixel(int x, int y, uint32_t color);
void drawLine(int x0, int y0, int x1, int y1, uint32_t color);
void WallTexturesready(void);
void drawWall(int x, int y, int wallType);
void castAllRays(void);
void castRay(float rayAngle, int stripId);
bool hasWallAt(float x, float y);
float normalizeAngle(float angle);
float distanceBetweenPoints(float x1, float y1, float x2, float y2);
int mapHasWallAt(float x, float y);
bool isInsideMap(float x, float y);
bool DetectCollision(float x, float y);
int getMapValue(int row, int col);
void renderMap(void);
void movePlayer(Player *player, float deltaTime);
void processInput(void);
void exitGame(void);
void setup_game(void);
void initPlayer(Player *player);
void update_game(void *param, Player *player);
void renderPlayer(Player *player);

/* Map functions */
int getMapValue(int row, int col);
void drawRect(int x, int y, int width, int height, uint32_t color);
void drawMapGrid(void);

/* SDL-related variables */
extern SDL_Window *window;
extern SDL_Renderer *renderer;
extern SDL_Event event;
extern int isGameRunning;

/* Player instance */
extern Player player;

/* Rays array */
extern Ray rays[NUM_RAYS];

/* Wall texture array */
extern Texture wallTextures[NUM_WALL_TEXTURES];
extern color_t wallColors[4];

/* Map representation (hardcoded for now) */
extern const int map[MAP_NUM_ROWS][MAP_NUM_COLS];

#endif /* MAZE_H */

