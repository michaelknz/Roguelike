#include "InteractionPM.h"
#include "Log.h"

vectori2 InteractionPM::collide_code = vectori2(0, 0);
bool InteractionPM::is_f = true;
vectori2 InteractionPM::room_move = vectori2();

InteractionPM::InteractionPM() {

}

InteractionPM::~InteractionPM() {

}

void InteractionPM::CollideWalls(Player* player, Room* room, vectorf2 del_pos) {

	vectorf2 pos_in_room_l = PosInRoom(player->transform.pos - vectorf2(player->size.x / 4.0f, 0.0f), room);
	vectorf2 pos_in_room_r = PosInRoom(player->transform.pos + vectorf2(player->size.x / 4.0f, 0.0f), room);
	vectorf2 pos_in_room_u = PosInRoom(player->transform.pos + vectorf2(0.0f, player->size.y / 4.0f), room);
	vectorf2 pos_in_room_d = PosInRoom(player->transform.pos - vectorf2(0.0f, player->size.y / 2.0f), room);

	vectori2 pos_in_room_quads_l((int)pos_in_room_l.x, (int)pos_in_room_l.y);
	vectori2 pos_in_room_quads_r((int)pos_in_room_r.x, (int)pos_in_room_r.y);
	vectori2 pos_in_room_quads_u((int)pos_in_room_u.x, (int)pos_in_room_u.y);
	vectori2 pos_in_room_quads_d((int)pos_in_room_d.x, (int)pos_in_room_d.y);

	bool flag_l = room->walls.find(room->tilemap_info.map[pos_in_room_quads_l.y * room->tilemap_info.size.x + pos_in_room_quads_l.x]) != room->walls.end();
	bool flag_r = room->walls.find(room->tilemap_info.map[pos_in_room_quads_r.y * room->tilemap_info.size.x + pos_in_room_quads_r.x]) != room->walls.end();
	bool flag_u = room->walls.find(room->tilemap_info.map[pos_in_room_quads_u.y * room->tilemap_info.size.x + pos_in_room_quads_u.x]) != room->walls.end();
	bool flag_d = room->walls.find(room->tilemap_info.map[pos_in_room_quads_d.y * room->tilemap_info.size.x + pos_in_room_quads_d.x]) != room->walls.end();

	if ((collide_code.x == -1 && del_pos.x < 0) || (collide_code.x == 1 && del_pos.x > 0)) {
		player->transform.pos.x -= del_pos.x;
		del_pos.x = 0;
	}

	if ((collide_code.y == -1 && del_pos.y > 0) || (collide_code.y == 1 && del_pos.y < 0)) {
		player->transform.pos.y -= del_pos.y;
		del_pos.y = 0;
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

vectorf2 InteractionPM::PosInRoom(vectorf2 pos, Room* room) {
	vectorf2 pos_in_room(pos.x - (room->tilemap_info.transform.pos.x - room->tilemap_info.transform.size.x / 2.0f), (room->tilemap_info.transform.pos.y + room->tilemap_info.transform.size.y / 2.0f) - pos.y);
	pos_in_room.x /= room->tilemap_info.transform.size.x;
	pos_in_room.y /= room->tilemap_info.transform.size.y;

	return pos_in_room;
}

void InteractionPM::InteractWithDoor(Player* player, Room* room, Camera* cam) {

	vectorf2 pos_in_room_l = PosInRoom(player->transform.pos - vectorf2(player->size.x / 4.0f, 0.0f), room);
	vectorf2 pos_in_room_r = PosInRoom(player->transform.pos + vectorf2(player->size.x / 4.0f, 0.0f), room);
	vectorf2 pos_in_room_u = PosInRoom(player->transform.pos + vectorf2(0.0f, player->size.y / 4.0f), room);
	vectorf2 pos_in_room_d = PosInRoom(player->transform.pos - vectorf2(0.0f, player->size.y / 2.0f), room);

	pos_in_room_l.x -= 0.5f;
	pos_in_room_r.x += 0.5f;
	pos_in_room_u.y -= 0.5f;
	pos_in_room_d.y += 0.5f;

	float player_del = 3.5f;

	bool f_state = Input::GetButtonState('f');
	if (!f_state) {
		is_f = true;
	}

	if (room->doors.find(room->tilemap_info.map[(int)pos_in_room_l.y * room->tilemap_info.size.x + (int)pos_in_room_l.x]) != room->doors.end()) {
		if (f_state && is_f) {
			is_f = false;
			cam->Move(vectori2(-1, 0), (float)room->tilemap_info.size.x * room->tilemap_info.transform.size.x);
			room_move = vectori2(-1, 0);
			player->transform.pos.x -= room->tilemap_info.transform.size.x * player_del;
		}
	}

	if (room->doors.find(room->tilemap_info.map[(int)pos_in_room_r.y * room->tilemap_info.size.x + (int)pos_in_room_r.x]) != room->doors.end()) {
		if (f_state && is_f) {
			is_f = false;
			cam->Move(vectori2(1, 0), (float)room->tilemap_info.size.x * room->tilemap_info.transform.size.x);
			room_move = vectori2(1, 0);
			player->transform.pos.x += room->tilemap_info.transform.size.x * player_del;
		}
	}

	if (room->doors.find(room->tilemap_info.map[(int)pos_in_room_u.y * room->tilemap_info.size.x + (int)pos_in_room_u.x]) != room->doors.end()) {
		if (f_state && is_f) {
			is_f = false;
			cam->Move(vectori2(0, 1), (float)room->tilemap_info.size.y * room->tilemap_info.transform.size.y);
			room_move = vectori2(0, 1);
			player->transform.pos.y += room->tilemap_info.transform.size.y * player_del;
		}
	}

	if (room->doors.find(room->tilemap_info.map[(int)pos_in_room_d.y * room->tilemap_info.size.x + (int)pos_in_room_d.x]) != room->doors.end()) {
		if (f_state && is_f) {
			is_f = false;
			cam->Move(vectori2(0, -1), (float)room->tilemap_info.size.y * room->tilemap_info.transform.size.y);
			room_move = vectori2(0, -1);
			player->transform.pos.y -= room->tilemap_info.transform.size.y * player_del;
		}
	}
}

vectori2 InteractionPM::GetRoomMove() {
	return room_move;
}

void InteractionPM::RoomMoveToZero() {
	room_move = vectori2();
}