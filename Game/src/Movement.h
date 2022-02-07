#ifndef MOVEMENT_H
#define MOVEMENT_H

#include <SDL.h>
#include <array>
#include <map>
#include <cmath>
#include "Math.h"

class Movement {
public:
	Movement();
	~Movement();
	void Update_Move(const SDL_Event& event);
	vectorf2 Move(vectorf2& pos, float speed);
private:
	std::array<bool, 4> buffer;
	std::map<int, int> buttons;
};

#endif