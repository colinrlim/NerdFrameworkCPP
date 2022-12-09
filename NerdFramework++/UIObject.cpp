#include "UIObject.h"
#include "Math.h"
#include <iostream>

UIObject::UIObject(const UDim2& position, const UDim2& size) :
    _color(Color3::white),
    _borderColor(Color3::black),

    _opacity(1.0),
    _borderOpacity(1.0),

    _colorBaked(Color4::white),
    _borderColorBaked(Color4::black),

    _position(position),
    _size(size),
    
    borderWidth(0),
    zindex(1),
    visible(true),

    onUpdate([](UIObject& obj, double delta) -> void {}),
    onDraw([](UIObject& obj, Image4& screen, const Rect2<double>& scope) -> void {}),
    onDrawSDL([](UIObject& obj, SDL_Renderer* renderer, const Rect2<double>& scope) -> void {})
{ }

const Color3& UIObject::getColor() const {
    return _color;
}
const Color3& UIObject::getBorderColor() const {
    return _borderColor;
}
void UIObject::setColor(const Color3& color) {
    _color = color;
    _colorBaked = _color.asColor4((uint8_t)(_opacity * 255));
}
void UIObject::setBorderColor(const Color3& color) {
    _borderColor = color;
    _borderColorBaked = _borderColor.asColor4((uint8_t)(_borderOpacity * 255));
}

double UIObject::getOpacity() const {
    return _opacity;
}
double UIObject::getBorderOpacity() const {
    return _borderOpacity;
}
void UIObject::setOpacity(double alpha) {
    _opacity = alpha;
    _colorBaked = _color.asColor4((uint8_t)(_opacity * 255));
}
void UIObject::setBorderOpacity(double alpha) {
    _borderOpacity = alpha;
    _borderColorBaked = _borderColor.asColor4((uint8_t)(_borderOpacity * 255));
}

const UDim2& UIObject::getPosition() const {
    return _position;
}
const UDim2& UIObject::getSize() const {
    return _size;
}
void UIObject::setPosition(const UDim2& position) {
    _position = position;
}
void UIObject::setSize(const UDim2& size) {
    _size = size;
}

Vector2i UIObject::getAbsolutePosition(int width, int height) const {
	return Vector2i((int)_position.x.absolute(width), (int)_position.y.absolute(height));
}
Vector2i UIObject::getAbsoluteSize(int width, int height) const {
	return Vector2i((int)_size.x.absolute(width), (int)_size.y.absolute(height));
}
Vector2i UIObject::getAbsolutePosition(const Rect2<double>& scope) const {
    return Vector2i((int)_position.x.absolute(scope.width), (int)_position.y.absolute(scope.height));
}
Vector2i UIObject::getAbsoluteSize(const Rect2<double>& scope) const {
    return Vector2i((int)_size.x.absolute(scope.width), (int)_size.y.absolute(scope.height));
}

