#include "Level.h"
#include <queue>
#include <cstdlib>
#include <ctime>
#include "Random.h"

Level::Level(Camera* cam) {
	rooms_col = 5;
	camera = cam;
	cur_room = new Room(Transform(vectorf2(-1.8f, 1.2f)), cam, vectori2());
	rooms[(std::pair<int,int>)vectori2()] = cur_room;
	cur_room_coord.SetValue(0, 0);
	GenLevel();
}

Level::~Level() {
	delete cur_room;
}

Room* Level::GetCurRoom() {
	return cur_room;
}

void Level::SetCurRoom(vectori2 val) {
	cur_room = rooms[val];
	cur_room_coord = val;
}

void Level::GenLevel() {
	std::queue<vectori2> q;
	std::array<vectori2, 4> sides = { vectori2(-1, 0), vectori2(1, 0), vectori2(0, -1), vectori2(0, 1) };
	q.push((std::pair<int,int>)vectori2());
	srand(time(0));
	int cur_col = rooms_col - 1;
	while (true) {
		if (q.empty() && cur_col) {
			for (std::map<std::pair<int, int>, Room*>::iterator i = rooms.begin(); i != rooms.end(); ++i) {
				q.push(vectori2((*i).first));
			}
		}
		vectori2 cur_coord = q.front();
		q.pop();
		for (int i = 0; i < sides.size(); ++i) {
			if (rooms.find(cur_coord + sides[i]) == rooms.end()) {
				int tcol = 0;
				for (int j = 0; j < sides.size(); ++j) {
					tcol += rooms.find(cur_coord + sides[i] + sides[j]) != rooms.end();
				}

				if (tcol <= 1 && Random::GetRandomInt(0, 1) == 1) {
					rooms[cur_coord + sides[i]] = new Room(Transform(vectorf2(-1.8f, 1.2f)), camera, cur_coord + sides[i]);
					cur_col--;
					SetDoors(cur_coord, sides[i]);
				}

				if (cur_col <= 0) {
					goto exit;
				}
			}
		}
	}
exit:
	return;
}

void Level::SetDoors(vectori2 cur_c, vectori2 offset) {
	std::array<char, 7> tmp = { ' ', 'l', 'd', ' ', 'u', 'r', ' ' };
	rooms[cur_c]->SetDoor(tmp[offset.x * 2 + offset.y + 3]);
	rooms[cur_c + offset]->SetDoor(tmp[(offset * (-1)).x * 2 + (offset * (-1)).y + 3]);
}