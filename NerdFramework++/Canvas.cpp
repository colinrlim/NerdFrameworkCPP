#include <algorithm>
#include "Canvas.h"

Canvas::Canvas(const UDim2& position, const UDim2& size) :
    UIObject(position, size)
{ }

void Canvas::update(double delta) {
    UIObject::update(delta);
}
void Canvas::draw(Image4& screen, const Rect2<double>& scope) {
    if (visible == false) return;
    this->onDraw(*this, screen, scope);
}
void Canvas::draw(SDL_Renderer* renderer, const Rect2<double>& scope) {
    if (visible == false) return;
    this->onDrawSDL(*this, renderer, scope);
}