#ifndef INPUT_H
#define INPUT_H

#include <map>
#include <SDL.h>
#include <vector>

class Input {
public:
	Input();
	~Input();
	void Update_Keyboard(const SDL_Event& event);
	bool GetButtonState(char but);
private:
	std::map<char, int> kmbuttons;
	std::map<int, char> sdl_to_but;
	std::vector<bool> buffer;
};

#endif