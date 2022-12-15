#pragma once

#include <SDL.h>
#include "Image4.h"
#include "Rect2.h"

class ImageBatcher {
    Image4 _image;
    SDL_Renderer* _renderer;
    SDL_Texture* _texture;

    ImageBatcher(const ImageBatcher& rhs);
    ImageBatcher& operator=(const ImageBatcher& rhs);
    ImageBatcher& operator=(ImageBatcher&& rhs);
public:
    ImageBatcher(SDL_Renderer* renderer, Image4&& image);
    ImageBatcher(ImageBatcher&& rhs);
    ~ImageBatcher();

    const Image4& getImage() const;
    void setImage(Image4&& image);

    void draw(Image4& screen, const Rect2<double>& bounds);
    void draw(SDL_Renderer* renderer, const Rect2<double>& bounds);
};

