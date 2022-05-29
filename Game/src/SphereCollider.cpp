#include "SphereCollider.h"
#include "RectCollider.h"

SphereCollider::SphereCollider(Transform* const tran, const Circle& circ, const std::string& tag, Entity* object) :Collider(CIRCLE, tran, tag, object) {
	this->circ = circ;
}

SphereCollider::~SphereCollider() {

}

Circle SphereCollider::GetShape() {
	return Circle(circ.center + transform->pos, circ.radius);
}

bool SphereCollider::IsCollide(Collider* other) {
	if (other->GetType() == CIRCLE) {
		return GeometryOp::CircleWithCircle(GetShape(), dynamic_cast<SphereCollider*>(other)->GetShape());
	}
	else {
		return GeometryOp::CircleWithRectangle(GetShape(), dynamic_cast<RectCollider*>(other)->GetShape());
	}
}