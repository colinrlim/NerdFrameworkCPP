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
	virtual void draw(const Palette<Color4>& palette, Image4& screen, const Rect2<double>& bounds, ImageFlipOptions flipOptions, ImageScaleType scaleType) = 0;
	virtual void draw(const Palette<Color4>& palette, SDL_Renderer* renderer, const Rect2<double>& bounds, ImageFlipOptions flipOptions, ImageScaleType scaleType) = 0;
	virtual void draw(const Palette<Color4>& palette, Image4& screen, const Rect2<double>& bounds, double degrees, const Vector2i& origin, ImageFlipOptions flipOptions, ImageScaleType scaleType) = 0;
	virtual void draw(const Palette<Color4>& palette, SDL_Renderer* renderer, const Rect2<double>& bounds, double degrees, const Vector2i& origin, ImageFlipOptions flipOptions, ImageScaleType scaleType) = 0;

	void draw(Image4& screen, const Rect2<double>& bounds) {
		draw(*defaultPalette, screen, bounds);
	}
	void draw(SDL_Renderer* renderer, const Rect2<double>& bounds) {
		draw(*defaultPalette, renderer, bounds);
	}
	void draw(Image4& screen, const Rect2<double>& bounds, ImageFlipOptions flipOptions, ImageScaleType scaleType) {
		draw(*defaultPalette, screen, bounds, flipOptions, scaleType);
	}
	void draw(SDL_Renderer* renderer, const Rect2<double>& bounds, ImageFlipOptions flipOptions, ImageScaleType scaleType) {
		draw(*defaultPalette, renderer, bounds, flipOptions, scaleType);
	}
	void draw(Image4& screen, const Rect2<double>& bounds, double degrees, const Vector2i& origin, ImageFlipOptions flipOptions, ImageScaleType scaleType) {
		draw(*defaultPalette, screen, bounds, flipOptions, scaleType);
	}
	void draw(SDL_Renderer* renderer, const Rect2<double>& bounds, double degrees, const Vector2i& origin, ImageFlipOptions flipOptions, ImageScaleType scaleType) {
		draw(*defaultPalette, renderer, bounds, flipOptions, scaleType);
	}
};

