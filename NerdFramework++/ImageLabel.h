#pragma once

#include "UIObject.h"
#include "Stamper.h"
#include "Image4.h"

class ImageLabel : public UIObject
{
public:
    Stamper* stamper;

    ImageLabel(Stamper* stamper, const UDim2& position, const UDim2& size);

    void update(double delta);
    void draw(Image4& screen, const Rect2<double>& scope);
    void draw(SDL_Renderer* renderer, const Rect2<double>& scope);
};

