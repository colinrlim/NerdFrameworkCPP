#include "ImageBatcher.h"
#include "Math.h"

ImageBatcher::ImageBatcher(const ImageBatcher& rhs) :
    _image(std::move(rhs._image)),
    _renderer(nullptr),
    _texture(nullptr)
{ }
ImageBatcher& ImageBatcher::operator=(const ImageBatcher& rhs) { return *this; }
ImageBatcher& ImageBatcher::operator=(ImageBatcher&& rhs) { return *this; }

ImageBatcher::ImageBatcher(SDL_Renderer* renderer, Image4&& image) :
    _image(std::move(image)),
    _renderer(renderer),
    _texture(SDL_CreateTexture(_renderer, SDL_PIXELFORMAT_ABGR8888, SDL_TEXTUREACCESS_STATIC, _image.width(), _image.height()))
{
}
ImageBatcher::ImageBatcher(ImageBatcher&& rhs) :
    _image(std::move(rhs._image)),
    _renderer(rhs._renderer),
    _texture(rhs._texture)
{
    rhs._texture = nullptr;
    rhs._renderer = nullptr;
}
ImageBatcher::~ImageBatcher() {
    if (_texture != nullptr)
        SDL_DestroyTexture(_texture);
}

const Image4& ImageBatcher::getImage() const {
    return _image;
}
void ImageBatcher::setImage(Image4&& image) {
    _image = std::move(image);
    SDL_DestroyTexture(_texture);
    _texture = SDL_CreateTexture(_renderer, SDL_PIXELFORMAT_ABGR8888, SDL_TEXTUREACCESS_STATIC, _image.width(), _image.height());
}

void ImageBatcher::draw(Image4& screen, const Rect2<double>& bounds) {
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
            Color4::flatten(pixel, _image.colorAt(t, s));
        }
    }
}
void ImageBatcher::draw(SDL_Renderer* renderer, const Rect2<double>& bounds) {
    SDL_Rect destination{ (int)bounds.x, (int)bounds.y, (int)bounds.width, (int)bounds.height };
    SDL_RenderCopy(renderer, _texture, nullptr, &destination);
}