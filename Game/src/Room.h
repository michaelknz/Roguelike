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
	Room(const vectori2& coord);
	~Room();
	virtual void SetMap();
	void SetElem();
	void Draw();
	void SetCamera(Camera* cam);
	void SetDoor(char side);
private:
	friend class InteractionPM;
	void Init(const vectori2& coord);
	void SetTileMap();
	void SetWalls();
	void SetDoors();
	TileMapStruct tilemap_info;
	TileMap* tilemap;
	std::set<char> walls;
	std::set<char> doors;
};

#endif