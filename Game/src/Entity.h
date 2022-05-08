#ifndef ENTITY_H
#define ENTITY_H

#include "Struct.h"
#include "Camera.h"

class Entity {
public:
	Entity(const Transform& transform, Camera* cam);
	~Entity();
	void SetTag(const std::string& tag);
	std::string Get_Tag();
	virtual void Update();
protected:
	Transform transform;
	Camera* camera;
	std::string tag;
};

#endif