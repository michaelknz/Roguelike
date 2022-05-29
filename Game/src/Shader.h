#ifndef SHADER_H
#define SHADER_H

#include <glew.h>
#include <string>
#include <fstream>
#include "Math.h"

class Shader {
public:
	Shader(const std::string& shader_name, bool is_gs);
	~Shader();
	void bind();
	void unbind();
	void SendVectorf3(vectorf3 vec, const std::string& name);
	void SendVectorf2(vectorf2 vec, const std::string& name);
	void SendMatrixf4x4(matf4x4 mat, const std::string& name);
	void Sendi1(int val, const std::string& name);
	void Sendf1(float val, const std::string& name);
private:
	std::string read_shader(const std::string& shader_name);
	GLuint Create_Shader(const std::string& text, GLuint type);
	GLuint shaders[3];
	GLuint prog;
	bool is_gs;
};

#endif
