#include "../inc/maze.h"

/**
 * initRain - initialize rain particles
 * @rain: pointer to the rain structure
 */
void initRain(rain_t *rain)
{
	for (int i = 0; i < RAIN_DROP_COUNT; i++)
	{
		rain->particles[i].x = rand() % SCREEN_WIDTH;
		rain->particles[i].y = rand() % SCREEN_HEIGHT;
		rain->particles[i].speed = RAIN_SPEED_MIN + (rand() % (RAIN_SPEED_MAX - RAIN_SPEED_MIN));
	}
	rain->enabled = true;
}

/**
 * updateRain - update rain particle positions
 * @rain: pointer to the rain structure
 * @deltaTime: time since last frame
 */
void updateRain(rain_t *rain, float deltaTime)
{
	for (int i = 0; i < RAIN_DROP_COUNT; i++)
	{
		rain->particles[i].y += rain->particles[i].speed * deltaTime;
		if (rain->particles[i].y > SCREEN_HEIGHT)
		{
			rain->particles[i].y = 0;
			rain->particles[i].x = rand() % SCREEN_WIDTH;
		}
	}
}

/**
 * renderRain - render rain particles
 * @rain: pointer to the rain structure
 * @renderer: SDL_Renderer to render on
 */
void renderRain(rain_t *rain, SDL_Renderer *renderer)
{
	for (int i = 0; i < RAIN_DROP_COUNT; i++)
	{
		SDL_RenderDrawLine(renderer, rain->particles[i].x,
				rain->particles[i].y,
				rain->particles[i].x,
				rain->particles[i].y + RAIN_DROP_LENGTH);
	}
}

