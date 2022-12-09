#pragma once

#include <vector>
#include "UIObject.h"

class Canvas : public UIObject
{
public:
    Canvas(const UDim2& position, const UDim2& size);

    void update(double delta);
    void draw(Image4& screen, const Rect2<double>& scope);
    void draw(SDL_Renderer* renderer, const Rect2<double>& scope);
};

