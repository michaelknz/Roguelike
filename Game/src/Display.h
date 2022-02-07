#ifndef DISPLAY_H
#define DISPLAY_H

#include <SDL.h>
#include <glew.h>
#include <string>

class Display {
public:
	Display(unsigned int width, unsigned int height, const std::string& title);
	~Display();

	void Clear_Screen(float r, float g, float b, float a);
	void Swap();
private:
	SDL_Window* window;
	SDL_GLContext context;
};

#endif