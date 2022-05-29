#include "Room.h"
#include "RectCollider.h"
#include "Log.h"

Room::Room(const Transform& transform, Camera* cam, const vectori2& coord): Entity(transform, cam) {
	Init(coord);
	SetMap();
	SetElem();
	SetWalls();
	SetDoors();
	SetTileMap();
	SetColliders();
	SetTag("Room");
}

Room::~Room() {
	delete tilemap;
}

void Room::Init(const vectori2& coord) {
	tilemap_info.transform.size.SetValue(0.15, 0.15);
	tilemap_info.size.SetValue(25, 16);
	tilemap_info.transform.pos.SetValue(transform.pos.x + (float)coord.x * tilemap_info.transform.size.x * (float)tilemap_info.size.x, 
		                                transform.pos.y + (float)coord.y * tilemap_info.transform.size.y * (float)tilemap_info.size.y);
	transform.pos = tilemap_info.transform.pos;
	tilemap_info.texture.size.SetValue(8, 8);
	tilemap_info.texture.name = "res/room.png";
	coords = coord;
}

void Room::Update() {
	Draw();
	for (int i = 0; i < 4; ++i) {
		Log::VisCollider(colliders[i], camera);
	}
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
	tilemap_info.elem['d'] = vectori2(4, 7);
	tilemap_info.elem['o'] = vectori2(11, 6);
	tilemap_info.elem['p'] = vectori2(12, 6);
}

void Room::Draw() {
	tilemap->Draw(transform);
}

void Room::SetTileMap() {
	tilemap = new TileMap(tilemap_info, camera);
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
	walls.insert('d');
	walls.insert('o');
	walls.insert('p');
}

void Room::SetDoors() {
	doors.insert('d');
	doors.insert('o');
	doors.insert('p');
}

void Room::SetDoor(char side) {
	int index = 0;
	switch (side)
	{
	case 'l':
		index = tilemap_info.size.y / 2 * tilemap_info.size.x;
		tilemap_info.map[index] = 'o';
		tilemap->SetMapElem(index, 'o');
		break;
	case 'r':
		index = tilemap_info.size.y / 2 * tilemap_info.size.x + tilemap_info.size.x - 1;
		tilemap_info.map[index] = 'p';
		tilemap->SetMapElem(index, 'p');
		break;
	case 'u':
		index = tilemap_info.size.x / 2;
		tilemap_info.map[index] = 'd';
		tilemap->SetMapElem(index, 'd');
		break;
	case 'd':
		index = (tilemap_info.size.y - 1) * tilemap_info.size.x + tilemap_info.size.x / 2;
		tilemap_info.map[index] = 'd';
		tilemap->SetMapElem(index, 'd');
		break;
	default:
		break;
	}
}

vectori2 Room::GetCoord() {
	return coords;
}

void Room::SetColliders() {
	vectorf2 st = vectorf2(-tilemap_info.transform.size.x / 2.0f, tilemap_info.transform.size.y / 2.0f);
	vectori2 fsize = tilemap_info.size;
	vectorf2 tsize = tilemap_info.transform.size;
	colliders.push_back(new RectCollider(&transform,
		Rectangle(
			st,
			vectorf2(st.x + tsize.x * (0.75f), st.y),
			vectorf2(st.x + tsize.x * (0.75f), st.y - ((float)fsize.y * tsize.y)),
			vectorf2(st.x, st.y - ((float)fsize.y * tsize.y))),
		"wallv", this));
	colliders.push_back(new RectCollider(&transform,
		Rectangle(
			st,
			vectorf2(st.x + ((float)fsize.x * tsize.x), st.y),
			vectorf2(st.x + ((float)fsize.x * tsize.x), st.y - tsize.y),
			vectorf2(st.x, st.y - tsize.y)),
		"wallh", this));
	colliders.push_back(new RectCollider(&transform,
		Rectangle(
			vectorf2(st.x + ((float)(fsize.x - 1) * tsize.x + tsize.x * (0.25f)), st.y),
			vectorf2(st.x + ((float)fsize.x * tsize.x), st.y),
			vectorf2(st.x + ((float)fsize.x * tsize.x), st.y - ((float)fsize.y * tsize.y)),
			vectorf2(st.x + ((float)(fsize.x - 1) * tsize.x + tsize.x * (0.25f)), st.y - ((float)fsize.y * tsize.y))),
		"wallv", this));
	colliders.push_back(new RectCollider(&transform,
		Rectangle(
			vectorf2(st.x + ((float)fsize.x * tsize.x), st.y - ((float)(fsize.y - 1) * tsize.y)),
			vectorf2(st.x + ((float)fsize.x * tsize.x), st.y - ((float)fsize.y * tsize.y)),
			vectorf2(st.x, st.y - ((float)fsize.y * tsize.y)),
			vectorf2(st.x, st.y - ((float)(fsize.y - 1) * tsize.y))
		),
		"wallh", this));
}