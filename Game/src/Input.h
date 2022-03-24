#ifndef INPUT_H
#define INPUT_H

#include <map>
#include <SDL.h>
#include <vector>

class Input {
public:
	Input();
	~Input();
	static void Update(const SDL_Event& event);
	static bool GetButtonState(char but);
	static int GetWheelState();
	static void Init();
private:
	static void Update_Keyboard(const SDL_Event& event);
	static void Update_MouseWheel(const SDL_Event& event);
	static std::map<char, int> kmbuttons;
	static std::map<int, char> sdl_to_but;
	static std::vector<bool> buffer;
	static int wheel_move_y;
};

#endif