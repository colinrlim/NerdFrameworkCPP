#pragma once

#include "UIObject.h"
#include "Stamper.h"
#include "Image4.h"

class ImageLabel : public UIObject
{
    ImageLabel(const ImageLabel& rhs) = delete;
    ImageLabel& operator=(const ImageLabel& rhs) = delete;
    ImageLabel& operator=(ImageLabel&& rhs) = delete;
public:
    Stamper* stamper;

    ImageLabel(Stamper* stamper, const UDim2& position, const UDim2& size);
    ~ImageLabel();

    void update(double delta);
    void draw(Image4& screen, const Rect2<double>& scope);
    void draw(SDL_Renderer* renderer, const Rect2<double>& scope);
};

