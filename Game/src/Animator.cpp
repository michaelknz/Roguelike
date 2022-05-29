#include "Animator.h"

Animator::Animator(const std::vector<vectorf2>& frames, float anim_speed) {
	SetFrames(frames);
	timer = new Timer;
	time_to_change = anim_speed;
	is_on = true;
	anim_mul = 1;
	Activate(false);
}

Animator::~Animator() {
	delete timer;
}

void Animator::SetFrames(const std::vector<vectorf2>& frames) {
	this->frames.resize(frames.size());
	for (int i = 0; i < frames.size(); ++i) {
		this->frames[i] = frames[i];
	}
}

void Animator::Activate(bool is_on) {
	if (this->is_on != is_on) {
		this->is_on = is_on;
		cur_time = time_to_change;
		coord_index = 0;
		timer->DelTime();
	}
}

void Animator::Update(const vectorf2& del_pos) {

	if (del_pos.x * del_pos.x + del_pos.y * del_pos.y == 0) {
		Activate(false);
	}

	else {
		Activate(true);
	}

	if (del_pos.x != 0) {
		anim_mul = (int)(del_pos.x / abs(del_pos.x));
	}

	if (is_on) {
		float a = timer->DelTime();
		cur_time += a;
		coord_index += (int)(cur_time / time_to_change);
		cur_time -= (float)((int)(cur_time / time_to_change)) * time_to_change;
		coord_index %= frames.size();
	}
}

vectorf2 Animator::GetCurFrame() {
	return frames[coord_index];
}

int Animator::GetAnimMul() {
	return anim_mul;
}