#include "Life_Bar.h"

Life_Bar::Life_Bar(float aspect, const LifeBarHeartsStruct& life_struct) {
	this->aspect = aspect;
	this->life_info.max_life = life_struct.max_life;
	life_info.prev_life = life_info.max_life;
	this->life_info.transform = life_struct.transform;
	this->life_info.texture = life_struct.texture;
	for (int i = 0; i < 3; ++i) {
		this->life_info.texture_pos[i] = life_struct.texture_pos[i];
	}
	for (int i = 0; i < life_struct.transform.order.size(); ++i) {
		this->life_info.transform.order[i] = life_struct.transform.order[i];
	}
	SetCamera();
	life_heards = nullptr;
	SetLifeHeards();
}

Life_Bar::~Life_Bar() {
	if (life_heards != nullptr) {
		delete life_heards;
	}
	delete camera;
}

void Life_Bar::SetLifeHeards() {
	TileMapStruct tilemap_info;
	tilemap_info.transform.pos = life_info.transform.pos;
	tilemap_info.transform.rotation = life_info.transform.rotation;

	for (int i = 0; i < life_info.transform.order.size(); ++i) {
		tilemap_info.transform.order[i] = life_info.transform.order[i];
	}

	tilemap_info.transform.shader_name = life_info.transform.shader_name;
	tilemap_info.transform.z = life_info.transform.z;
	tilemap_info.transform.size = life_info.transform.size;
	tilemap_info.map = std::string(life_info.max_life / 2, 'F');

	if (life_info.max_life % 2) {
		tilemap_info.map += "H";
	}

	tilemap_info.elem['F'] = life_info.texture_pos[0];
	tilemap_info.elem['H'] = life_info.texture_pos[1];
	tilemap_info.elem['E'] = life_info.texture_pos[2];

	tilemap_info.texture = life_info.texture;
	tilemap_info.size = vectori2(tilemap_info.map.size(), 1);
	life_heards = new TileMap(tilemap_info);
	life_heards->SetCamera(camera);
}

void Life_Bar::Update(int player_life) {
	int del_time = player_life - life_info.prev_life;
	if (del_time < 0) {
		del_time = abs(del_time);
		int index = life_info.prev_life / 2 + life_info.prev_life % 2 - 1;
		while (del_time > 0) {
			int tmp = std::min(del_time, life_info.prev_life % 2 + ((life_info.prev_life + 1) % 2) * 2);
			del_time -= tmp;
			life_info.prev_life -= tmp;
			life_heards->SetMapElem(index, (char)(life_info.prev_life % 2 * (int)'H' + ((life_info.prev_life + 1) % 2) * (int)'E'));
			--index;
		}
	}

	else {
		int index = life_info.prev_life / 2 + life_info.prev_life % 2 - 1;
		while (del_time > 0) {
			int tmp = std::min(del_time, life_info.prev_life % 2 + ((life_info.prev_life + 1) % 2) * 2);
			del_time -= tmp;
			life_info.prev_life += tmp;
			life_heards->SetMapElem(index, (char)(life_info.prev_life % 2 * 'H' + (life_info.prev_life + 1) % 2 * 'F'));
			++index;
		}
	}

	life_heards->Draw();
}

void Life_Bar::SetCamera() {
	camera = new Camera(vectorf3(), vectorf3(), 90.0f, 0.1f, 100.0f, aspect);
}