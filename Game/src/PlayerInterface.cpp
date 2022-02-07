#include "PlayerInterface.h"

PlayerInterface::PlayerInterface(float aspect) {
	this->aspect = aspect;
	bar = nullptr;
}

PlayerInterface::~PlayerInterface() {
	if (bar != nullptr) {
		delete bar;
		bar = nullptr;
	}
}

void PlayerInterface::SetLifeHearts(const LifeBarHeartsStruct& bar_info) {
	bar = new Life_Bar(aspect, bar_info);
}

void PlayerInterface::Update(int player_life) {
	bar->Update(player_life);
}