#include "Player.h"

Player::Player(Camera* cam) {
	Init(cam->GetAspect());
	SetCamera(cam);
	SetLifeBar(cam->GetAspect());
	SetAnimator();
}

void Player::SetCamera(Camera* cam) {
	render->SetCamera(cam);
}

void Player::Init(float aspect) {
	del_pos.SetValue(0, 0);
	transform.size.SetValue(0.15f, 0.2f);
	transform.pos.SetValue(0, 0);
	transform.rotation = vectorf3(0, 0, 0);
	transform.shader_name = "DefaultShader";
	transform.order = { -1, -1,
		                -1,  1,
		                 1,  1,
		                -1, -1,
		                 1,  1,
		                 1, -1 };
	transform.z = -0.01f;
	spec.speed = 1.5f;
	spec.max_life = 6;
	spec.cur_life = 6;
	texture_info.name = "res/Hero.png";
	texture_info.size = vectori2(17, 21);
	texture_info.st_pos = vectori2(8, 191);
	render = new Renderer(transform, texture_info);
	movement = new Movement;
	inter = new PlayerInterface(aspect);
}

Player::~Player() {
	delete render;
	delete movement;
	delete animator;
}

void Player::Update() {
	animator->Update(del_pos);
	render->SendVecotrf2(animator->GetCurFrame(), "anim_offset");
	transform.rotation.y = (float)((animator->GetAnimMul() * -1) + 1) * 90.0f;
	render->Draw(transform);
	inter->Update(spec.cur_life);
}

void Player::Update_Move(const SDL_Event& event) {
	movement->Update_Move(event);
}

void Player::Move(float time) {
	del_pos = movement->Move(transform.pos, spec.speed * time);
}

void Player::SetAnimator() {
	std::vector<vectori2> tmp_walk = { vectori2(0,0),vectori2(32,0), vectori2(64,0), vectori2(96,0) };
	walk_frames.resize(tmp_walk.size());
	for (int i = 0; i < tmp_walk.size(); ++i) {
		walk_frames[i] = render->FromPixelsToCoords(tmp_walk[i]);
	}

	animator = new Animator(walk_frames);
}

void Player::SetLifeBar(float aspect) {
	LifeBarHeartsStruct life;
	life.max_life = spec.max_life;
	life.texture_pos = { vectori2(6,3),vectori2(5,3),vectori2(4,3) };
	life.texture.name = "res/room.png";
	life.texture.size = vectori2(8, 8);
	life.texture.st_pos = vectori2(0, 0);
	life.transform.size = vectorf2(0.15f, 0.15f);
	life.transform.shader_name = "TileMapShader";
	life.transform.rotation = vectorf3(0, 0, 0);
	life.transform.order= { -1, -1,
						    -1,  1,
						     1,  1,
						    -1, -1,
						     1,  1,
						     1, -1 };
	life.transform.z = 0.0;
	life.transform.pos = vectorf2(-aspect + life.transform.size.x / 2.0f, 1.0f - life.transform.size.y / 2.0f);
	inter->SetLifeHearts(life);
}