#pragma once

#include <SDL.h>
#include "ColorSequence.h"
#include "Triangle2.h"
#include "UIObject.h"

class Renderer2 : public UIObject
{
public:
	Renderer2();
	Renderer2(const UDim2& position, const UDim2& size);

	void renderLine(Image4& screen, const Color4& color, const Vector2& begin, const Vector2& end) const;
	void renderLine(Image4& screen, const ColorSequence<Color4>& color, const Vector2& begin, const Vector2& end) const;
	void renderTriangle(Image4& screen, const Color4& color, const Vector2& a, const Vector2& b, const Vector2& c) const;
	void renderTriangle(Image4& screen, const Color4& color1, const Color4& color2, const Color4& Color4, const Vector2& a, const Vector2& b, const Vector2& c) const;
	void renderTriangle(Image4& screen, const Color4& color, const Triangle2& triangle) const;
	void renderTriangle(Image4& screen, const Color4& color1, const Color4& color2, const Color4& Color4, const Triangle2& triangle) const;
	void renderCircle(Image4& screen, const Color4& color, const Vector2& pos, int radius) const;
	void renderCircle(Image4& screen, const ColorSequence<Color4>& color, const Vector2& pos, int radius) const;

	void renderLine(SDL_Renderer* renderer, const Color4& color, const Vector2& begin, const Vector2& end) const;
	void renderLine(SDL_Renderer* renderer, const ColorSequence<Color4>& color, const Vector2& begin, const Vector2& end) const;
	void renderTriangle(SDL_Renderer* renderer, const Color4& color, const Vector2& a, const Vector2& b, const Vector2& c) const;
	void renderTriangle(SDL_Renderer* renderer, const Color4& color1, const Color4& color2, const Color4& Color4, const Vector2& a, const Vector2& b, const Vector2& c) const;
	void renderTriangle(SDL_Renderer* renderer, const Color4& color, const Triangle2& triangle) const;
	void renderTriangle(SDL_Renderer* renderer, const Color4& color1, const Color4& color2, const Color4& Color4, const Triangle2& triangle) const;
	void renderCircle(SDL_Renderer* renderer, const Color4& color, const Vector2& pos, int radius) const;
	void renderCircle(SDL_Renderer* renderer, const ColorSequence<Color4>& color, const Vector2& pos, int radius) const;
};

