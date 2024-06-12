#ifndef PLAYER_H
#define PLAYER_H

#include <SDL2/SDL.h>
#include <stdbool.h>
#include "../inc/config.h"

typedef struct
{
	float x;
	float y;
	float width;
	float height;
	int walkDirection;
	int turnDirection;
	float rotationAngle;
	float walkSpeed;
	float turnSpeed;
} Player;

extern Player player;

void initPlayer(Player* player);
void handlePlayerInput(Player* player);
void movePlayer(Player* player, float deltaTime);
void renderPlayer(Player* player);
void movePlayerForward(Player* player);
void movePlayerBackward(Player* player);
void movePlayerLeft(Player* player);
void movePlayerRight(Player* player);

#endif /* PLAYER_H */

