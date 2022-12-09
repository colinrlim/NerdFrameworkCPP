#include <algorithm>
#include "Frame.h"

Frame::Frame(const UDim2& position, const UDim2& size) :
    UIObject(position, size),
    children(),
    scrollBarSize(UDim(0.0, 5.0))
{ }
Frame::Frame(std::vector<UIObject*>&& children, const UDim2& position, const UDim2& size) :
    UIObject(position, size),
    children(children),
    scrollBarSize(UDim(0.0, 5.0))
{ }

void Frame::update(double delta) {
    UIObject::update(delta);

    for (size_t i = 0; i < this->children.size(); i++) {
        this->children[i]->update(delta);
    }
}
void Frame::draw(Image4& screen, const Rect2<double>& scope) {
    UIObject::draw(screen, scope);
    if (visible == false) return;

    Rect2<double> childScope(getPosition(), getSize(), scope);

    std::sort(this->children.begin(), this->children.end(), [](UIObject const* lhs, UIObject const* rhs) -> bool { return lhs->zindex > rhs->zindex; });
    for (size_t i = 0; i < this->children.size(); i++) {
        this->children[i]->draw(screen, childScope);
    }
}
void Frame::draw(SDL_Renderer* renderer, const Rect2<double>& scope) {
    UIObject::draw(renderer, scope);
    if (visible == false) return;
    
    Rect2<double> childScope(getPosition(), getSize(), scope);

    std::sort(this->children.begin(), this->children.end(), [](UIObject const* lhs, UIObject const* rhs) -> bool { return lhs->zindex > rhs->zindex; });
    for (size_t i = 0; i < this->children.size(); i++) {
        this->children[i]->draw(renderer, childScope);
    }
}