#ifndef LIFE_BAR_H
#define LIFE_BAR_H

#include "TileMap.h"
#include "Struct.h"
#include <algorithm>

class Life_Bar {
public:
	Life_Bar(float aspect, const LifeBarHeartsStruct& life_struct);
	~Life_Bar();
	void SetLifeHeards();
	void Update(int player_life);
private:
	void SetCamera();
	float aspect;
	TileMap* life_heards;
	LifeBarHeartsStruct life_info;
	Camera* camera;
};

#endif