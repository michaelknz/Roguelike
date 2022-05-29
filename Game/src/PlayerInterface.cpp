#include "PlayerInterface.h"

PlayerInterface::PlayerInterface(Camera* cam) {
	this->aspect = cam->GetAspect();
	bar = nullptr;
	inv = nullptr;
}

PlayerInterface::~PlayerInterface() {
	if (bar != nullptr) {
		delete bar;
		bar = nullptr;
	}
	if (inv != nullptr) {
		delete inv;
		inv = nullptr;
	}
}

void PlayerInterface::SetLifeHearts(const CharSpec& player_info) {
	LifeBarHeartsStruct life;
	life.max_life = player_info.max_life;
	life.texture_pos = { vectori2(6,3),vectori2(5,3),vectori2(4,3) };
	life.texture.name = "res/room.png";
	life.texture.size = vectori2(8, 8);
	life.transform.size = vectorf2(0.12f, 0.12f);
	life.transform.pos = vectorf2(-aspect + life.transform.size.x / 2.0f, 1.0f - life.transform.size.y / 2.0f);
	bar = new Life_Bar(aspect, life);
}

void PlayerInterface::SetInventoryBar() {
	InvectoryBarInfo inv_info;
	inv_info.pos = vectorf2(-aspect + 0.06f, 0.8f);
	inv_info.texture_pos[0] = vectori2(1, 3);
	inv_info.texture_pos[1] = vectori2(0, 3);
	inv_info.size = vectori2(5, 1);
	inv_info.texture.name = "res/room.png";
	inv_info.texture.size = vectori2(8, 8);
	inv = new Inventory_Bar(aspect, inv_info);
}

void PlayerInterface::Update(int player_life) {
	bar->Update(player_life);
	inv->Update();
}