#ifndef WINDOW_H
#define WINDOW_H

#include <stdbool.h>
#include <SDL2/SDL.h>

extern SDL_Window *window;
extern SDL_Renderer *renderer;

bool initWindow(void);
void destroyWindow(void);

#endif /* WINDOW_H */

