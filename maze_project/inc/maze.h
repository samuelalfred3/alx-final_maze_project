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
#define FRAME_TIME_LENGTH 16

/* Number of wall textures */
#define NUM_WALL_TEXTURES 4

#define PI 3.14159265358979323846

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

/* Function declarations */
void initialize_game(Game *game);
void process_input(Game *game);
void render_game(Game *game, Player *player);
void destroy_game(Game *game);
bool initializeWindow(void);
void destroyWindow(void);
void clearColorBuffer(uint32_t color);
void renderColorBuffer(void);
void processInput(void);
bool isInsideMap(float x, float y);
bool DetectCollision(float x, float y);
int getMapValue(int row, int col);
void initPlayer(Player *player);
void handlePlayerInput(Player *player);
void movePlayer(Player *player, float deltaTime);
void renderPlayer(Player *player);
void cleanUpPlayer(void);
float normalizeAngle(float angle);
float distanceBetweenPoints(float x1, float y1, float x2, float y2);
void castRay(float rayAngle, int stripId);
void drawPixel(int x, int y, color_t color);
void drawLine(int x0, int y0, int x1, int y1, color_t color);
void WallTexturesready(void);
void drawWall(int x, int y, int wallType);
bool initSDL(void);
void clearScreen(void);
void renderScreen(void);
void renderWall(void);
void renderRays(void);
void closeWindow(void);
void renderMap(void);
void freeWallTextures(void);

#endif /* MAZE_H */

