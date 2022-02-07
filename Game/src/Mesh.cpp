#include "Mesh.h"


Mesh::Mesh() {

	glGenVertexArrays(1, &vao);
	glGenBuffers(1, &vbo);
	glGenBuffers(1, &vbo_texture);

}

Mesh::~Mesh() {
	glDeleteBuffers(1, &vbo);
	glGenBuffers(1, &vbo_texture);
	glDeleteVertexArrays(1, &vao);
}

void Mesh::DrawMesh() {
	glBindVertexArray(vao);
	glDrawArrays(GL_TRIANGLES, 0, Count);
	glBindVertexArray(0);
}

void Mesh::DrawMeshInstance(int size) {
	glBindVertexArray(vao);
	glDrawArraysInstanced(GL_TRIANGLES, 0, Count, size);
	glBindVertexArray(0);
}