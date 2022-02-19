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
};

struct TextureStruct {
	std::string name;
	vectori2 size;
	vectori2 st_pos;
};

struct TileMapStruct {
	TextureStruct texture;
	TransformQuad transform;
	vectori2 size;
	std::map<char, vectori2> elem;
	std::string map;
};

struct CharSpec {
	int max_life;
	int cur_life;
	float speed;
	float anim_speed;
};

struct LifeBarHeartsStruct {
	TransformQuad transform;
	TextureStruct texture;
	int max_life;
	int prev_life;
	std::array<vectori2, 3> texture_pos;
};

#endif