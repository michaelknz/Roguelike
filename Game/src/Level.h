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
	void SetCamera(Camera* cam);
	void Update();
	Room* GetCurRoom();
private:
	Room* cur_room;

};

#endif