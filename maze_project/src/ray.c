#include <math.h>
#include <SDL2/SDL.h>
#include "../inc/game_config.h"
#include "../inc/graphics_utils.h"

extern Player player;
Ray rays[NUM_RAYS];

/**
 * normalizeAngle - Normalize the angle to be within 0 to 2*PI.
 * @angle: The angle to be normalized.
 * Return: The normalized angle.
 */
float normalizeAngle(float angle)
{
	angle = fmod(angle, 2 * PI);
	if (angle < 0)
	{
		angle += 2 * PI;
	}
	return (angle);
}

/**
 * distanceBetweenPoints - Calculate the distance between two points.
 * @x1: The x-coordinate of the first point.
 * @y1: The y-coordinate of the first point.
 * @x2: The x-coordinate of the second point.
 * @y2: The y-coordinate of the second point.
 * Return: The distance between the two points.
 */
float distanceBetweenPoints(float x1, float y1, float x2, float y2)
{
	return (sqrtf((x2 - x1) * (x2 - x1) + (y2 - y1) * (y2 - y1)));
}

/**
 * castRay - Cast a single ray.
 * @rayAngle: The angle of the ray.
 * @stripId: The ID of the strip.
 */
void castRay(float rayAngle, int stripId)
{
	rayAngle = normalizeAngle(rayAngle);

	bool isRayFacingDown = rayAngle > 0 && rayAngle < PI;
	bool isRayFacingUp = !isRayFacingDown;

	bool isRayFacingRight = rayAngle < 0.5 * PI || rayAngle > 1.5 * PI;
	bool isRayFacingLeft = !isRayFacingRight;

	float xintercept, yintercept;
	float xstep, ystep;

	/* Horizontal ray-grid intersection */
	bool foundHorzWallHit = false;
	float horzWallHitX = 0;
	float horzWallHitY = 0;
	int horzWallContent = 0

		yintercept = floorf(player.y / TILE_SIZE) * TILE_SIZE;
	yintercept += isRayFacingDown ? TILE_SIZE : 0;

	xintercept = player.x + (yintercept - player.y) / tanf(rayAngle);

	ystep = TILE_SIZE;
	ystep *= isRayFacingUp ? -1 : 1;

	xstep = TILE_SIZE / tanf(rayAngle);
	xstep *= (isRayFacingLeft && xstep > 0) ? -1 : 1;
	xstep *= (isRayFacingRight && xstep < 0) ? -1 : 1;

	float nextHorzTouchX = xintercept;
	float nextHorzTouchY = yintercept;

	while (isInsideMap(nextHorzTouchX, nextHorzTouchY))
	{
		float xToCheck = nextHorzTouchX;
		float yToCheck = nextHorzTouchY + (isRayFacingUp ? -1 : 0);

		if (DetectCollision(xToCheck, yToCheck))
		{
			foundHorzWallHit = true;
			horzWallHitX = nextHorzTouchX;
			horzWallHitY = nextHorzTouchY;
			horzWallContent = getMapValue((int)floorf(yToCheck / TILE_SIZE), (int)floorf(xToCheck / TILE_SIZE));
			break;
		}
		else
		{
			nextHorzTouchX += xstep;
			nextHorzTouchY += ystep;
		}
	}

	/* Vertical ray-grid intersection */
	bool foundVertWallHit = false;
	float vertWallHitX = 0;
	float vertWallHitY = 0;
	int vertWallContent = 0;

	xintercept = floorf(player.x / TILE_SIZE) * TILE_SIZE;
	xintercept += isRayFacingRight ? TILE_SIZE : 0;

	yintercept = player.y + (xintercept - player.x) * tanf(rayAngle);

	xstep = TILE_SIZE;
	xstep *= isRayFacingLeft ? -1 : 1;

	ystep = TILE_SIZE * tanf(rayAngle);
	ystep *= (isRayFacingUp && ystep > 0) ? -1 : 1;
	ystep *= (isRayFacingDown && ystep < 0) ? -1 : 1;

	float nextVertTouchX = xintercept;
	float nextVertTouchY = yintercept;

	while (isInsideMap(nextVertTouchX, nextVertTouchY))
	{
		float xToCheck = nextVertTouchX + (isRayFacingLeft ? -1 : 0);
		float yToCheck = nextVertTouchY;

		if (DetectCollision(xToCheck, yToCheck))
		{
			foundVertWallHit = true;
			vertWallHitX = nextVertTouchX;
			vertWallHitY = nextVertTouchY;
			vertWallContent = getMapValue((int)floorf(yToCheck / TILE_SIZE), (int)floorf(xToCheck / TILE_SIZE));
			break;
		}
		else
		{
			nextVertTouchX += xstep;
			nextVertTouchY += ystep;
		}
	}

	float horzHitDistance = foundHorzWallHit
		? distanceBetweenPoints(player.x, player.y, horzWallHitX, horzWallHitY)
		: FLT_MAX;
	float vertHitDistance = foundVertWallHit
		? distanceBetweenPoints(player.x, player.y, vertWallHitX, vertWallHitY)
		: FLT_MAX;

	if (vertHitDistance < horzHitDistance)
	{
		rays[stripId].distance = vertHitDistance;
		rays[stripId].wallHitX = vertWallHitX;
		rays[stripId].wallHitY = vertWallHitY;
		rays[stripId].wasHitVertical = true;
		rays[stripId].wallHitContent = vertWallContent;
	}
	else
	{
		rays[stripId].distance = horzHitDistance;
		rays[stripId].wallHitX = horzWallHitX;
		rays[stripId].wallHitY = horzWallHitY;
		rays[stripId].wasHitVertical = false;
		rays[stripId].wallHitContent = horzWallContent;
	}

	rays[stripId].rayAngle = rayAngle;
	rays[stripId].isRayFacingDown = isRayFacingDown;
	rays[stripId].isRayFacingUp = isRayFacingUp;
	rays[stripId].isRayFacingLeft = isRayFacingLeft;
	rays[stripId].isRayFacingRight = isRayFacingRight;
}

/**
 * castAllRays - Cast all rays for the current frame.
 */
void castAllRays(void)
{
	float rayAngle = player.rotationAngle - (FOV_ANGLE / 2);
	for (int stripId = 0; stripId < NUM_RAYS; stripId++)
	{
		castRay(rayAngle, stripId);
		rayAngle += FOV_ANGLE / NUM_RAYS;
	}
}

/**
 * renderRays - Render all rays.
 */
void renderRays(void)
{
	for (int i = 0; i < NUM_RAYS; i++)
	{
		drawLine(
				player.x * MINIMAP_SCALE_FACTOR,
				player.y * MINIMAP_SCALE_FACTOR,
				rays[i].wallHitX * MINIMAP_SCALE_FACTOR,
				rays[i].wallHitY * MINIMAP_SCALE_FACTOR,
				0xFFFF0000
				);
	}
}

