#include "Movement.h"

Movement::Movement() {
	buffer = { false, false, false, false };
	buttons[SDLK_w] = 0;
	buttons[SDLK_a] = 1;
	buttons[SDLK_s] = 2;
	buttons[SDLK_d] = 3;
}

Movement::~Movement() {

}

void Movement::Update_Move(const SDL_Event& event) {
	if (event.type == SDL_KEYDOWN) {
		if (buttons.find(event.key.keysym.sym) != buttons.end()) {
			buffer[buttons[event.key.keysym.sym]] = true;
		}
	}

	if (event.type == SDL_KEYUP) {
		if (buttons.find(event.key.keysym.sym) != buttons.end()) {
			buffer[buttons[event.key.keysym.sym]] = false;
		}
	}
}

vectorf2 Movement::Move(vectorf2& pos, float speed) {
	vectorf2 dir;
	dir.x = buffer[3] - buffer[1];
	dir.y = buffer[0] - buffer[2];
	if (dir.x != 0 || dir.y != 0) {
		dir = dir * (1.0f / sqrt(dir.x * dir.x + dir.y * dir.y));
	}
	pos.x += speed * dir.x;
	pos.y += speed * dir.y;
	return vectorf2(speed * dir.x, speed * dir.y);
}