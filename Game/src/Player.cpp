#include "Player.h"
#include "InteractionPM.h"
#include "RectCollider.h"
#include "Scene.h"
#include "Log.h"

Player::Player(const Transform& transform, Camera* cam):Entity(transform, cam) {
	Init();
	SetLifeBar();
	SetInventoryBar();
	SetAnimator();
	SetColliders();
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
	inter = new PlayerInterface(camera);
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
	Log::VisCollider(colliders[0], camera);
}

void Player::Move(float time) {
	vectorf2 del_pos = movement->Move(transform.pos, spec.speed * time);
	animator->Update(del_pos);
	CollideWalls(del_pos);
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
	inter->SetLifeHearts(spec);
}

void Player::SetInventoryBar() {
	inter->SetInventoryBar();
}

void Player::SetCurRoom() {
	cur_room = dynamic_cast<Room*>(Scene::GetObjectsByTag("Room")[0]);
}

void Player::SetColliders() {
	colliders.push_back(new RectCollider(&transform,
		Rectangle(
			vectorf2(-size.x / 2.0f, -size.y / 2.0f),
			vectorf2(-size.x / 2.0f, size.y / 2.0f),
			vectorf2(size.x / 2.0f, size.y / 2.0f),
			vectorf2(size.x / 2.0f, -size.y / 2.0f)
		),
		"player",
		this));
}

void Player::CollideWalls(vectorf2 del_pos) {
	std::vector<Collider*> tmp;
	tmp = Scene::CheckCollide(colliders[0], "wallv");
	if (tmp.size() > 0) {
		vectorf2 tmp_del_pos = vectorf2(del_pos.x, 0);
		float mul = CountDelPos(tmp[0], tmp_del_pos);
		transform.pos.x -= (mul + 0.01f) * del_pos.x;
	}
	tmp = Scene::CheckCollide(colliders[0], "wallh");
	if (tmp.size() > 0) {
		vectorf2 tmp_del_pos = vectorf2(0, del_pos.y);
		float mul = CountDelPos(tmp[0], tmp_del_pos);
		transform.pos.y -= (mul + 0.01f) * del_pos.y;
	}
}

float Player::CountDelPos(Collider* other, vectorf2 dir) {
	dir = dir * (-1);
	Rectangle other_rect = dynamic_cast<RectCollider*>(other)->GetShape();
	Rectangle player_rect = dynamic_cast<RectCollider*>(colliders[0])->GetShape();
	std::array<vectorf2, 4> other_mas = { other_rect.point1, other_rect.point2, other_rect.point3, other_rect.point4 };
	std::array<vectorf2, 4> player_mas = { player_rect.point1, player_rect.point2, player_rect.point3, player_rect.point4 };
	float out = 0;
	for (int i = 0; i < 4; ++i) {
		vectorf2 tmp_p1 = player_mas[i % 4];
		vectorf2 tmp_p2 = player_mas[(i + 1) % 4];
		for (int j = 0; j < 4; ++j) {
			vectorf2 tmp = GeometryOp::GetDelMul(dir, tmp_p1, tmp_p2, other_mas[j]);
			if (fabs(tmp.x) <= 1.0f && fabs(tmp.y) <= 1.0f) {
				out = fmax(out, tmp.x);
			}
		}
	}
	dir = dir * (-1);
	for (int i = 0; i < 4; ++i) {
		vectorf2 tmp_p1 = other_mas[i % 4];
		vectorf2 tmp_p2 = other_mas[(i + 1) % 4];
		for (int j = 0; j < 4; ++j) {
			vectorf2 tmp = GeometryOp::GetDelMul(dir, tmp_p1, tmp_p2, player_mas[j]);
			if (fabs(tmp.x) <= 1.0f && fabs(tmp.y) <= 1.0f) {
				out = fmax(out, tmp.x);
			}
		}
	}
	return out;
}