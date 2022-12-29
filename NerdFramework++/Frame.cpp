#include <algorithm>
#include "Frame.h"

void Frame::leftClick(int x, int y, const Rect2<double>& scope) const {
    for (auto iterator = _buttons.begin(); iterator != _buttons.end(); ++iterator) {
        const Button& object = **iterator;
        const Rect2<double> objectBounds(object.getPosition(), object.getSize(), scope);
        if (objectBounds.overlaps(x, y))
            object.onLeftClick(x, y);
    }
    for (auto iterator = _frames.begin(); iterator != _frames.end(); ++iterator) {
        const Frame& object = **iterator;
        const Rect2<double> objectBounds(object.getPosition(), object.getSize(), scope);
        if (objectBounds.overlaps(x, y))
            object.rightClick(x, y, scope);
    }
}
void Frame::rightClick(int x, int y, const Rect2<double>& scope) const {
    for (auto iterator = _buttons.begin(); iterator != _buttons.end(); ++iterator) {
        const Button& object = **iterator;
        const Rect2<double> objectBounds(object.getPosition(), object.getSize(), scope);
        if (objectBounds.overlaps(x, y))
            object.onRightClick(x, y);
    }
    for (auto iterator = _frames.begin(); iterator != _frames.end(); ++iterator) {
        const Frame& object = **iterator;
        const Rect2<double> objectBounds(object.getPosition(), object.getSize(), scope);
        if (objectBounds.overlaps(x, y))
            object.rightClick(x, y, scope);
    }
}

void Frame::cacheAllChildren() {
    for (auto iterator = _children.begin(); iterator != _children.end(); ++iterator) {
        const UIObject* object = *iterator;
        if (typeid(Button) == typeid(*object))
            _buttons.push_back((Button*)object);
        else if (typeid(Frame) == typeid(*object))
            _frames.push_back((Frame*)object);
    }
}

Frame::Frame(const UDim2& position, const UDim2& size) :
    UIObject(position, size),
    _children(),
    _buttons(),
    _frames(),
    scrollBarSize(UDim(0.0, 5.0))
{ }
Frame::Frame(const std::vector<UIObject*>& children, const UDim2& position, const UDim2& size) :
    UIObject(position, size),
    _children(children),
    _buttons(),
    _frames(),
    scrollBarSize(UDim(0.0, 5.0))
{
    cacheAllChildren();
}
Frame::Frame(std::vector<UIObject*>&& children, const UDim2& position, const UDim2& size) :
    UIObject(position, size),
    _children(std::move(children)),
    _buttons(),
    _frames(),
    scrollBarSize(UDim(0.0, 5.0))
{
    cacheAllChildren();
}

void Frame::addChild(UIObject* object) {
    _children.push_back(object);
    if (typeid(Button) == typeid(*object))
        _buttons.push_back((Button*)object);
    if (typeid(Frame) == typeid(*object))
        _frames.push_back((Frame*)object);
}
const std::vector<UIObject*>& Frame::getChildren() {
    return _children;
}
const std::vector<Button*>& Frame::getButtons() {
    return _buttons;
}

void Frame::update(double delta) {
    UIObject::update(delta);

    for (size_t i = 0; i < _children.size(); i++) {
        _children[i]->update(delta);
    }
}
void Frame::draw(Image4& screen, const Rect2<double>& scope) {
    UIObject::draw(screen, scope);
    if (visible == false) return;

    Rect2<double> childScope(getPosition(), getSize(), scope);

    std::sort(_children.begin(), _children.end(), [](UIObject const* lhs, UIObject const* rhs) -> bool { return lhs->zindex > rhs->zindex; });
    for (size_t i = 0; i < _children.size(); i++) {
        _children[i]->draw(screen, childScope);
    }
}
void Frame::draw(SDL_Renderer* renderer, const Rect2<double>& scope) {
    UIObject::draw(renderer, scope);
    if (visible == false) return;
    
    Rect2<double> childScope(getPosition(), getSize(), scope);

    std::sort(_children.begin(), _children.end(), [](UIObject const* lhs, UIObject const* rhs) -> bool { return lhs->zindex > rhs->zindex; });
    for (size_t i = 0; i < _children.size(); i++) {
        _children[i]->draw(renderer, childScope);
    }
}