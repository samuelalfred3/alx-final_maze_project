#ifndef CONFIG_H
#define CONFIG_H

/* Screen dimensions */
#define SCREEN_WIDTH 800
#define SCREEN_HEIGHT 600

/* Map dimensions */
#define MAP_WIDTH 10
#define MAP_HEIGHT 10

/* Player movement speeds */
#define MOVE_SPEED 0.05
#define ROT_SPEED 0.03

/* Map representation (use a smaller map for simplicity) */
extern const char map[MAP_HEIGHT][MAP_WIDTH + 1];

#endif /* CONFIG_H */

