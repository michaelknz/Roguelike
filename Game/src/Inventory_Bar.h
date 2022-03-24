#ifndef INVENTORY_H
#define INVENTORY_H

#include "TileMap.h"
#include "Input.h"

class Inventory_Bar {
public:
	Inventory_Bar(float aspect, const InvectoryBarInfo& inv_bar_info);
	~Inventory_Bar();
	void Update();
private:
	TileMap* SmallTileMap;
	void SetCamera(float aspect);
	void SetTileMap(const InvectoryBarInfo& inv_bar_info);
	void Draw();
	void MoveActiveBar();
	int last_wheel_pos;
	int active_index;
	int size_sm_tilemap;
	Camera* camera;
};

#endif