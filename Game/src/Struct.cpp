#include "Struct.h"

Transform::Transform(vectorf2 pos) {
	this->pos = pos;
	rotation = vectorf2(0, 0);
}

Transform::Transform() {
	pos = vectorf2();
	rotation = vectorf2();
}

TransformQuad::TransformQuad() {
	size = vectorf2();
	pos = vectorf2();
	rotation = vectorf3();
	shader_name = "DefaultShader";
	order = { -1, -1,
			  -1,  1,
			   1,  1,
			  -1, -1,
			   1,  1,
			   1, -1 };
	z = 0;
	is_gs = false;
}

TextureStruct::TextureStruct() {
	name = "";
	size = vectori2();
	st_pos = vectori2();
}

TileMapStruct::TileMapStruct() {
	transform.shader_name = "TileMapShader";
	size = vectori2();

}

CharSpec::CharSpec() {
	max_life = 0;
	cur_life = 0;
	speed = 0;
	anim_speed = 0;
}

LifeBarHeartsStruct::LifeBarHeartsStruct() {
	transform.shader_name = "TileMapShader";
	max_life = 0;
	prev_life = 0;
}

InvectoryBarInfo::InvectoryBarInfo() {
	size = vectori2();
	pos = vectorf2();
}