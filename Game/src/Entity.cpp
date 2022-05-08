#include "Entity.h"

Entity::Entity(const Transform& transform, Camera* cam) {
	this->transform = transform;
	camera = cam;
}

Entity::~Entity() {

}

void Entity::Update() {

}

void Entity::SetTag(const std::string& tag) {
	this->tag = tag;
}

std::string Entity::Get_Tag() {
	return tag;
}