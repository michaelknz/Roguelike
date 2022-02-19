#ifndef ANIMATOR_H
#define ANIMATOR_H

#include <vector>
#include "Math.h"
#include "Timer.h"
#include "Renderer.h"

class Animator {
public:
	Animator(const std::vector<vectorf2>& frames, float anim_speed);
	~Animator();
	void SetFrames(const std::vector<vectorf2>& frames);
	void Activate(bool is_on);
	void Update(const vectorf2& del_pos);
	vectorf2 GetCurFrame();
	int GetAnimMul();
private:
	std::vector<vectorf2> frames;
	Timer* timer;
	float time_to_change;
	bool is_on;
	int coord_index;
	float cur_time;
	int anim_mul;
};

#endif