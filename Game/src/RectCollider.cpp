#include "RectCollider.h"
#include "SphereCollider.h"
#include "Log.h"

RectCollider::RectCollider(Transform* const tran, const Rectangle& rect, const std::string& tag, Entity* object) :Collider(RECTANGLE, tran, tag, object) {
	this->rect = rect;
}

RectCollider::~RectCollider() {

}

Rectangle RectCollider::GetShape() {
	return Rectangle(transform->pos + rect.point1, transform->pos + rect.point2, transform->pos + rect.point3, transform->pos + rect.point4);
}

bool RectCollider::IsCollide(Collider* other) {
	if (other->GetType() == CIRCLE) {
		return GeometryOp::CircleWithRectangle(dynamic_cast<SphereCollider*>(other)->GetShape(), GetShape());
	}
	else {
		return GeometryOp::RectangleWithRectangle(GetShape(), dynamic_cast<RectCollider*>(other)->GetShape());
	}
}