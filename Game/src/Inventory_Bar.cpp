#include "Inventory_Bar.h"

Inventory_Bar::Inventory_Bar(float aspect, const InvectoryBarInfo& inv_bar_info) {
	
	last_wheel_pos = 0;
	active_index = 0;
	size_sm_tilemap = 0;
	SetCamera(aspect);
	SetTileMap(inv_bar_info);
}

Inventory_Bar::~Inventory_Bar() {
	delete camera;
	delete SmallTileMap;
}

void Inventory_Bar::SetCamera(float aspect) {
	camera = new Camera(vectorf3(), vectorf3(), 90.0f, 0.1f, 100.0f, aspect);
}

void Inventory_Bar::SetTileMap(const InvectoryBarInfo& inv_bar_info) {
	TileMapStruct info;

	info.transform.pos = inv_bar_info.pos;
	pos = inv_bar_info.pos;
	info.transform.rotation = vectorf3();
	info.transform.order = { -1, -1,
							-1,  1,
							 1,  1,
							-1, -1,
							 1,  1,
							 1, -1 };
	info.transform.shader_name = "TileMapShader";
	info.transform.size = vectorf2(0.12f, 0.12f);
	info.transform.z = 0;
	info.size = inv_bar_info.size;
	size_sm_tilemap = info.size.x * info.size.y;
	info.map = "";
	info.texture = inv_bar_info.texture;
	info.elem['A'] = inv_bar_info.texture_pos[1];
	info.elem['U'] = inv_bar_info.texture_pos[0];
	for (int i = 0; i < info.size.x * info.size.y; ++i) {
		info.map += "U";
	}
	info.map[0] = 'A';
	SmallTileMap = new TileMap(info, camera);
}

void Inventory_Bar::Draw() {
	SmallTileMap->Draw(Transform(pos));
}

void Inventory_Bar::MoveActiveBar() {
	int tmp = Input::GetWheelState();
	if (tmp == 0) {
		last_wheel_pos = 0;
	}
	else if (tmp - last_wheel_pos) {
		SmallTileMap->SetMapElem(active_index, 'U');
		active_index += tmp - last_wheel_pos;
		active_index = (active_index + size_sm_tilemap) % size_sm_tilemap;
		SmallTileMap->SetMapElem(active_index, 'A');
		last_wheel_pos = tmp;
	}
}

void Inventory_Bar::Update() {
	MoveActiveBar();
	Draw();
}