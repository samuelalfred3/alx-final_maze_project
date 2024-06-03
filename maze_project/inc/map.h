#ifndef MAP_H
#define MAP_H

#define MAP_WIDTH 10
#define MAP_HEIGHT 9

/* External map declaration */
extern char map[MAP_HEIGHT][MAP_WIDTH + 1];

/* Function prototype for loading the map */
void load_map(const char *filename);

#endif /* MAP_H */

