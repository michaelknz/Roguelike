#ifndef MAIN_GAME_H
#define MAIN_GAME_H

#include "Display.h"
#include "Player.h"
#include "Camera.h"
#include "Timer.h"
#include "Level.h"
#include "InteractionPM.h"

class Main_Game {
public:
	Main_Game();
	~Main_Game();
	void Main_Loop();
private:
	void Init_Entities();
	void Delete_Entities();
	void Set_Camera();
	Display* display;
	Player* player;
	Level* level;
	Camera* camera;
	Timer* timer;
	int width;
	int height;
	std::string title;
};

#endif