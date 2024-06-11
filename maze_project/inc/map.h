#ifndef MAP_H
#define MAP_H

#include <stdbool.h>

#define MAP_NUM_ROWS 13
#define MAP_NUM_COLS 20
#define TILE_SIZE 64

bool DetectCollision(float x, float y);
void renderMap(void);
int getMapValue(int row, int col);
bool isInsideMap(float x, float y);

#endif /* MAP_H */

