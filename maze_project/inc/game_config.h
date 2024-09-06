#ifndef GAME_CONFIG_H
#define GAME_CONFIG_H

#include <SDL2/SDL.h>
#include <stdbool.h>
#include <math.h> /* For M_PI */

/* Window dimensions */
#define WINDOW_WIDTH 1024
#define WINDOW_HEIGHT 768

/* Player settings */
#define PLAYER_SPEED 0.05f
#define PLAYER_ROTATION_SPEED 0.03f

/* Map settings */
#define TILE_SIZE 64
#define MAP_NUM_ROWS 13
#define MAP_NUM_COLS 20

/* Field of view for raycasting */
#define FOV_ANGLE (60 * (M_PI / 180)) /* 60 degrees in radians */
#define NUM_RAYS WINDOW_WIDTH          /* One ray per column */

/* Raycasting settings */
#define MAX_DEPTH 30.0f

/* Texture settings */
#define TEXTURE_WIDTH 64
#define TEXTURE_HEIGHT 64

/* Game colors */
#define COLOR_RED 0xFF0000FF
#define COLOR_GREEN 0x00FF00FF
#define COLOR_BLUE 0x0000FFFF
#define COLOR_WHITE 0xFFFFFFFF
#define COLOR_BLACK 0x000000FF

/* Structs for player, ray, etc. */
typedef struct
{
	float x;
	float y;
	float width;
	float height;
	float rotation_angle;
	float walk_direction;
	float turn_direction;
	float move_speed;
	float rotation_speed;
} Player;

typedef struct
{
	float ray_angle;
	float wall_hit_x;
	float wall_hit_y;
	float distance;
	bool was_hit_vertical;
	int texture_offset_x;
} Ray;

typedef struct
{
	SDL_Window *window;
	SDL_Renderer *renderer;
	bool is_running;
} Game;

void initialize_game(Game *game);
void process_input(Game *game);
void update_game(Game *game, Player *player);
void render_game(Game *game, Player *player);
void destroy_game(Game *game);
int main(int argc, char *argv[]);

#endif /* GAME_CONFIG_H */

