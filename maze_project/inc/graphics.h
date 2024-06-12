#ifndef GRAPHICS_H
#define GRAPHICS_H

#include <SDL2/SDL.h>
#include <stdbool.h>
#include <stdint.h>
#include "config.h"

typedef uint32_t color_t;

extern SDL_Renderer *renderer;
extern SDL_Window *window;

bool initializeWindow(void);
void destroyWindow(void);
void clearColorBuffer(color_t color);
void renderColorBuffer(void);
void drawPixel(int x, int y, color_t color);
void drawLine(int x0, int y0, int x1, int y1, color_t color);
void renderWall(void);

#endif /* GRAPHICS_H */

