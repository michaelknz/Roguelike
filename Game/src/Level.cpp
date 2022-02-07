#include "Level.h"

Level::Level(Camera* cam) {
	cur_room = new Room();
	SetCamera(cam);
}

Level::~Level() {
	delete cur_room;
}

void Level::SetCamera(Camera* cam) {
	cur_room->SetCamera(cam);
}

void Level::Update() {
	cur_room->Draw();
}

Room* Level::GetCurRoom() {
	return cur_room;
}