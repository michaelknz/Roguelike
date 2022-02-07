#ifndef INTERACTIONPM_H
#define INTERACTIONPM_H

#include "Player.h"
#include "Level.h"

class InteractionPM {
public:
	InteractionPM();
	~InteractionPM();
	static void CollideWalls(Player* player, Level* level);
private:
	static vectori2 collide_code;
};

#endif