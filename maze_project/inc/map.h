#ifndef MAP_H
#define MAP_H

#define MAP_WIDTH 20
#define MAP_HEIGHT 13

/* External map declaration */
extern char map[MAP_HEIGHT][MAP_WIDTH + 1];

/* Function prototype for loading the map */
void load_map(const char *filename);
int get_map_value(int x, int y);

#endif /* MAP_H */

