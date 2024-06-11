#ifndef RAY_H
#define RAY_H

#include "player.h"
#include "config.h"
#include <stdbool.h>

typedef struct
{
	float rayAngle;
	float distance;
	int wallHitX;
	int wallHitY;
	bool wasHitVertical;
	int wallHitContent;
	bool isRayFacingDown;
	bool isRayFacingUp;
	bool isRayFacingLeft;
	bool isRayFacingRight;
} Ray;

extern Ray rays[NUM_RAYS];

void castRay(float rayAngle, int stripId);
void castAllRays();
void renderRays();

#endif /* RAY_H */

