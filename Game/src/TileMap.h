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
	TileMap(const TileMapStruct& tilemap_info);
	~TileMap();
	void Init(const TileMapStruct& tilemap_info);
	void Draw();
	void SetMap(const std::string* map, const std::map<char, vectori2>* elem);
	void SendToShader(vectorf2 block_size);
	void SendOffsets();
	void SetCamera(Camera* cam);
	void SetMapElem(int index, const vectori2& val);
private:
	Renderer* render;
	vectori2 size;
	TextureStruct texture_info;
	TransformQuad transform;
	const std::string* map;
	const std::map<char, vectori2>* elem;
};

#endif