#pragma once

#include "Stamper.h"

class ImageStamper : public Stamper {
    Image4 _image;
    SDL_Renderer* _renderer;
    SDL_Texture* _texture;

    ImageStamper(const ImageStamper& rhs);
    ImageStamper& operator=(const ImageStamper& rhs);
    ImageStamper& operator=(ImageStamper&& rhs);
public:
    ImageStamper(Image4&& image);
    ImageStamper(SDL_Renderer* renderer, Image4&& image);
    ImageStamper(ImageStamper&& rhs);
    ~ImageStamper();

    void draw(Image4& screen, const Rect2<double>& bounds);
    void draw(SDL_Renderer* renderer, const Rect2<double>& bounds);
    void draw(Image4& screen, const Rect2<double>& bounds, ImageFlipOptions flipOptions, ImageScaleType scaleType);
    void draw(SDL_Renderer* renderer, const Rect2<double>& bounds, ImageFlipOptions flipOptions, ImageScaleType scaleType);
private:
    void draw(Image4& screen, const Rect2<double>& source, const Rect2<double>& destination, double degrees, const Vector2& origin, ImageFlipOptions flipOptions) const;
public:
    void draw(Image4& screen, const Rect2<double>& bounds, double degrees, const Vector2i& origin, ImageFlipOptions flipOptions, ImageScaleType scaleType);
    void draw(SDL_Renderer* renderer, const Rect2<double>& bounds, double degrees, const Vector2i& origin, ImageFlipOptions flipOptions, ImageScaleType scaleType);
};

