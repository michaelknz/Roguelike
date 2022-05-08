#include "Quad.h"

Quad::Quad() {
	mesh = new Mesh;
}

Quad::~Quad() {
	delete mesh;
}

void Quad::SendVertices(const TransformQuad& transform) {
	std::array<float, 18> verticies;
	verticies = { (float)(transform.order[0]) * transform.size.x / 2.0f, (float)(transform.order[1]) * transform.size.y / 2.0f, 0,
				  (float)(transform.order[2]) * transform.size.x / 2.0f, (float)(transform.order[3]) * transform.size.y / 2.0f, 0,
				  (float)(transform.order[4]) * transform.size.x / 2.0f, (float)(transform.order[5]) * transform.size.y / 2.0f, 0,
				  (float)(transform.order[6]) * transform.size.x / 2.0f, (float)(transform.order[7]) * transform.size.y / 2.0f, 0,
				  (float)(transform.order[8]) * transform.size.x / 2.0f, (float)(transform.order[9]) * transform.size.y / 2.0f, 0,
				  (float)(transform.order[10]) * transform.size.x / 2.0f, (float)(transform.order[11]) * transform.size.y / 2.0f, 0 };

	mesh->SetMesh<18>(verticies);
	this->transform = transform;
}

TransformQuad* Quad::GetTransformQuad() {
	return &transform;
}

void Quad::DrawQuad() {
	mesh->DrawMesh();
}

void Quad::DrawInstacedQuad(int size) {
	mesh->DrawMeshInstance(size);
}

void Quad::SendCoords(const std::array<float, 12>& coords) {
	mesh->SetTextureCoords<12>(coords);
}

void Quad::UpdateQuad(Transform transform) {
	this->transform.pos = transform.pos;
	this->transform.rotation = vectorf3(transform.rotation.x, transform.rotation.y, 0);
}