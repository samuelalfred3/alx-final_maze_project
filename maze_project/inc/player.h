#ifndef PLAYER_H
#define PLAYER_H

#include <SDL2/SDL.h>
#include <stdbool.h>

typedef struct {
	float x;
	float y;
	float width;
	float height;
	int turnDirection;
	int walkDirection;
	float rotationAngle;
	float walkSpeed;
	float turnSpeed;
} Player;

extern Player player;

void movePlayer(Player* player, float deltaTime);
void movePlayerForward();
void movePlayerBackward();
void movePlayerLeft();
void movePlayerRight();
void renderPlayer();
void handlePlayerInput(Player* player);

#endif

