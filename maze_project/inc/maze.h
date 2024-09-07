#ifndef MAZE_H
#define MAZE_H

#include <SDL2/SDL.h>
#include <stdbool.h>

/* Window and screen dimensions */
#define WINDOW_WIDTH 800
#define WINDOW_HEIGHT 600

/* Map dimensions */
#define MAP_NUM_ROWS 10
#define MAP_NUM_COLS 10
#define TILE_SIZE 64

/* Player constants */
#define PLAYER_MOVE_SPEED 5
#define PLAYER_TURN_SPEED 0.05

/* Raycasting constants */
#define FOV (60 * (M_PI / 180))  /* Field of view in radians */+
#define NUM_RAYS WINDOW_WIDTH     /* One ray per column of the screen */

/* Color buffer to store pixel data */
extern uint32_t *colorBuffer;
extern SDL_Texture *colorBufferTexture;

/* Structure for player */
typedef struct {
    float x;
    float y;
    float width;
    float height;
    float turnDirection;  /* -1 for left, +1 for right */
    float walkDirection;  /* -1 for back, +1 for forward */
    float rotationAngle;
    float walkSpeed;
    float turnSpeed;
} Player;

/* Structure for a ray */
typedef struct {
    float rayAngle;
    float wallHitX;
    float wallHitY;
    float distance;
    int wasHitVertical;
    int isRayFacingUp;
    int isRayFacingDown;
    int isRayFacingLeft;
    int isRayFacingRight;
} Ray;

/* Texture structure */
typedef struct {
    SDL_Surface *surface;
    SDL_Texture *texture;
    int width;
    int height;
} Texture;

/* Function declarations */
void setup(void);
void update(void);
void render(void);
void handleInput(void);
void destroyWindow(void);
bool initializeWindow(void);
void clearColorBuffer(uint32_t color);
void renderColorBuffer(void);
void drawPixel(int x, int y, uint32_t color);
void drawLine(int x0, int y0, int x1, int y1, uint32_t color);
void loadTexture(void);
void WallTexturesready(void);
void freeWallTextures(void);
void castAllRays(void);
void castRay(float rayAngle, int stripId);
bool hasWallAt(float x, float y);
float normalizeAngle(float angle);
float distanceBetweenPoints(float x1, float y1, float x2, float y2);
int mapHasWallAt(float x, float y);
void renderMap(void);
void movePlayer(void);
void renderPlayer(void);
void processInput(void);

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
extern Texture wallTextures[4];

/* Map representation (hardcoded for now) */
extern int map[MAP_NUM_ROWS][MAP_NUM_COLS];

#endif /* MAZE_H */

