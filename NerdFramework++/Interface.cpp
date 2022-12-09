#include "Interface.h"
#include <iostream>

Interface::Interface() :
	window(SDL_CreateWindow("Window", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 640, 480, SDL_WINDOW_SHOWN)),
	frame(UDim2::zero, UDim2::one),
	_width(640),
	_height(480),
	onUpdate([](Interface& obj, double delta) -> void {}),
	screen(_width, _height),
	_created(std::chrono::steady_clock::now()),
	_lastFrame(std::chrono::steady_clock::now())
{
	if (window != nullptr)
	{
		_renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
		_texture = SDL_CreateTexture(_renderer, SDL_PIXELFORMAT_ABGR8888, SDL_TEXTUREACCESS_STATIC, _width, _height);
	}
}
Interface::Interface(SDL_Window* window) :
	window(window),
	frame(UDim2::zero, UDim2::one),
	onUpdate([](Interface& obj, double delta) -> void {}),
	_created(std::chrono::steady_clock::now()),
	_lastFrame(std::chrono::steady_clock::now())
{
	SDL_GetWindowSize(window, &_width, &_height);
	screen = Image4(_width, _height);
	if (window != nullptr)
	{
		_renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
		_texture = SDL_CreateTexture(_renderer, SDL_PIXELFORMAT_ABGR8888, SDL_TEXTUREACCESS_STATIC, _width, _height);
	}
}
Interface::Interface(SDL_Window* window, const std::vector<UIObject*>& scene) :
	window(window),
	frame(UDim2::zero, UDim2::one),
	onUpdate([](Interface& obj, double delta) -> void {}),
	_created(std::chrono::steady_clock::now()),
	_lastFrame(std::chrono::steady_clock::now())
{
	SDL_GetWindowSize(window, &_width, &_height);
	screen = Image4(_width, _height);
	frame.children = scene;
	if (window != nullptr)
	{
		_renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
		_texture = SDL_CreateTexture(_renderer, SDL_PIXELFORMAT_ABGR8888, SDL_TEXTUREACCESS_STATIC, _width, _height);
	}
}
Interface::Interface(const std::vector<UIObject*>& scene) :
	window(SDL_CreateWindow("Window", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 640, 480, SDL_WINDOW_SHOWN)),
	frame(UDim2::zero, UDim2::one),
	onUpdate([](Interface& obj, double delta) -> void {}),
	_width(640),
	_height(480),
	screen(_width, _height),
	_created(std::chrono::steady_clock::now()),
	_lastFrame(std::chrono::steady_clock::now())
{
	frame.children = scene;
	if (window != NULL)
	{
		_renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
		_texture = SDL_CreateTexture(_renderer, SDL_PIXELFORMAT_ABGR8888, SDL_TEXTUREACCESS_STATIC, _width, _height);
	}
}
Interface::~Interface() {
	if (window != NULL)
	{
		SDL_DestroyTexture(_texture);
		SDL_DestroyRenderer(_renderer);
	}
	SDL_DestroyWindow(window);
}

double Interface::secondsElapsed() const {
	return (double)std::chrono::duration_cast<std::chrono::seconds>(std::chrono::steady_clock::now() - _created).count();
}

void Interface::update() {
	auto now(std::chrono::steady_clock::now());
	double delta = (double)std::chrono::duration_cast<std::chrono::seconds>(now - _lastFrame).count();
	onUpdate(*this, delta);
	frame.update(delta);
	_lastFrame = now;
}
void Interface::draw() {
	frame.draw(screen, Rect2<double>(0, 0, _width, _height));
	SDL_UpdateTexture(_texture, nullptr, screen.data, _width * 4);

	SDL_RenderClear(_renderer);
	SDL_RenderCopy(_renderer, _texture, nullptr, nullptr);
	SDL_RenderPresent(_renderer);
}
void Interface::drawSDL() {
	SDL_RenderClear(_renderer);
	frame.draw(_renderer, Rect2<double>(0, 0, _width, _height));
	SDL_RenderPresent(_renderer);
}