#include "Input.h"


Input::Input() {
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

Input::~Input() {

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

bool Input::GetButtonState(char but) {
	return buffer[kmbuttons[but]];
}