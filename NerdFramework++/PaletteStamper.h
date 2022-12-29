#pragma once

#include "Stamper.h"

class PaletteStamper : public Stamper {
protected:
	PaletteStamper() : defaultPalette(nullptr) { }
	PaletteStamper(Palette<Color4>* defaultPalette) : defaultPalette(defaultPalette) { }
public:
	Palette<Color4>* defaultPalette;

	virtual void draw(const Palette<Color4>& palette, Image4& screen, const Rect2<double>& bounds) = 0;
	virtual void draw(const Palette<Color4>& palette, SDL_Renderer* renderer, const Rect2<double>& bounds) = 0;
};

