#ifndef ROOM_H
#define ROOM_H

#include "TileMap.h"
#include "Mesh.h"
#include <string>
#include <map>
#include <set>
#include "Struct.h"
#include "Entity.h"

class Room: public Entity {
public:
	Room(const Transform& transform, Camera* cam, const vectori2& coord);
	~Room();
	virtual void SetMap();
	void SetElem();
	void SetDoor(char side);
	vectori2 GetCoord();
	void Update() override;
private:
	friend class InteractionPM;
	void Draw();
	void Init(const vectori2& coord);
	void SetTileMap();
	void SetWalls();
	void SetDoors();
	TileMapStruct tilemap_info;
	TileMap* tilemap;
	vectori2 coords;
	std::set<char> walls;
	std::set<char> doors;
};

#endif