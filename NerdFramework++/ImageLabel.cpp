#include "ImageLabel.h"
#include "Math.h"

ImageLabel::ImageLabel(const ImageLabel& rhs) :
    UIObject(rhs.getPosition(), rhs.getSize()),
    _image(std::move(rhs._image)),
    _renderer(nullptr),
    _texture(nullptr)
{ }
ImageLabel& ImageLabel::operator=(const ImageLabel& rhs) { return *this; }
ImageLabel& ImageLabel::operator=(ImageLabel&& rhs) { return *this; }

ImageLabel::ImageLabel(Image4&& image, const UDim2& position, const UDim2& size) :
    UIObject(position, size),
    _image(std::move(image)),
    _renderer(nullptr),
    _texture(nullptr)
{ }
ImageLabel::ImageLabel(ImageLabel&& rhs) :
    UIObject(std::move(rhs)),
    _image(std::move(rhs._image)),
    _renderer(rhs._renderer),
    _texture(rhs._texture)
{
    rhs._texture = nullptr;
    rhs._renderer = nullptr;
}
ImageLabel::~ImageLabel() {
    if (_texture != nullptr)
        SDL_DestroyTexture(_texture);
}

const Image4& ImageLabel::getImage() const {
    return _image;
}
void ImageLabel::setImage(Image4&& image) {
    _image = std::move(image);
    if (_renderer != nullptr) {
        SDL_DestroyTexture(_texture);
        _texture = SDL_CreateTexture(_renderer, SDL_PIXELFORMAT_ABGR8888, SDL_TEXTUREACCESS_STATIC, _image.width(), _image.height());
        SDL_UpdateTexture(_texture, nullptr, image.data, image.width() * 4);
    }
}

void ImageLabel::update(double delta) {
    UIObject::update(delta);
}
void ImageLabel::draw(Image4& screen, const Rect2<double>& scope) {
    UIObject::draw(screen, scope);
    if (visible == false) return;

    Rect2<double> childScope(getPosition(), getSize(), scope);

    // Fit to screen bounds
    const double maxWidth = screen.width();
    const double maxHeight = screen.height();
    double xMinConstrained = Math::max(0.0, childScope.x);
    double yMinConstrained = Math::max(0.0, childScope.y);
    double xMaxConstrained = Math::min(childScope.x + childScope.width, maxWidth - 1.0);
    double yMaxConstrained = Math::min(childScope.y + childScope.height, maxHeight - 1.0);

    // Render object fill color (image) on top of pre-existing
    for (size_t y = (int)yMinConstrained; y <= (int)yMaxConstrained; y++) {
        double s = (y - childScope.y) / childScope.height;
        for (size_t x = (int)xMinConstrained; x <= (int)xMaxConstrained; x++) {
            double t = (x - childScope.x) / childScope.width;
            void* pixel = screen.pixelAt(x, y);
            Color4::flatten(pixel, _image.colorAt(t, s));
        }
    }
}
void ImageLabel::draw(SDL_Renderer* renderer, const Rect2<double>& scope) {
    UIObject::draw(renderer, scope);
    Rect2<double> childScope(getPosition(), getSize(), scope);

    if (_texture == nullptr) {
        _renderer = renderer;
        _texture = SDL_CreateTexture(_renderer, SDL_PIXELFORMAT_ABGR8888, SDL_TEXTUREACCESS_STATIC, _image.width(), _image.height());
        SDL_UpdateTexture(_texture, nullptr, _image.data, _image.width() * 4);
    }

    SDL_Rect destination{ (int)childScope.x, (int)childScope.y, (int)childScope.width, (int)childScope.height };
    SDL_RenderCopy(_renderer, _texture, nullptr, &destination);
}