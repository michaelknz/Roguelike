#include "Renderer.h"

Renderer::Renderer(const TransformQuad& transform, const TextureStruct& texture_info) {
	shader = new Shader(transform.shader_name);
	quad = new Quad;
	texture = nullptr;
	SetTexture(texture_info, transform);
	SetQuad(transform);
}

Renderer::~Renderer() {
	delete shader;
	delete quad;
	if (texture != nullptr) {
		delete texture;
	}
}

void Renderer::Draw(const TransformQuad& transform) {
	SendMVP(transform);
	BindAll();
	quad->DrawQuad();
	UnbindAll();
}

void Renderer::DrawInstance(const TransformQuad& transform, int size) {
	SendMVP(transform);
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

void Renderer::SendMVP(const TransformQuad& transform) {
	matf4x4 model;
	model.Init();
	MatrixOp::simple_rotate(model, transform.rotation);
	MatrixOp::translate(model, vectorf3(transform.pos.x, transform.pos.y, transform.z));
	SendMatrixf4x4(camera->GetVP() * model, "mvp");
}

void Renderer::BindAll() {
	shader->bind();
	texture->bind();
}

void Renderer::UnbindAll() {
	texture->unbind();
	shader->unbind();
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
