#ifndef PLAYER_H
#define PLAYER_H

#include "Math.h"
#include "Renderer.h"
#include "Movement.h"
#include "Animator.h"
#include "PlayerInterface.h"
#include "Struct.h"

class Player {
public:
	Player(Camera* cam);
	~Player();
	void Update();
	void SetCamera(Camera* cam);
	void Move(float time);
private:
	friend class InteractionPM;
	void Init(float aspect);
	void SetAnimator();
	void SetLifeBar(float aspect);
	void SetInventoryBar();
	TransformQuad transform;
	TextureStruct texture_info;
	CharSpec spec;
	vectorf2 del_pos;
	std::vector<vectorf2> walk_frames;
	Renderer* render;
	Movement* movement;
	Animator* animator;
	PlayerInterface* inter;
};

#endif