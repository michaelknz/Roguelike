#include "PlayerInterface.h"

PlayerInterface::PlayerInterface(float aspect) {
	this->aspect = aspect;
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

void PlayerInterface::SetLifeHearts(const LifeBarHeartsStruct& bar_info) {
	bar = new Life_Bar(aspect, bar_info);
}

void PlayerInterface::SetInventoryBar() {
	InvectoryBarInfo inv_info;
	inv_info.pos = vectorf2(-aspect + 0.06f, 0.8f);
	inv_info.texture_pos[0] = vectori2(1, 3);
	inv_info.texture_pos[1] = vectori2(0, 3);
	inv_info.size = vectori2(5, 1);
	inv_info.texture.name = "res/room.png";
	inv_info.texture.size = vectori2(8, 8);
	inv_info.texture.st_pos = vectori2(0, 0);
	inv = new Inventory_Bar(aspect, inv_info);
}

void PlayerInterface::Update(int player_life) {
	bar->Update(player_life);
	inv->Update();
}