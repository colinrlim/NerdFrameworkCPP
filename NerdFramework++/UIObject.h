#pragma once

#include <functional>
#include <SDL.h>
#include "Vector2i.h"
#include "Color4.h"
#include "Image4.h"
#include "UDim2.h"
#include "Rect2.h"

class UIObject
{
private:
    UDim2 _position;
    UDim2 _size;

    Color3 _color;
    Color3 _borderColor;

    double _opacity;
    double _borderOpacity;

    Color4 _colorBaked;
    Color4 _borderColorBaked;
protected:
    UIObject(const UDim2& position = UDim2::zero, const UDim2& size = UDim2::one);
public:
    int borderWidth;
    int zindex;
    bool visible;

    std::function<void(UIObject&, double)> onUpdate;
    std::function<void(UIObject&, Image4&, const Rect2<double>&)> onDraw;
    std::function<void(UIObject&, SDL_Renderer*, const Rect2<double>&)> onDrawSDL;

    const Color3& getColor() const;
    const Color3& getBorderColor() const;
    void setColor(const Color3& color);
    void setBorderColor(const Color3& color);

    double getOpacity() const;
    double getBorderOpacity() const;
    void setOpacity(double alpha);
    void setBorderOpacity(double alpha);

    const UDim2& getPosition() const;
    const UDim2& getSize() const;
    virtual void setPosition(const UDim2& position);
    virtual void setSize(const UDim2& size);

    Vector2i getAbsolutePosition(int width, int height) const;
    Vector2i getAbsoluteSize(int width, int height) const;
    Vector2i getAbsolutePosition(const Rect2<double>& scope) const;
    Vector2i getAbsoluteSize(const Rect2<double>& scope) const;

    virtual void update(double delta);
    virtual void draw(Image4& screen, const Rect2<double>& scope);
    virtual void draw(SDL_Renderer* renderer, const Rect2<double>& scope);
};

