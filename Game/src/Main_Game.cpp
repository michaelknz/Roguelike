#include "Main_Game.h"

Main_Game::Main_Game() {
	width = 800;
	height = 600;
	title = "Game";
	Set_Camera();
	Init_Entities();
}

Main_Game::~Main_Game() {
	Delete_Entities();
}

void Main_Game::Init_Entities() {
	display = new Display(width, height, title);
	player = new Player(camera);
	level = new Level(camera);
	timer = new Timer;
}

void Main_Game::Delete_Entities() {
	delete camera;
	delete player;
	delete level;
	delete display;
	delete timer;
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

			if (Event.type == SDL_KEYDOWN || Event.type == SDL_KEYUP) {
				player->Update_Move(Event);
			}
		}
		display->Clear_Screen(0.5f, 0.5f, 0.5f, 1.0f);
		level->Update();
		player->Move(timer->DelTime());
		InteractionPM::CollideWalls(player, level);
		player->Update();
		display->Swap();
	}
}