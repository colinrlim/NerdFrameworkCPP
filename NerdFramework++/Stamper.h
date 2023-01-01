#pragma once

#include <SDL.h>
#include "Image4.h"

class Stamper {
public:
	enum ImageFlipOptions {
		FLIP_NONE		  = 0,
		FLIP_HORIZONTALLY = 1,
		FLIP_VERTICALLY   = 2
	};
	enum class ImageScaleType {
		STRETCH,
		TILE,
		FIT,
		CROP
	};

	virtual void draw(Image4& screen, const Rect2<double>& bounds) = 0;
	virtual void draw(SDL_Renderer* renderer, const Rect2<double>& bounds) = 0;
	virtual void draw(Image4& screen, const Rect2<double>& bounds, ImageFlipOptions flipOptions, ImageScaleType scaleType) = 0;
	virtual void draw(SDL_Renderer* renderer, const Rect2<double>& bounds, ImageFlipOptions flipOptions, ImageScaleType scaleType) = 0;
	virtual void draw(Image4& screen, const Rect2<double>& bounds, double degrees, const Vector2i& origin, ImageFlipOptions flipOptions, ImageScaleType scaleType) = 0;
	virtual void draw(SDL_Renderer* renderer, const Rect2<double>& bounds, double degrees, const Vector2i& origin, ImageFlipOptions flipOptions, ImageScaleType scaleType) = 0;
protected:
	static constexpr size_t transformedX(size_t x, int width, ImageFlipOptions flipOptions) {
		if ((flipOptions & FLIP_HORIZONTALLY) != 0)
			return width - 1 - x;
		return x;
	}
	static constexpr size_t transformedY(size_t y, int height, ImageFlipOptions flipOptions) {
		if ((flipOptions & FLIP_VERTICALLY) != 0)
			return height - 1 - y;
		return y;
	}
	static constexpr double transformedT(double t, ImageFlipOptions flipOptions) {
		if ((flipOptions & FLIP_HORIZONTALLY) != 0)
			return 0.999 - t;
		return t;
	}
	static constexpr double transformedS(double s, ImageFlipOptions flipOptions) {
		if ((flipOptions & FLIP_VERTICALLY) != 0)
			return 0.999 - s;
		return s;
	}
};

