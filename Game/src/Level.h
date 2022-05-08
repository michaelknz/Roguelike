#ifndef LEVEL_H
#define LEVEL_H

#include <map>
#include "Math.h"
#include "Room.h"
#include "Camera.h"

class Level {
public:
	Level(Camera* cam);
	~Level();
	Room* GetCurRoom();
	void SetCurRoom(vectori2 val);
private:
	void GenLevel();
	Camera* camera;
	void SetDoors(vectori2 cur_c, vectori2 offset);
	Room* cur_room;
	vectori2 cur_room_coord;
	std::map<std::pair<int,int>, Room*> rooms;
	int rooms_col;
};

#endif