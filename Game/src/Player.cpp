#include "Player.h"
#include "InteractionPM.h"

Player::Player(const Transform& transform, Camera* cam):Entity(transform, cam) {
	Init();
	SetLifeBar();
	SetInventoryBar();
	SetAnimator();
	SetTag("Player");
}

void Player::Init() {
	TransformQuad transform_quad;
	transform_quad.size.SetValue(0.15f, 0.2f);
	size.SetValue(transform_quad.size.x, transform_quad.size.y);
	transform_quad.pos.SetValue(transform.pos.x, transform.pos.y);
	transform_quad.rotation = vectorf3(transform.rotation.x, transform.rotation.y, 0);
	transform_quad.z = -0.01f;
	spec.speed = 1.5f;
	spec.anim_speed = 0.15f;
	spec.max_life = 6;
	spec.cur_life = 6;
	texture_info.name = "res/Hero.png";
	texture_info.size = vectori2(17, 21);
	texture_info.st_pos = vectori2(8, 191);
	render = new Renderer(transform_quad, texture_info, camera);
	movement = new Movement;
	inter = new PlayerInterface(camera->GetAspect());
	timer = new Timer;
	cur_room = nullptr;
}

Player::~Player() {
	delete render;
	delete movement;
	delete animator;
	delete timer;
}

void Player::Update() {
	Move(timer->DelTime());
	render->SendVecotrf2(animator->GetCurFrame(), "anim_offset");
	transform.rotation.y = (float)((animator->GetAnimMul() * -1) + 1) * 90.0f;
	render->Draw(transform);
	inter->Update(spec.cur_life);
}

void Player::Move(float time) {
	vectorf2 del_pos = movement->Move(transform.pos, spec.speed * time);
	animator->Update(del_pos);
	InteractionPM::CollideWalls(this, cur_room, del_pos);
	InteractionPM::InteractWithDoor(this, cur_room, camera);
}

void Player::SetAnimator() {
	std::vector<vectori2> tmp_walk = { vectori2(0,0),vectori2(32,0), vectori2(64,0), vectori2(96,0) };
	std::vector<vectorf2> walk_frames;
	walk_frames.resize(tmp_walk.size());
	for (int i = 0; i < tmp_walk.size(); ++i) {
		walk_frames[i] = render->FromPixelsToCoords(tmp_walk[i]);
	}

	animator = new Animator(walk_frames, spec.anim_speed);
}

void Player::SetLifeBar() {
	LifeBarHeartsStruct life;
	life.max_life = spec.max_life;
	life.texture_pos = { vectori2(6,3),vectori2(5,3),vectori2(4,3) };
	life.texture.name = "res/room.png";
	life.texture.size = vectori2(8, 8);
	life.transform.size = vectorf2(0.12f, 0.12f);
	life.transform.pos = vectorf2(-camera->GetAspect() + life.transform.size.x / 2.0f, 1.0f - life.transform.size.y / 2.0f);
	inter->SetLifeHearts(life);
}

void Player::SetInventoryBar() {
	inter->SetInventoryBar();
}

void Player::SetCurRoom() {
	cur_room = dynamic_cast<Room*>(Scene::GetObjectsByTag("Room")[0]);
}