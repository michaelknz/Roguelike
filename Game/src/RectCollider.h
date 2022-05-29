#ifndef RECTCOLLIDER_H
#define RECTCOLLIDER_H

#include "Collider.h"

class RectCollider : public Collider {
public:
	RectCollider(Transform* const tran, const Rectangle& rect, const std::string& tag, Entity* object);
	~RectCollider();
	bool IsCollide(Collider* other) override;
	Rectangle GetShape();
private:
	Rectangle rect;
};

#endif