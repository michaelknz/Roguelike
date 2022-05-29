#ifndef MESH_H
#define MESH_H

#include <glew.h>
#include <array>

class Mesh {
public:
	Mesh();
	~Mesh();
	template<int T>
	void SetMesh(std::array<float, T> vertices) {

		glBindVertexArray(vao);

		glBindBuffer(GL_ARRAY_BUFFER, vbo);

		Count = vertices.size();

		glBufferData(GL_ARRAY_BUFFER, Count * sizeof(float), &vertices[0], GL_STATIC_DRAW);

		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (GLvoid*)(0));
		glEnableVertexAttribArray(0);

		glBindVertexArray(0);

	}
	template<int T>
	void SetTextureCoords(std::array<float, T> coords) {
		glBindVertexArray(vao);

		glBindBuffer(GL_ARRAY_BUFFER, vbo_texture);

		tex_count = coords.size();

		glBufferData(GL_ARRAY_BUFFER, coords.size() * sizeof(float), &coords[0], GL_STATIC_DRAW);

		glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(float), (GLvoid*)(0));
		glEnableVertexAttribArray(1);

		glBindVertexArray(0);
	}
	void DrawMesh();
	void DrawMeshInstance(int size);
private:
	GLuint vao;
	GLuint vbo;
	GLuint vbo_texture;
	unsigned int Count;
	unsigned int tex_count;
};

#endif