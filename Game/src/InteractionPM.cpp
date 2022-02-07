#include "InteractionPM.h"

vectori2 InteractionPM::collide_code = vectori2(0, 0);

InteractionPM::InteractionPM() {

}

InteractionPM::~InteractionPM() {

}

void InteractionPM::CollideWalls(Player* player, Level* level) {
	Room* room = level->GetCurRoom();
	vectorf2 pos_in_room_l(player->transform.pos.x - (room->tilemap_info.transform.pos.x - room->tilemap_info.transform.size.x / 2.0f) - player->transform.size.x / 4.0f, (room->tilemap_info.transform.pos.y + room->tilemap_info.transform.size.y / 2.0f) - player->transform.pos.y);
	vectorf2 pos_in_room_r(player->transform.pos.x - (room->tilemap_info.transform.pos.x - room->tilemap_info.transform.size.x / 2.0f) + player->transform.size.x / 4.0f, (room->tilemap_info.transform.pos.y + room->tilemap_info.transform.size.y / 2.0f) - player->transform.pos.y);
	vectorf2 pos_in_room_u(player->transform.pos.x - (room->tilemap_info.transform.pos.x - room->tilemap_info.transform.size.x / 2.0f), (room->tilemap_info.transform.pos.y + room->tilemap_info.transform.size.y / 2.0f) - player->transform.pos.y - player->transform.size.y / 4.0f);
	vectorf2 pos_in_room_d(player->transform.pos.x - (room->tilemap_info.transform.pos.x - room->tilemap_info.transform.size.x / 2.0f), (room->tilemap_info.transform.pos.y + room->tilemap_info.transform.size.y / 2.0f) - player->transform.pos.y + player->transform.size.y / 2.0f);
	pos_in_room_l.x /= room->tilemap_info.transform.size.x;
	pos_in_room_l.y /= room->tilemap_info.transform.size.y;
	pos_in_room_r.x /= room->tilemap_info.transform.size.x;
	pos_in_room_r.y /= room->tilemap_info.transform.size.y;
	pos_in_room_u.x /= room->tilemap_info.transform.size.x;
	pos_in_room_u.y /= room->tilemap_info.transform.size.y;
	pos_in_room_d.x /= room->tilemap_info.transform.size.x;
	pos_in_room_d.y /= room->tilemap_info.transform.size.y;
	vectori2 pos_in_room_quads_l((int)pos_in_room_l.x, (int)pos_in_room_l.y);
	vectori2 pos_in_room_quads_r((int)pos_in_room_r.x, (int)pos_in_room_r.y);
	vectori2 pos_in_room_quads_u((int)pos_in_room_u.x, (int)pos_in_room_u.y);
	vectori2 pos_in_room_quads_d((int)pos_in_room_d.x, (int)pos_in_room_d.y);
	bool flag_l = room->walls.find(room->tilemap_info.map[pos_in_room_quads_l.y * room->tilemap_info.size.x + pos_in_room_quads_l.x]) != room->walls.end();
	bool flag_r = room->walls.find(room->tilemap_info.map[pos_in_room_quads_r.y * room->tilemap_info.size.x + pos_in_room_quads_r.x]) != room->walls.end();
	bool flag_u = room->walls.find(room->tilemap_info.map[pos_in_room_quads_u.y * room->tilemap_info.size.x + pos_in_room_quads_u.x]) != room->walls.end();
	bool flag_d = room->walls.find(room->tilemap_info.map[pos_in_room_quads_d.y * room->tilemap_info.size.x + pos_in_room_quads_d.x]) != room->walls.end();

	if ((collide_code.x == -1 && player->del_pos.x < 0) || (collide_code.x == 1 && player->del_pos.x > 0)) {
		player->transform.pos.x -= player->del_pos.x;
		player->del_pos.x = 0;
	}

	if ((collide_code.y == -1 && player->del_pos.y > 0) || (collide_code.y == 1 && player->del_pos.y < 0)) {
		player->transform.pos.y -= player->del_pos.y;
		player->del_pos.y = 0;
	}

	if (flag_l && collide_code.x != -1) {
		player->transform.pos.x += (1.0f - (pos_in_room_l.x - (float)((int)pos_in_room_l.x))) * room->tilemap_info.transform.size.x;
		collide_code.x = -1;
	}

	if (flag_r && collide_code.x != 1) {
		player->transform.pos.x -= (pos_in_room_r.x - (float)((int)pos_in_room_r.x)) * room->tilemap_info.transform.size.x;
		collide_code.x = 1;
	}

	if (!flag_l && !flag_r) {
		collide_code.x = 0;
	}

	if (flag_u && collide_code.y != -1) {
		player->transform.pos.y -= (1.0f - (pos_in_room_u.y - (float)((int)pos_in_room_u.y))) * room->tilemap_info.transform.size.y;
		collide_code.y = -1;
	}

	if (flag_d && collide_code.y != 1) {
		player->transform.pos.y += (pos_in_room_d.y - (float)((int)pos_in_room_d.y)) * room->tilemap_info.transform.size.y;
		collide_code.y = 1;
	}

	if (!flag_d && !flag_u) {
		collide_code.y = 0;
	}
}