#include "Interface.h"
#include <iostream>

Interface::Interface(std::function<void(Interface&, SDL_Renderer*)> onInit) :
	window(SDL_CreateWindow("Window", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 640, 480, SDL_WINDOW_SHOWN)),
	frame(UDim2::zero, UDim2::one),
	_width(640),
	_height(480),
	screen(_width, _height),
	_created(),
	_lastFrame(),
	onUpdate([](Interface& interface, double delta) -> void {}),
	onDraw([](Interface& interface, Image4& screen, const Rect2<double>& bounds) -> void {}),
	onDrawSDL([](Interface& interface, SDL_Renderer* renderer, const Rect2<double>& bounds) -> void {})
{
	_created.tickNow();
	_lastFrame.tickNow();
	if (window != nullptr)
	{
		_renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
		_texture = SDL_CreateTexture(_renderer, SDL_PIXELFORMAT_ABGR8888, SDL_TEXTUREACCESS_STATIC, _width, _height);
		SDL_SetRenderDrawBlendMode(_renderer, SDL_BLENDMODE_BLEND);
		SDL_SetTextureBlendMode(_texture, SDL_BLENDMODE_BLEND);
	}

	onInit(*this, _renderer);
}
Interface::Interface(SDL_Window* window, std::function<void(Interface&, SDL_Renderer*)> onInit) :
	window(window),
	frame(UDim2::zero, UDim2::one),
	_created(),
	_lastFrame(),
	onUpdate([](Interface& interface, double delta) -> void {}),
	onDraw([](Interface& interface, Image4& screen, const Rect2<double>& bounds) -> void {}),
	onDrawSDL([](Interface& interface, SDL_Renderer* renderer, const Rect2<double>& bounds) -> void {})
{
	_created.tickNow();
	_lastFrame.tickNow();
	SDL_GetWindowSize(window, &_width, &_height);
	screen = std::move(Image4(_width, _height));
	if (window != nullptr)
	{
		_renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
		_texture = SDL_CreateTexture(_renderer, SDL_PIXELFORMAT_ABGR8888, SDL_TEXTUREACCESS_STATIC, _width, _height);
		SDL_SetRenderDrawBlendMode(_renderer, SDL_BLENDMODE_BLEND);
		SDL_SetTextureBlendMode(_texture, SDL_BLENDMODE_BLEND);
	}

	onInit(*this, _renderer);
}
Interface::Interface(SDL_Window* window, const std::vector<UIObject*>& scene, std::function<void(Interface&, SDL_Renderer*)> onInit) :
	window(window),
	frame(scene, UDim2::zero, UDim2::one),
	_created(),
	_lastFrame(),
	onUpdate([](Interface& interface, double delta) -> void {}),
	onDraw([](Interface& interface, Image4& screen, const Rect2<double>& bounds) -> void {}),
	onDrawSDL([](Interface& interface, SDL_Renderer* renderer, const Rect2<double>& bounds) -> void {})
{
	_created.tickNow();
	_lastFrame.tickNow();
	SDL_GetWindowSize(window, &_width, &_height);
	screen = std::move(Image4(_width, _height));
	if (window != nullptr)
	{
		_renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
		_texture = SDL_CreateTexture(_renderer, SDL_PIXELFORMAT_ABGR8888, SDL_TEXTUREACCESS_STATIC, _width, _height);
		SDL_SetRenderDrawBlendMode(_renderer, SDL_BLENDMODE_BLEND);
		SDL_SetTextureBlendMode(_texture, SDL_BLENDMODE_BLEND);
	}

	onInit(*this, _renderer);
}
Interface::Interface(const std::vector<UIObject*>& scene, std::function<void(Interface&, SDL_Renderer*)> onInit) :
	window(SDL_CreateWindow("Window", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 640, 480, SDL_WINDOW_SHOWN)),
	frame(scene, UDim2::zero, UDim2::one),
	_width(640),
	_height(480),
	screen(_width, _height),
	_created(),
	_lastFrame(),
	onUpdate([](Interface& interface, double delta) -> void {}),
	onDraw([](Interface& interface, Image4& screen, const Rect2<double>& bounds) -> void {}),
	onDrawSDL([](Interface& interface, SDL_Renderer* renderer, const Rect2<double>& bounds) -> void {})
{
	_created.tickNow();
	_lastFrame.tickNow();
	if (window != NULL)
	{
		_renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
		_texture = SDL_CreateTexture(_renderer, SDL_PIXELFORMAT_ABGR8888, SDL_TEXTUREACCESS_STATIC, _width, _height);
		SDL_SetRenderDrawBlendMode(_renderer, SDL_BLENDMODE_BLEND);
		SDL_SetTextureBlendMode(_texture, SDL_BLENDMODE_BLEND);
	}

	onInit(*this, _renderer);
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
	return _created.tock();
}

void Interface::update() {
	const Rect2<double> bounds(0, 0, _width, _height);

	int x, y;
	SDL_GetMouseState(&x, &y);

	if (true == false) // left click
		frame.leftClick(x, y, bounds);
	if (true == false) // right click
		frame.rightClick(x, y, bounds);

	double delta = _lastFrame.tock();
	onUpdate(*this, delta);
	frame.update(delta);
	_lastFrame.tickNow();
}
void Interface::draw() {
	const Rect2<double> bounds(0, 0, _width, _height);

	frame.draw(screen, bounds);
	onDraw(*this, screen, bounds);
	SDL_UpdateTexture(_texture, nullptr, screen.data, _width * 4);

	SDL_RenderClear(_renderer);
	SDL_RenderCopy(_renderer, _texture, nullptr, nullptr);
	SDL_RenderPresent(_renderer);
}
void Interface::drawSDL() {
	const Rect2<double> bounds(0, 0, _width, _height);

	SDL_RenderClear(_renderer);
	frame.draw(_renderer, bounds);
	onDrawSDL(*this, _renderer, bounds);
	SDL_RenderPresent(_renderer);
}