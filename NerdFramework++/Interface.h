#pragma once

#include <chrono>
#include <vector>
#include <SDL.h>
#include "Image4.h"
#include "Frame.h"

class Interface
{
private:
	std::chrono::steady_clock::time_point _created;
	std::chrono::steady_clock::time_point _lastFrame;
	SDL_Renderer* _renderer;
	SDL_Texture* _texture;
	int _width;
	int _height;
public:
	SDL_Window* window;

	Image4 screen;
	Frame frame;

	std::function<void(Interface&, double)> onUpdate;

	Interface();
	Interface(SDL_Window* window);
	Interface(SDL_Window* window, const std::vector<UIObject*>& scene);
	Interface(const std::vector<UIObject*>& scene);
	~Interface();

	double secondsElapsed() const;
	
	void update();
	void draw();
	void drawSDL();
};

