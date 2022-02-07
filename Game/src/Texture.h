#ifndef TEXTURE_H
#define TEXTURE_H

#include <SOIL.h>
#include "Quad.h"
#include <string>
#include <glew.h>
#include <map>
#include "Shader.h"
#include "Math.h"
#include "Struct.h"

class Texture {
public:
	Texture(const TextureStruct& texture_info);
	~Texture();
	void Set_Texture(const std::string& texture_name);
	void Send_Coords(Quad* quad, const TransformQuad& transform);
	vectorf2 FromPixelsToCoords(vectori2 pix);
	vectorf2 GetSize();
	void bind();
	void unbind();
private:
	void Init(vectori2 start_pos, vectori2 size);
	GLuint texture;
	unsigned char* image;
	int weight, height;
	vectorf2 start_pos;
	vectorf2 size;
};

#endif