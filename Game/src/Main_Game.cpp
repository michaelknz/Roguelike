#include "Main_Game.h"
#include "InteractionPM.h"

Main_Game::Main_Game() {
	width = 1280;
	height = 960;
	title = "Game";
	Set_Camera();
	Init_Entities();
}

Main_Game::~Main_Game() {
	Delete_Entities();
}

void Main_Game::Init_Entities() {
	display = new Display(width, height, title);
	player = new Player(Transform(vectorf2()), camera);
	level = new Level(camera);
	scene = Scene::getInstance();
	SetScene();
	Input::Init();
}

void Main_Game::Delete_Entities() {
	delete camera;
	delete player;
	delete level;
	delete display;
	Scene::deleteInstance();
}

void Main_Game::Set_Camera() {
	camera = new Camera(vectorf3(0.0f, 0.0f, -0.5f), vectorf3(0.0f, 0.0f, 0.0f), 90.0f, 0.1f, 100.0f, (float)width / (float)height);
}

void Main_Game::Main_Loop() {
	SDL_Event Event;
	while (true) {
		if (SDL_PollEvent(&Event)) {
			if (Event.type == SDL_QUIT) {
				break;
			}

			if (Event.type == SDL_KEYDOWN || Event.type == SDL_KEYUP || Event.type == SDL_MOUSEWHEEL) {
				Input::Update(Event);
			}
		}
		display->Clear_Screen(0.0f, 0.0f, 0.0f, 1.0f);
		scene->UpdateAllEntities();
		UpdateScene();
		display->Swap();
	}
}

void Main_Game::UpdateScene() {
	vectori2 room_move = InteractionPM::GetRoomMove();
	if (room_move.x != 0 || room_move.y != 0) {
		scene->Clear_Scene();
		level->SetCurRoom(level->GetCurRoom()->GetCoord() + room_move);
		scene->AddEntity(level->GetCurRoom());
		scene->AddEntity(player);
		player->SetCurRoom();
		InteractionPM::RoomMoveToZero();
	}
}

void Main_Game::SetScene() {
	scene->Clear_Scene();
	scene->AddEntity(level->GetCurRoom());
	scene->AddEntity(player);
	player->SetCurRoom();
	InteractionPM::RoomMoveToZero();
}