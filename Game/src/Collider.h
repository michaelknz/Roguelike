#ifndef COLLIDER_H
#define COLLIDER_H

#include <string>
#include "Struct.h"

class Entity;

enum {
	CIRCLE,
	RECTANGLE
};

class Collider {
public:
	Collider(int type, Transform* const tran, const std::string& tag, Entity* object);
	~Collider();
	virtual bool IsCollide(Collider* other);
	int GetType();
	std::string GetTag();
	Entity* GetObject();
private:
	void SetTag(const std::string& tag);
	int type;
	std::string tag;
	Entity* object;
protected:
	Transform* const transform;
};

#endif