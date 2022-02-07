#include "TileMap.h"

TileMap::TileMap(const TileMapStruct& tilemap_info) {
	render = new Renderer(tilemap_info.transform, tilemap_info.texture);
	Init(tilemap_info);
	SetMap(&(tilemap_info.map), &(tilemap_info.elem));
	SendToShader(tilemap_info.transform.size);
}

TileMap::~TileMap() {
	delete render;
}

void TileMap::SetMap(const std::string* map, const std::map<char, vectori2>* elem) {
	this->map = map;
	this->elem = elem;
}

void TileMap::SetCamera(Camera* cam) {
	render->SetCamera(cam);
}

void TileMap::Init(const TileMapStruct& tilemap_info) {
	this->transform.pos = tilemap_info.transform.pos;
	this->transform.rotation = tilemap_info.transform.rotation;
	this->transform.shader_name = tilemap_info.transform.shader_name;
	this->transform.size = tilemap_info.transform.size;
	for (int i = 0; i < tilemap_info.transform.order.size(); ++i) {
		this->transform.order[i] = tilemap_info.transform.order[i];
	}
	this->transform.z = tilemap_info.transform.z;
	this->size = tilemap_info.size;
	this->texture_info.size = tilemap_info.texture.size;
	this->texture_info.st_pos = tilemap_info.texture.st_pos;
	this->texture_info.name = tilemap_info.texture.name;
}

void TileMap::SendOffsets() {
	for (int i = 0; i < size.x * size.y; ++i) {
		vectori2 tmpi = (*elem).at((*map)[i]);
		tmpi.x *= texture_info.size.x;
		tmpi.y *= texture_info.size.y;
		vectorf2 tmp = render->FromPixelsToCoords(tmpi);
		render->SendVecotrf2(tmp, "offsets[" + std::to_string(i) + "]");
	}
}

void TileMap::SendToShader(vectorf2 block_size) {
	render->SendVecotrf2(block_size, "block_size");
	render->Sendi1(size.x, "width");
	SendOffsets();
}

void TileMap::Draw() {
	render->DrawInstance(transform, size.x * size.y);
}

void TileMap::SetMapElem(int index, const vectori2& val) {
	vectori2 tmpi = val;
	tmpi.x *= texture_info.size.x;
	tmpi.y *= texture_info.size.y;
	vectorf2 tmp = render->FromPixelsToCoords(tmpi);
	render->SendVecotrf2(tmp, "offsets[" + std::to_string(index) + "]");
}