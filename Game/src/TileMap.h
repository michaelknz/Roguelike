#ifndef TILEMAP_H
#define TILEMAP_H

#include "Renderer.h"
#include "Math.h"
#include "Camera.h"
#include <string>
#include <map>
#include "Struct.h"

class TileMap {
public:
	TileMap(const TileMapStruct& tilemap_info, Camera* cam);
	~TileMap();
	void Init(const TileMapStruct& tilemap_info);
	void Draw(Transform transform);
	void SetMap(const std::string map, const std::map<char, vectori2> elem);
	void SetMapElem(int index, char val);
private:
	void SendToShader(vectorf2 block_size);
	void SendOffsets();
	Renderer* render;
	vectori2 size;
	TextureStruct texture_info;
	TransformQuad transform;
	std::string map;
	std::map<char, vectori2> elem;
};

#endif