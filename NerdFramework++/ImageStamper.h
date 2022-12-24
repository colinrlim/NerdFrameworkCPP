#pragma once

#include <SDL.h>
#include "Image4.h"
#include "Rect2.h"

class ImageStamper {
    Image4 _image;
    SDL_Renderer* _renderer;
    SDL_Texture* _texture;

    ImageStamper(const ImageStamper& rhs);
    ImageStamper& operator=(const ImageStamper& rhs);
    ImageStamper& operator=(ImageStamper&& rhs);
public:
    ImageStamper(SDL_Renderer* renderer, Image4&& image);
    ImageStamper(ImageStamper&& rhs);
    ~ImageStamper();

    const Image4& getImage() const;
    void setImage(Image4&& image);

    void draw(Image4& screen, const Rect2<double>& bounds);
    void draw(SDL_Renderer* renderer, const Rect2<double>& bounds);
};

