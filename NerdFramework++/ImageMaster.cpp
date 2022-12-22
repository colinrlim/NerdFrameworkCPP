#include "ImageMaster.h"
#include "Math.h"

ImageMaster::ImageMaster(const ImageMaster& rhs) :
    _image(std::move(rhs._image)),
    _renderer(nullptr),
    _texture(nullptr)
{ }
ImageMaster& ImageMaster::operator=(const ImageMaster& rhs) { return *this; }
ImageMaster& ImageMaster::operator=(ImageMaster&& rhs) { return *this; }

ImageMaster::ImageMaster(SDL_Renderer* renderer, Image4&& image) :
    _image(std::move(image)),
    _renderer(renderer),
    _texture(SDL_CreateTexture(_renderer, SDL_PIXELFORMAT_ABGR8888, SDL_TEXTUREACCESS_STATIC, _image.width(), _image.height()))
{
}
ImageMaster::ImageMaster(ImageMaster&& rhs) :
    _image(std::move(rhs._image)),
    _renderer(rhs._renderer),
    _texture(rhs._texture)
{
    rhs._texture = nullptr;
    rhs._renderer = nullptr;
}
ImageMaster::~ImageMaster() {
    if (_texture != nullptr)
        SDL_DestroyTexture(_texture);
}

const Image4& ImageMaster::getImage() const {
    return _image;
}
void ImageMaster::setImage(Image4&& image) {
    _image = std::move(image);
    SDL_DestroyTexture(_texture);
    _texture = SDL_CreateTexture(_renderer, SDL_PIXELFORMAT_ABGR8888, SDL_TEXTUREACCESS_STATIC, _image.width(), _image.height());
}

void ImageMaster::draw(Image4& screen, const Rect2<double>& bounds) {
    // Fit to screen bounds
    const double maxWidth = screen.width();
    const double maxHeight = screen.height();
    double xMinConstrained = Math::max(0.0, bounds.x);
    double yMinConstrained = Math::max(0.0, bounds.y);
    double xMaxConstrained = Math::min(bounds.x + bounds.width, maxWidth - 1.0);
    double yMaxConstrained = Math::min(bounds.y + bounds.height, maxHeight - 1.0);

    // Render object fill color (image) on top of pre-existing
    for (size_t y = (int)yMinConstrained; y <= (int)yMaxConstrained; y++) {
        double s = (y - bounds.y) / bounds.height;
        for (size_t x = (int)xMinConstrained; x <= (int)xMaxConstrained; x++) {
            double t = (x - bounds.x) / bounds.width;
            void* pixel = screen.pixelAt(x, y);
            Color4::flatten(pixel, _image.atParameterization(t, s));
        }
    }
}
void ImageMaster::draw(SDL_Renderer* renderer, const Rect2<double>& bounds) {
    SDL_Rect destination{ (int)bounds.x, (int)bounds.y, (int)bounds.width, (int)bounds.height };
    SDL_RenderCopy(renderer, _texture, nullptr, &destination);
}