void UIObject::update(double delta) {
	this->onUpdate(*this, delta);
}
void UIObject::draw(Image4& screen, const Rect2<double>& scope) {
    if (visible == false) return;

    // Object bounds; Doesn't use AbsolutePosition() and AbsoluteSize() for optimization purposes
    double xMin = _position.x.absolute(scope.width) + scope.x;
    double yMin = _position.y.absolute(scope.height) + scope.y;
    double xMax = xMin + _size.x.absolute(scope.width);
    double yMax = yMin + _size.y.absolute(scope.height);

    // Fit to screen bounds
    const double maxWidth = screen.getWidth();
    const double maxHeight = screen.getHeight();
    xMin = Math::max(0.0, xMin);
    yMin = Math::max(0.0, yMin);
    xMax = Math::min(xMax, maxWidth - 1.0);
    yMax = Math::min(yMax, maxHeight - 1.0);

    // Render object border color on top of pre-existing
    if (borderWidth > 0 && _borderOpacity > 0.0)
    {
        for (size_t y = (int)Math::max(0.0, yMin - borderWidth); y < (int)Math::min(yMin, maxHeight); y++)
            for (size_t x = (int)Math::max(0.0, xMin - borderWidth); x <= (int)Math::min(xMax + borderWidth, maxHeight); x++) {
                void* pixel = screen.pixelAt(x, y);
                Color4::flatten(pixel, _borderColorBaked);
            }
        for (size_t y = (int)Math::max(0.0, yMax + 1); y <= (int)Math::min(yMax + borderWidth, maxHeight); y++)
            for (size_t x = (int)Math::max(0.0, xMin - borderWidth); x <= (int)Math::min(xMax + borderWidth, maxHeight); x++) {
                void* pixel = screen.pixelAt(x, y);
                Color4::flatten(pixel, _borderColorBaked);
            }
        for (size_t y = (int)yMin; y <= (int)yMax; y++)
            for (size_t x = (int)Math::max(0.0, xMin - borderWidth); x < (int)Math::min(xMin, maxHeight); x++) {
                void* pixel = screen.pixelAt(x, y);
                Color4::flatten(pixel, _borderColorBaked);
            }
        for (size_t y = (int)yMin; y <= (int)yMax; y++)
            for (size_t x = (int)Math::max(0.0, xMax + 1); x <= (int)Math::min(xMax + borderWidth, maxHeight); x++) {
                void* pixel = screen.pixelAt(x, y);
                Color4::flatten(pixel, _borderColorBaked);
            }
    }

    // Render object fill color on top of pre-existing
    if (_opacity > 0.0)
        for (size_t y = (int)yMin; y <= (int)yMax; y++)
            for (size_t x = (int)xMin; x <= (int)xMax; x++) {
                void* pixel = screen.pixelAt(x, y);
                Color4::flatten(pixel, _colorBaked);
            }

    this->onDraw(*this, screen, scope);
}
void UIObject::draw(SDL_Renderer* renderer, const Rect2<double>& scope) {
    if (visible == false) return;

    // Object bounds; Doesn't use AbsolutePosition() and AbsoluteSize() for optimization purposes
    double xPos = _position.x.absolute(scope.width) + scope.x;
    double yPos = _position.y.absolute(scope.height) + scope.y;
    double xSize = _size.x.absolute(scope.width);
    double ySize = _size.y.absolute(scope.height);

    // Render object border color on top of pre-existing
    if (borderWidth > 0 && _borderOpacity > 0.0)
    {
        SDL_SetRenderDrawColor(renderer, _borderColorBaked.r, _borderColorBaked.g, _borderColorBaked.b, _borderColorBaked.alpha);
        SDL_Rect borderTop{ (int)(xPos - borderWidth), (int)(yPos - borderWidth), (int)(xSize) + borderWidth * 2, (int)(borderWidth) };
        SDL_Rect borderBottom{ (int)(xPos - borderWidth), (int)(yPos + ySize), (int)(xSize) + borderWidth * 2, (int)(borderWidth)};
        SDL_Rect borderLeft{ (int)(xPos - borderWidth), (int)(yPos), (int)(borderWidth), (int)(ySize) };
        SDL_Rect borderRight{ (int)(xPos + xSize), (int)(yPos), (int)(borderWidth), (int)(ySize) };
        SDL_RenderFillRect(renderer, &borderTop);
        SDL_RenderFillRect(renderer, &borderBottom);
        SDL_RenderFillRect(renderer, &borderLeft);
        SDL_RenderFillRect(renderer, &borderRight);
    }

    // Render object fill color on top of pre-existing
    if (_opacity < 1.0) {
        SDL_SetRenderDrawColor(renderer, _colorBaked.r, _colorBaked.g, _colorBaked.b, _colorBaked.alpha);
        SDL_Rect fillRect{ (int)xPos, (int)yPos, (int)xSize, (int)ySize };
        SDL_RenderFillRect(renderer, &fillRect);
    }

    this->onDrawSDL(*this, renderer, scope);
}