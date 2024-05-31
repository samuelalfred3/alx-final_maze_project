#ifndef MAP_H
#define MAP_H

#define MAP_WIDTH 10
#define MAP_HEIGHT 9

extern char map[MAP_HEIGHT][MAP_WIDTH + 1];

/* Function to load the map from a file */
void load_map(const char *filename);

#endif /* MAP_H */

