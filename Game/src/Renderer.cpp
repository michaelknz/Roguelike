#include "Renderer.h"

Renderer::Renderer(const TransformQuad& transform, const TextureStruct& texture_info, Camera* cam) {
	shader = new Shader(transform.shader_name, transform.is_gs);
	quad = new Quad;
	texture = nullptr;
	SetTexture(texture_info, transform);
	SetQuad(transform);
	SetCamera(cam);
}

Renderer::Renderer(const TransformQuad& transform, Camera* cam) {
	shader = new Shader(transform.shader_name, transform.is_gs);
	quad = new Quad;
	texture = nullptr;
	SetQuad(transform);
	SetCamera(cam);
}

Renderer::~Renderer() {
	delete shader;
	delete quad;
	if (texture != nullptr) {
		delete texture;
	}
}

void Renderer::Draw(Transform transform) {
	quad->UpdateQuad(transform);
	SendMVP(quad->GetTransformQuad());
	BindAll();
	quad->DrawQuad();
	UnbindAll();
}

void Renderer::DrawInstance(Transform transform, int size) {
	quad->UpdateQuad(transform);
	SendMVP(quad->GetTransformQuad());
	BindAll();
	quad->DrawInstacedQuad(size);
	UnbindAll();
}

void Renderer::SendVectorf3(vectorf3 vec, const std::string& name) {
	shader->SendVectorf3(vec, name);
}

void Renderer::SendVecotrf2(vectorf2 vec, const std::string& name) {
	shader->SendVectorf2(vec, name);
}

void Renderer::SendMatrixf4x4(matf4x4 mat, const std::string& name) {
	shader->SendMatrixf4x4(mat, name);
}

void Renderer::Sendi1(int val, const std::string& name) {
	shader->Sendi1(val, name);
}

void Renderer::SetCamera(Camera* cam) {
	camera = cam;
}

void Renderer::SetTexture(const TextureStruct& texture_info, const TransformQuad& transform) {
	if (texture != nullptr) {
		delete texture;
	}
	texture = new Texture(texture_info);
	texture->Send_Coords(quad, transform);
	shader->Sendi1(0, "Texture");
}

void Renderer::SendMVP(const TransformQuad* transform) {
	matf4x4 model;
	model.Init();
	MatrixOp::simple_rotate(model, transform->rotation);
	MatrixOp::translate(model, vectorf3(transform->pos.x, transform->pos.y, transform->z));
	SendMatrixf4x4(camera->GetVP() * model, "mvp");
}

void Renderer::BindAll() {
	shader->bind();
	if (texture != nullptr) {
		texture->bind();
	}
}

void Renderer::UnbindAll() {
	texture->unbind();
	if (texture != nullptr) {
		shader->unbind();
	}
}

void Renderer::SetQuad(const TransformQuad& transform) {
	quad->SendVertices(transform);
}

vectorf2 Renderer::FromPixelsToCoords(vectori2 pix) {
	return texture->FromPixelsToCoords(pix);
}

void Renderer::Sendf1(float val, const std::string& name) {
	shader->Sendf1(val, name);
}
