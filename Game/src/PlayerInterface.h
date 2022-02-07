#ifndef PLAYERINTERFACE_H
#define PLAYERINTERFACE_H

#include "Life_Bar.h"
#include "Struct.h"

class PlayerInterface {
public:
	PlayerInterface(float aspect);
	~PlayerInterface();
	void SetLifeHearts(const LifeBarHeartsStruct& bar_info);
	void Update(int player_life);
private:
	Life_Bar* bar;
	float aspect;
};

#endif