#ifndef RENDERER_H
#define RENDERER_H

#include "Shader.h"
#include "Quad.h"
#include "Camera.h"
#include "Texture.h"
#include <string>
#include <array>
#include "Struct.h"

class Renderer {
public:
	Renderer(const TransformQuad& transform, const TextureStruct& texture_info, Camera* cam);
	Renderer(const TransformQuad& transform, Camera* cam);
	~Renderer();
	void SetQuad(const TransformQuad& transform);
	void Draw(Transform transform);
	void DrawInstance(Transform transform, int size);
	void SendVectorf3(vectorf3 vec, const std::string& name);
	void SendVecotrf2(vectorf2 vec, const std::string& name);
	void SendMatrixf4x4(matf4x4 mat, const std::string& name);
	vectorf2 FromPixelsToCoords(vectori2 pix);
	void Sendi1(int val, const std::string& name);
	void Sendf1(float val, const std::string& name);
	void SetTexture(const TextureStruct& texture_info, const TransformQuad& transform);
private:
	void SetCamera(Camera* cam);
	void SendMVP(const TransformQuad* transform);
	void BindAll();
	void UnbindAll();
	Shader* shader;
	Quad* quad;
	Camera* camera;
	Texture* texture;
};

#endif