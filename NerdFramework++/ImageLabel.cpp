#include "ImageLabel.h"
#include "Math.h"

ImageLabel::ImageLabel(Stamper* stamper, const UDim2& position, const UDim2& size) :
    UIObject(position, size),
    stamper(stamper)
{ }

void ImageLabel::update(double delta) {
    UIObject::update(delta);
}
void ImageLabel::draw(Image4& screen, const Rect2<double>& scope) {
    UIObject::draw(screen, scope);
    if (visible == false) return;

    Rect2<double> childScope(getPosition(), getSize(), scope);

    stamper->draw(screen, childScope);
}
void ImageLabel::draw(SDL_Renderer* renderer, const Rect2<double>& scope) {
    UIObject::draw(renderer, scope);
    Rect2<double> childScope(getPosition(), getSize(), scope);

    stamper->draw(renderer, childScope);
}