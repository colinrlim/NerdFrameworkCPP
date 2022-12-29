#pragma once

#include <vector>
#include "Button.h"

class Frame : public UIObject
{
private:
    std::vector<UIObject*> _children;
    std::vector<Button*> _buttons;
    std::vector<Frame*> _frames;

    void leftClick(int x, int y, const Rect2<double>& scope) const;
    void rightClick(int x, int y, const Rect2<double>& scope) const;

    void cacheAllChildren();

    friend class Interface;
public:
    UDim scrollBarSize;

    Frame(const UDim2& position, const UDim2& size);
    Frame(const std::vector<UIObject*>& children, const UDim2& position, const UDim2& size);
    Frame(std::vector<UIObject*>&& children, const UDim2& position, const UDim2& size);

    void addChild(UIObject* object);
    const std::vector<UIObject*>& getChildren();
    const std::vector<Button*>& getButtons();

    void update(double delta);
    void draw(Image4& screen, const Rect2<double>& scope);
    void draw(SDL_Renderer* renderer, const Rect2<double>& scope);
};

