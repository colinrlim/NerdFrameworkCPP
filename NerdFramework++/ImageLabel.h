#pragma once

#include "UIObject.h"
#include "Image4.h"

class ImageLabel : public UIObject
{
    SDL_Renderer* _renderer;
    SDL_Texture* _texture;
    Image4 _image;

    ImageLabel(const ImageLabel& rhs);
    ImageLabel& operator=(const ImageLabel& rhs);
public:
    ImageLabel(const UDim2& position, const UDim2& size);
    ImageLabel(Image4&& image, const UDim2& position, const UDim2& size);
    ~ImageLabel();

    const Image4& getImage() const;
    void setImage(Image4&& image);

    void update(double delta);
    void draw(Image4& screen, const Rect2<double>& scope);
    void draw(SDL_Renderer* renderer, const Rect2<double>& scope);
};

