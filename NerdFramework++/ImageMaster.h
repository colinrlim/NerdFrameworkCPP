#pragma once

#include <SDL.h>
#include "Image4.h"
#include "Rect2.h"

class ImageMaster {
    Image4 _image;
    SDL_Renderer* _renderer;
    SDL_Texture* _texture;

    ImageMaster(const ImageMaster& rhs);
    ImageMaster& operator=(const ImageMaster& rhs);
    ImageMaster& operator=(ImageMaster&& rhs);
public:
    ImageMaster(SDL_Renderer* renderer, Image4&& image);
    ImageMaster(ImageMaster&& rhs);
    ~ImageMaster();

    const Image4& getImage() const;
    void setImage(Image4&& image);

    void draw(Image4& screen, const Rect2<double>& bounds);
    void draw(SDL_Renderer* renderer, const Rect2<double>& bounds);
};

