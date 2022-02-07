#include "Texture.h"

Texture::Texture(const TextureStruct& texture_info) {
	Set_Texture(texture_info.name);
	Init(texture_info.st_pos, texture_info.size);
}

Texture::~Texture() {
	glDeleteTextures(1, &texture);
}

void Texture::Set_Texture(const std::string& texture_name) {
	glGenTextures(1, &texture);
	glBindTexture(GL_TEXTURE_2D, texture);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	int channels;
	image = SOIL_load_image(texture_name.c_str(), &weight, &height, &channels, SOIL_LOAD_RGBA);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, weight, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, image);
	glGenerateTextureMipmap(GL_TEXTURE_2D);
	SOIL_free_image_data(image);
	glBindTexture(GL_TEXTURE_2D, 0);
}

void Texture::Init(vectori2 start_pos, vectori2 size) {
	this->start_pos.x = (float)start_pos.x / (float)weight;
	this->start_pos.y = (float)start_pos.y / (float)height;
	this->size.x = (float)size.x / (float)weight;
	this->size.y = (float)size.y / (float)height;
}

void Texture::Send_Coords(Quad* quad, const TransformQuad& transform) {
	std::array<float, 12> coords;
	coords = { start_pos.x + (float)(transform.order[0] + 1) * size.x / 2.0f, start_pos.y + (float)(transform.order[1] + 1) * size.y / 2.0f,
			start_pos.x + (float)(transform.order[2] + 1) * size.x / 2.0f, start_pos.y + (float)(transform.order[3] + 1) * size.y / 2.0f,
			start_pos.x + (float)(transform.order[4] + 1) * size.x / 2.0f, start_pos.y + (float)(transform.order[5] + 1) * size.y / 2.0f,
			start_pos.x + (float)(transform.order[6] + 1) * size.x / 2.0f, start_pos.y + (float)(transform.order[7] + 1) * size.y / 2.0f,
			start_pos.x + (float)(transform.order[8] + 1) * size.x / 2.0f, start_pos.y + (float)(transform.order[9] + 1) * size.y / 2.0f,
			start_pos.x + (float)(transform.order[10] + 1) * size.x / 2.0f, start_pos.y + (float)(transform.order[11] + 1) * size.y / 2.0f };
	quad->SendCoords(coords);
}

void Texture::bind() {
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, texture);
}

void Texture::unbind() {
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, 0);
}

vectorf2 Texture::FromPixelsToCoords(vectori2 pix) {
	return vectorf2((float)pix.x / (float)weight, (float)pix.y / (float)height);
}

vectorf2 Texture::GetSize() {
	return size;
}