#include "Entity.h"

Entity::Entity(const Transform& transform, Camera* cam) {
	this->transform = transform;
	camera = cam;
}

Entity::~Entity() {
	for (int i = 0; i < colliders.size(); ++i) {
		delete colliders[i];
	}
}

void Entity::Update() {

}

void Entity::SetTag(const std::string& tag) {
	this->tag = tag;
}

std::string Entity::Get_Tag() {
	return tag;
}

std::vector<Collider*>* Entity::GetColliders() {
	return &colliders;
}