#ifndef QUAD_H
#define QUAD_H

#include "Mesh.h"
#include "Math.h"
#include <array>
#include "Struct.h"

class Quad {
public:
	Quad();
	~Quad();
	void SendVertices(const TransformQuad& transform);
	void SendCoords(const std::array<float, 12>& coords);
	void DrawQuad();
	void DrawInstacedQuad(int size);
	TransformQuad* GetTransformQuad();
	void UpdateQuad(Transform transform);
private:
	Mesh* mesh;
	TransformQuad transform;
};

#endif