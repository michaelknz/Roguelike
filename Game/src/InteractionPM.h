#ifndef INTERACTIONPM_H
#define INTERACTIONPM_H

#include "Player.h"
#include "Room.h"

class InteractionPM {
public:
	InteractionPM();
	~InteractionPM();
	static void CollideWalls(Player* player, Room* room, vectorf2 del_pos);
	static void InteractWithDoor(Player* player, Room* room, Camera* cam);
	static vectori2 GetRoomMove();
	static void RoomMoveToZero();
private:
	static vectorf2 PosInRoom(vectorf2 pos, Room* room);
	static vectori2 collide_code;
	static bool is_f;
	static vectori2 room_move;
};

#endif