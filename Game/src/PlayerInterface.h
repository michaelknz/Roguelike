#ifndef PLAYERINTERFACE_H
#define PLAYERINTERFACE_H

#include "Life_Bar.h"
#include "Inventory_Bar.h"
#include "Struct.h"

class PlayerInterface {
public:
	PlayerInterface(float aspect);
	~PlayerInterface();
	void SetLifeHearts(const LifeBarHeartsStruct& bar_info);
	void SetInventoryBar();
	void Update(int player_life);
private:
	Life_Bar* bar;
	Inventory_Bar* inv;
	float aspect;
};

#endif