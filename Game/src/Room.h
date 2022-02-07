#ifndef ROOM_H
#define ROOM_H

#include "TileMap.h"
#include "Mesh.h"
#include <string>
#include <map>
#include <set>
#include "Struct.h"

class Room {
public:
	Room();
	~Room();
	virtual void SetMap();
	void SetElem();
	void Draw();
	void SetCamera(Camera* cam);
private:
	friend class InteractionPM;
	void Init();
	void SetTileMap();
	void SetWalls();
	TileMapStruct tilemap_info;
	TileMap* tilemap;
	std::set<char> walls;
};

#endif