#ifndef PLAYER_H
#define PLAYER_H

#include "Math.h"
#include "Renderer.h"
#include "Movement.h"
#include "Animator.h"
#include "PlayerInterface.h"
#include "Struct.h"
#include "Scene.h"
#include "Room.h"

class Player: public Entity {
public:
	Player(const Transform& transform, Camera* cam);
	~Player();
	void Update() override;
	void SetCurRoom();
private:
	friend class InteractionPM;
	void Init();
	void SetAnimator();
	void SetLifeBar();
	void SetInventoryBar();
	void Move(float time);
	void SetColliders();
	void CollideWalls(vectorf2 del_pos);
	float CountDelPos(Collider* other, vectorf2 dir);
	TextureStruct texture_info;
	CharSpec spec;
	Room* cur_room;
	vectorf2 size;
	Renderer* render;
	Movement* movement;
	Animator* animator;
	PlayerInterface* inter;
	Timer* timer;
};

#endif