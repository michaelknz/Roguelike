#ifndef STRUCT_H
#define STRUCT_H

#include "Math.h"
#include <array>
#include <string>
#include <map>

struct TransformQuad {
	vectorf2 pos;
	vectorf2 size;
	vectorf3 rotation;
	std::array<int, 12> order;
	std::string shader_name;
	float z;
	bool is_gs;
	TransformQuad();
};

struct Transform {
	vectorf2 pos;
	vectorf2 rotation;
	Transform(vectorf2 pos);
	Transform();
};

struct TextureStruct {
	std::string name;
	vectori2 size;
	vectori2 st_pos;
	TextureStruct();
};

struct TileMapStruct {
	TextureStruct texture;
	TransformQuad transform;
	vectori2 size;
	std::map<char, vectori2> elem;
	std::string map;
	TileMapStruct();
};

struct CharSpec {
	int max_life;
	int cur_life;
	float speed;
	float anim_speed;
	CharSpec();
};

struct LifeBarHeartsStruct {
	TransformQuad transform;
	TextureStruct texture;
	int max_life;
	int prev_life;
	std::array<vectori2, 3> texture_pos;
	LifeBarHeartsStruct();
};

struct InvectoryBarInfo {
	TextureStruct texture;
	std::array<vectori2, 2> texture_pos;
	vectori2 size;
	vectorf2 pos;
	InvectoryBarInfo();
};

#endif