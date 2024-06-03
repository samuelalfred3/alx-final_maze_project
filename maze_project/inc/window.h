#ifndef WINDOW_H
#define WINDOW_H

#include <stdbool.h>
#include <SDL.h>
#include "config.h"

bool initializeWindow(void);
void destroyWindow(void);
void clearColorBuffer(color_t color);
void renderColorBuffer(void);
void drawPixel(int x, int y, color_t color);

#endif /* WINDOW_H */

