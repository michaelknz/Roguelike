#include "Collider.h"

Collider::Collider(int type, Transform* const tran, const std::string& tag, Entity* object):transform(tran) {
	this->type = type;
	SetTag(tag);
	this->object = object;
}

Collider::~Collider() {

}

int Collider::GetType() {
	return type;
}

bool Collider::IsCollide(Collider* other) {
	return false;
}

void Collider::SetTag(const std::string& tag) {
	this->tag = tag;
}

std::string Collider::GetTag() {
	return tag;
}

Entity* Collider::GetObject() {
	return object;
}