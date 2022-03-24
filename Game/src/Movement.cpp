#include "Movement.h"

Movement::Movement() {

}

Movement::~Movement() {

}

vectorf2 Movement::Move(vectorf2& pos, float speed) {
	vectorf2 dir;
	dir.x = Input::GetButtonState('d') - Input::GetButtonState('a');
	dir.y = Input::GetButtonState('w') - Input::GetButtonState('s');
	if (dir.x != 0 || dir.y != 0) {
		dir = dir * (1.0f / sqrt(dir.x * dir.x + dir.y * dir.y));
	}
	pos.x += speed * dir.x;
	pos.y += speed * dir.y;
	return vectorf2(speed * dir.x, speed * dir.y);
}