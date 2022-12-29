#pragma once

#include <SDL.h>
#include "Image4.h"

class Stamper {
public:
	virtual void draw(Image4& screen, const Rect2<double>& bounds) = 0;
	virtual void draw(SDL_Renderer* renderer, const Rect2<double>& bounds) = 0;
};

