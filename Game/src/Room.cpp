#include "Room.h"

Room::Room() {
	Init();
	SetMap();
	SetElem();
	SetWalls();
	SetTileMap();
}

Room::~Room() {
	delete tilemap;
}

void Room::Init() {
	tilemap_info.transform.pos.SetValue(-1.8f, 1.2f);
	tilemap_info.transform.rotation.SetValue(0, 0, 0);
	tilemap_info.transform.size.SetValue(0.15, 0.15);
	tilemap_info.transform.order = { -1, -1,
		                             -1,  1,
		                              1,  1,
		                             -1, -1,
		                              1,  1,
		                              1, -1 };
	tilemap_info.transform.shader_name = "TileMapShader";
	tilemap_info.transform.z = 0;
	tilemap_info.size.SetValue(25, 16);
	tilemap_info.texture.size.SetValue(8, 8);
	tilemap_info.texture.st_pos.SetValue(0, 0);
	tilemap_info.texture.name = "res/room.png";
}

void Room::SetMap() {
	tilemap_info.map = "l#######################r"
		               "s.......................S"
		               "s.......................S"
		               "s.......................S"
		               "s.......................S"
		               "s.......................S"
		               "s.......................S"
		               "s.......................S"
		               "s.......................S"
		               "s.......................S"
		               "s.......................S"
		               "s.......................S"
		               "s.......................S"
		               "s.......................S"
		               "s.......................S"
		               "L***********************R";
}

void Room::SetElem() {
	tilemap_info.elem['#'] = vectori2(1, 9);
	tilemap_info.elem['*'] = vectori2(1, 9);
	tilemap_info.elem['s'] = vectori2(0, 8);
	tilemap_info.elem['S'] = vectori2(3, 8);
	tilemap_info.elem['l'] = vectori2(0, 9);
	tilemap_info.elem['r'] = vectori2(3, 9);
	tilemap_info.elem['L'] = vectori2(0, 7);
	tilemap_info.elem['R'] = vectori2(3, 7);
	tilemap_info.elem['.'] = vectori2(1, 8);
}

void Room::SetCamera(Camera* cam) {
	tilemap->SetCamera(cam);
}

void Room::Draw() {
	tilemap->Draw();
}

void Room::SetTileMap() {
	tilemap = new TileMap(tilemap_info);
}

void Room::SetWalls() {
	walls.insert('#');
	walls.insert('*');
	walls.insert('s');
	walls.insert('S');
	walls.insert('l');
	walls.insert('L');
	walls.insert('r');
	walls.insert('R');
}