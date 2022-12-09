#include "Renderer2.h"

Renderer2::Renderer2() : UIObject() { }
Renderer2::Renderer2(const UDim2& position, const UDim2& size) : UIObject(position, size) { }

void Renderer2::renderLine(Image4& screen, const Color4& color, const Vector2& begin, const Vector2& end) const {

}
void Renderer2::renderLine(Image4& screen, const ColorSequence<Color4>& color, const Vector2& begin, const Vector2& end) const {

}
void Renderer2::renderTriangle(Image4& screen, const Color4& color, const Vector2& a, const Vector2& b, const Vector2& c) const {

}
void Renderer2::renderTriangle(Image4& screen, const Color4& color1, const Color4& color2, const Color4& Color4, const Vector2& a, const Vector2& b, const Vector2& c) const {

}
void Renderer2::renderTriangle(Image4& screen, const Color4& color, const Triangle2& triangle) const {
    renderTriangle(screen, color, triangle.a, triangle.b, triangle.c);
}
void Renderer2::renderTriangle(Image4& screen, const Color4& color1, const Color4& color2, const Color4& Color4, const Triangle2& triangle) const {
    renderTriangle(screen, color1, color2, Color4, triangle.a, triangle.b, triangle.c);
}
void Renderer2::renderCircle(Image4& screen, const Color4& color, const Vector2& pos, int radius) const {

}
void Renderer2::renderCircle(Image4& screen, const ColorSequence<Color4>& color, const Vector2& pos, int radius) const {

}

void Renderer2::renderLine(SDL_Renderer* renderer, const Color4& color, const Vector2& begin, const Vector2& end) const {
    SDL_SetRenderDrawColor(renderer, color.r, color.g, color.b, color.alpha);
    SDL_RenderDrawLine(renderer, (int)begin.x, (int)begin.y, (int)end.x, (int)end.y);
}
void Renderer2::renderLine(SDL_Renderer* renderer, const ColorSequence<Color4>& color, const Vector2& begin, const Vector2& end) const {

}
void Renderer2::renderTriangle(SDL_Renderer* renderer, const Color4& color, const Vector2& a, const Vector2& b, const Vector2& c) const {
    const std::vector< SDL_Vertex > verts
    {
        { SDL_FPoint{ (float)a.x, (float)a.y }, SDL_Color{ color.r, color.g, color.b, color.alpha }, SDL_FPoint{ 0 }, },
        { SDL_FPoint{ (float)b.x, (float)b.y }, SDL_Color{ color.r, color.g, color.b, color.alpha }, SDL_FPoint{ 0 }, },
        { SDL_FPoint{ (float)c.x, (float)c.y }, SDL_Color{ color.r, color.g, color.b, color.alpha }, SDL_FPoint{ 0 }, },
    };
    SDL_RenderGeometry(renderer, nullptr, verts.data(), (int)verts.size(), nullptr, 0);
}
void Renderer2::renderTriangle(SDL_Renderer* renderer, const Color4& color1, const Color4& color2, const Color4& Color4, const Vector2& a, const Vector2& b, const Vector2& c) const {
    const std::vector< SDL_Vertex > verts
    {
        { SDL_FPoint{ (float)a.x, (float)a.y }, SDL_Color{ color1.r, color1.g, color1.b, color1.alpha }, SDL_FPoint{ 0 }, },
        { SDL_FPoint{ (float)b.x, (float)b.y }, SDL_Color{ color2.r, color2.g, color2.b, color2.alpha }, SDL_FPoint{ 0 }, },
        { SDL_FPoint{ (float)c.x, (float)c.y }, SDL_Color{ Color4.r, Color4.g, Color4.b, Color4.alpha }, SDL_FPoint{ 0 }, },
    };
    SDL_RenderGeometry(renderer, nullptr, verts.data(), (int)verts.size(), nullptr, 0);
}
void Renderer2::renderTriangle(SDL_Renderer* renderer, const Color4& color, const Triangle2& triangle) const {
	renderTriangle(renderer, color, triangle.a, triangle.b, triangle.c);
}
void Renderer2::renderTriangle(SDL_Renderer* renderer, const Color4& color1, const Color4& color2, const Color4& Color4, const Triangle2& triangle) const {
	renderTriangle(renderer, color1, color2, Color4, triangle.a, triangle.b, triangle.c);
}
void Renderer2::renderCircle(SDL_Renderer* renderer, const Color4& color, const Vector2& pos, int radius) const {

}
void Renderer2::renderCircle(SDL_Renderer* renderer, const ColorSequence<Color4>& color, const Vector2& pos, int radius) const {

}