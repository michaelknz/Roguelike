#ifndef MOVEMENT_H
#define MOVEMENT_H

#include <SDL.h>
#include <array>
#include <map>
#include <cmath>
#include "Math.h"
#include "Input.h"

class Movement {
public:
	Movement();
	~Movement();
	vectorf2 Move(vectorf2& pos, float speed, Input* input);
};

#endif