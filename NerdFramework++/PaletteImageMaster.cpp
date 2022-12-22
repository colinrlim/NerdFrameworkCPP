#include "PaletteImageMaster.h"
#include "Math.h"

PaletteImageMaster::PaletteImageMaster(const PaletteImageMaster& rhs) :
    _image(std::move(rhs._image)),
    _renderer(nullptr),
    _textures()
{ }
PaletteImageMaster& PaletteImageMaster::operator=(const PaletteImageMaster& rhs) { return *this; }
PaletteImageMaster& PaletteImageMaster::operator=(PaletteImageMaster&& rhs) { return *this; }

SDL_Texture* PaletteImageMaster::createTexture(Palette<Color4>* palette) const {
    Image4 bakedImage(_image, *palette);
    SDL_Texture* texture = SDL_CreateTexture(_renderer, SDL_PIXELFORMAT_ABGR8888, SDL_TEXTUREACCESS_STATIC, bakedImage.width(), bakedImage.height());
    SDL_UpdateTexture(texture, nullptr, bakedImage.data, bakedImage.width() * 4);
    return texture;
}

PaletteImageMaster::PaletteImageMaster(SDL_Renderer* renderer, PaletteImage&& image) :
    _image(std::move(image)),
    _renderer(renderer),
    _textures()
{
}
PaletteImageMaster::PaletteImageMaster(PaletteImageMaster&& rhs) :
    _image(std::move(rhs._image)),
    _renderer(rhs._renderer),
    _textures(std::move(rhs._textures))
{
    rhs._renderer = nullptr;
}
PaletteImageMaster::~PaletteImageMaster() {
    for (auto pair = _textures.begin(); pair != _textures.end(); ++pair)
        SDL_DestroyTexture(pair->second);
}

const PaletteImage& PaletteImageMaster::getImage() const {
    return _image;
}
void PaletteImageMaster::setImage(PaletteImage&& image) {
    _image = std::move(image);
    for (auto pair = _textures.begin(); pair != _textures.end(); ++pair)
        SDL_DestroyTexture(pair->second);
}

void PaletteImageMaster::draw(Palette<Color4>* palette, Image4& screen, const Rect2<double>& bounds) {
    if (_textures.find(palette) == _textures.end())
        _textures.emplace(palette, createTexture(palette));

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
            Color4::flatten(pixel, (*palette)[_image.atParameterization(t, s)]);
        }
    }
}
void PaletteImageMaster::draw(Palette<Color4>* palette, SDL_Renderer* renderer, const Rect2<double>& bounds) {
    SDL_Rect destination{ (int)bounds.x, (int)bounds.y, (int)bounds.width, (int)bounds.height };
    if (_textures.find(palette) == _textures.end())
        _textures.emplace(palette, createTexture(palette));
    SDL_RenderCopy(renderer, _textures[palette], nullptr, &destination);
}