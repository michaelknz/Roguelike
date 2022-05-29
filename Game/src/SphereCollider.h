#ifndef SPHERECOLLIDER_H
#define SPHERECOLLIDER_H

#include "Collider.h"

class SphereCollider : public Collider {
public:
	SphereCollider(Transform* const tran, const Circle& circ, const std::string& tag, Entity* object);
	~SphereCollider();
	bool IsCollide(Collider* other) override;
	Circle GetShape();
private:
	Circle circ;
};

#endif