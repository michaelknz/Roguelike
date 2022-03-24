#include "Input.h"

std::map<char, int> Input::kmbuttons;
std::map<int, char> Input::sdl_to_but;
std::vector<bool> Input::buffer;
int Input::wheel_move_y = 0;


Input::Input() {
	
}

Input::~Input() {

}

void Input::Init() {
	kmbuttons['w'] = 0;
	kmbuttons['a'] = 1;
	kmbuttons['s'] = 2;
	kmbuttons['d'] = 3;
	kmbuttons['f'] = 4;

	sdl_to_but[SDLK_w] = 'w';
	sdl_to_but[SDLK_a] = 'a';
	sdl_to_but[SDLK_s] = 's';
	sdl_to_but[SDLK_d] = 'd';
	sdl_to_but[SDLK_f] = 'f';

	buffer.resize(kmbuttons.size());
	for (int i = 0; i < buffer.size(); ++i) {
		buffer[i] = false;
	}
}

void Input::Update(const SDL_Event& event) {
	Update_Keyboard(event);
	Update_MouseWheel(event);
}

void Input::Update_Keyboard(const SDL_Event& event) {
	if (event.type == SDL_KEYDOWN) {
		if (sdl_to_but.find(event.key.keysym.sym) != sdl_to_but.end()) {
			buffer[kmbuttons[sdl_to_but[event.key.keysym.sym]]] = true;
		}
	}

	if (event.type == SDL_KEYUP) {
		if (sdl_to_but.find(event.key.keysym.sym) != sdl_to_but.end()) {
			buffer[kmbuttons[sdl_to_but[event.key.keysym.sym]]] = false;
		}
	}
}

void Input::Update_MouseWheel(const SDL_Event& event) {
	if (event.type == SDL_MOUSEWHEEL) {
		wheel_move_y += event.wheel.y;
		if (event.wheel.y == 0) {
			wheel_move_y = 0;
		}
	}
}

bool Input::GetButtonState(char but) {
	return buffer[kmbuttons[but]];
}

int Input::GetWheelState() {
	return wheel_move_y;
}