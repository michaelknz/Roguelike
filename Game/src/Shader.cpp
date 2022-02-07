#include "Shader.h"

Shader::Shader(const std::string& shader_name) {
	prog = glCreateProgram();
	shaders[0] = Create_Shader(read_shader("shaders/" + shader_name + ".vs"), GL_VERTEX_SHADER);
	shaders[1] = Create_Shader(read_shader("shaders/" + shader_name + ".fs"), GL_FRAGMENT_SHADER);
	for (int i = 0; i < 2; ++i) {
		glAttachShader(prog, shaders[i]);
	}
	glLinkProgram(prog);

	GLint loglen;
	glGetProgramiv(prog, GL_INFO_LOG_LENGTH, &loglen);
	if (loglen > 0) {
		char* log = new char[loglen];
		GLsizei writen;
		glGetProgramInfoLog(prog, loglen, &writen, log);
		printf("%s\n", log);
		delete[] log;
	}
}

Shader::~Shader() {
	for (int i = 0; i < 2; ++i) {
		glDetachShader(prog, shaders[i]);
		glDeleteShader(shaders[i]);
	}
	glDeleteProgram(prog);
}

void Shader::bind() {
	glUseProgram(prog);
}

void Shader::unbind() {
	glUseProgram(0);
}

std::string Shader::read_shader(const std::string& shader_name) {
	std::ifstream file;
	file.open(shader_name.c_str());
	std::string out;
	while (file.good()) {
		std::string line;
		std::getline(file, line);
		out += line + "\n";
	}
	file.close();
	return out;
}

GLuint Shader::Create_Shader(const std::string& text, GLuint type) {
	GLuint shader = glCreateShader(type);
	const char* p[1];
	int l[1];
	p[0] = text.c_str();
	l[0] = text.size();
	glShaderSource(shader, 1, p, l);
	glCompileShader(shader);
	return shader;
}

void Shader::SendVectorf3(vectorf3 vec, const std::string& name) {
	bind();
	glUniform3f(glGetUniformLocation(prog, name.c_str()), vec.x, vec.y, vec.z);
	unbind();
}

void Shader::SendMatrixf4x4(matf4x4 mat, const std::string& name) {
	bind();
	glUniformMatrix4fv(glGetUniformLocation(prog, name.c_str()), 1, GL_TRUE, mat.mas);
	unbind();
}

void Shader::Sendi1(int val, const std::string& name) {
	bind();
	glUniform1i(glGetUniformLocation(prog, name.c_str()), val);
	unbind();
}

void Shader::SendVectorf2(vectorf2 vec, const std::string& name) {
	bind();
	glUniform2f(glGetUniformLocation(prog, name.c_str()), vec.x, vec.y);
	unbind();
}

void Shader::Sendf1(float val, const std::string& name) {
	bind();
	glUniform1f(glGetUniformLocation(prog, name.c_str()), val);
	unbind();
}