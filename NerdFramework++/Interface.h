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
	std::function<void(Interface&, Image4&, const Rect2<double>&)> onDraw;
	std::function<void(Interface&, SDL_Renderer*, const Rect2<double>&)> onDrawSDL;

	Interface(std::function<void(Interface&, SDL_Renderer*)> onInit = [](Interface& interface, SDL_Renderer* renderer) -> void {});
	Interface(SDL_Window* window, std::function<void(Interface&, SDL_Renderer*)> onInit = [](Interface& interface, SDL_Renderer* renderer) -> void {});
	Interface(SDL_Window* window, const std::vector<UIObject*>& scene, std::function<void(Interface&, SDL_Renderer*)> onInit = [](Interface& interface, SDL_Renderer* renderer) -> void {});
	Interface(const std::vector<UIObject*>& scene, std::function<void(Interface&, SDL_Renderer*)> onInit = [](Interface& interface, SDL_Renderer* renderer) -> void {});
	~Interface();

	double secondsElapsed() const;
	
	void update();
	void draw();
	void drawSDL();
};

