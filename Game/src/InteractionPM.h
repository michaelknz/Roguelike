#ifndef INTERACTIONPM_H
#define INTERACTIONPM_H

#include "Player.h"
#include "Level.h"

class InteractionPM {
public:
	InteractionPM();
	~InteractionPM();
	static void CollideWalls(Player* player, Level* level);
	static void InteractWithDoor(Player* player, Level* level, Input* input, Camera* cam);
private:
	static vectorf2 PosInRoom(vectorf2 pos, Room* room);
	static vectori2 collide_code;
	static bool is_f;
};

#endif