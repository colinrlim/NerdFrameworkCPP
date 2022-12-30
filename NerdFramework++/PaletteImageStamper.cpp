#include "PaletteImageStamper.h"
#include "Math.h"
#include <iostream>

PaletteImageStamper::PaletteImageStamper(const PaletteImageStamper& rhs) :
    _image(std::move(rhs._image)),
    _renderer(nullptr),
    _textures(),
    PaletteStamper(rhs)
{ }
PaletteImageStamper& PaletteImageStamper::operator=(const PaletteImageStamper& rhs) { return *this; }
PaletteImageStamper& PaletteImageStamper::operator=(PaletteImageStamper&& rhs) { return *this; }

SDL_Texture* PaletteImageStamper::createTexture(const Palette<Color4>& palette) const {
    Image4 bakedImage(_image, palette);
    SDL_Texture* texture = SDL_CreateTexture(_renderer, SDL_PIXELFORMAT_ABGR8888, SDL_TEXTUREACCESS_STATIC, bakedImage.width(), bakedImage.height());
    SDL_SetTextureBlendMode(texture, SDL_BLENDMODE_BLEND);
    SDL_UpdateTexture(texture, nullptr, bakedImage.data, bakedImage.width() * 4);
    return texture;
}

PaletteImageStamper::PaletteImageStamper(PaletteImage&& image, Palette<Color4>* defaultPalette) :
    _image(std::move(image)),
    _renderer(nullptr),
    _textures(),
    PaletteStamper(defaultPalette)
{ }
PaletteImageStamper::PaletteImageStamper(SDL_Renderer* renderer, PaletteImage&& image, Palette<Color4>* defaultPalette) :
    _image(std::move(image)),
    _renderer(renderer),
    _textures(),
    PaletteStamper(defaultPalette)
{ }
PaletteImageStamper::PaletteImageStamper(PaletteImageStamper&& rhs) :
    _image(std::move(rhs._image)),
    _renderer(rhs._renderer),
    _textures(std::move(rhs._textures)),
    PaletteStamper(std::move(rhs))
{
    rhs._renderer = nullptr;
}
PaletteImageStamper::~PaletteImageStamper() {
    for (auto pair = _textures.begin(); pair != _textures.end(); ++pair)
        SDL_DestroyTexture(pair->second);
}

void PaletteImageStamper::draw(const Palette<Color4>& palette, Image4& screen, const Rect2<double>& bounds) {
    // Fit to screen bounds
    const double maxWidth = screen.width();
    const double maxHeight = screen.height();
    double xMinConstrained = Math::max(0.0, bounds.x);
    double yMinConstrained = Math::max(0.0, bounds.y);
    double xMaxConstrained = Math::min(bounds.x + bounds.width, maxWidth);
    double yMaxConstrained = Math::min(bounds.y + bounds.height, maxHeight);

    // Render object fill color (image) on top of pre-existing
    for (size_t y = (int)yMinConstrained; y < (int)yMaxConstrained; y++) {
        double s = (y - bounds.y) / bounds.height;
        for (size_t x = (int)xMinConstrained; x < (int)xMaxConstrained; x++) {
            double t = (x - bounds.x) / bounds.width;
            void* pixel = screen.pixelAt(x, y);
            Color4::flatten(pixel, palette[_image.atParameterization(t, s)]);
        }
    }
}
void PaletteImageStamper::draw(const Palette<Color4>& palette, SDL_Renderer* renderer, const Rect2<double>& bounds) {
    const Palette<Color4>* palettePtr = &palette;
    SDL_Rect destination{ (int)bounds.x, (int)bounds.y, (int)bounds.width, (int)bounds.height };
    if (_textures.find(palettePtr) == _textures.end())
        _textures.emplace(palettePtr, createTexture(palette));
    SDL_RenderCopy(renderer, _textures[palettePtr], nullptr, &destination);
}
void PaletteImageStamper::draw(Image4& screen, const Rect2<double>& bounds) {
    draw(*defaultPalette, screen, bounds);
}
void PaletteImageStamper::draw(SDL_Renderer* renderer, const Rect2<double>& bounds) {
    draw(*defaultPalette, renderer, bounds);
}