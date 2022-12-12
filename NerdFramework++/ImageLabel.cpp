#include "ImageLabel.h"
#include "Math.h"

ImageLabel::ImageLabel(const ImageLabel& rhs) :
    UIObject(rhs.getPosition(), rhs.getSize()),
    _image(rhs._image),
    _texture(nullptr),
    _renderer(nullptr)
{ }
ImageLabel& ImageLabel::operator=(const ImageLabel& rhs) { return *this; }

ImageLabel::ImageLabel(const UDim2& position, const UDim2& size) :
    UIObject(position, size),
    _image(Image4::none),
    _texture(nullptr),
    _renderer(nullptr)
{ }
ImageLabel::ImageLabel(Image4&& image, const UDim2& position, const UDim2& size) :
    UIObject(position, size),
    _image(image),
    _texture(nullptr),
    _renderer(nullptr)
{ }
ImageLabel::~ImageLabel() {
    SDL_DestroyTexture(_texture);
}

const Image4& ImageLabel::getImage() const {
    return _image;
}
void ImageLabel::setImage(Image4&& image) {
    _image = std::move(image);
    if (_renderer != nullptr) {
        SDL_DestroyTexture(_texture);
        _texture = SDL_CreateTexture(_renderer, SDL_PIXELFORMAT_ABGR8888, SDL_TEXTUREACCESS_STATIC, _image.getWidth(), _image.getHeight());
    }
}

void ImageLabel::update(double delta) {
    UIObject::update(delta);
}
void ImageLabel::draw(Image4& screen, const Rect2<double>& scope) {
    UIObject::draw(screen, scope);
    if (visible == false) return;

    Rect2<double> childScope(getPosition(), getSize(), scope);

    // Object bounds; Doesn't use AbsolutePosition() and AbsoluteSize() for optimization purposes
    double xMin = childScope.x;
    double yMin = childScope.y;
    double xMax = xMin + childScope.width;
    double yMax = yMin + childScope.height;

    // Fit to screen bounds
    const double maxWidth = screen.getWidth();
    const double maxHeight = screen.getHeight();
    xMin = Math::max(0.0, xMin);
    yMin = Math::max(0.0, yMin);
    xMax = Math::min(xMax, maxWidth - 1.0);
    yMax = Math::min(yMax, maxHeight - 1.0);

    // Render object fill color (image) on top of pre-existing
    double xLength = xMax - xMin;
    double yLength = yMax - yMin;
    for (size_t y = (int)yMin; y <= (int)yMax; y++) {
        double s = (y - yMin) / yLength;
        for (size_t x = (int)xMin; x <= (int)xMax; x++) {
            double t = (x - xMin) / xLength;
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
        _texture = SDL_CreateTexture(_renderer, SDL_PIXELFORMAT_ABGR8888, SDL_TEXTUREACCESS_STATIC, _image.getWidth(), _image.getHeight());
    }

    SDL_Rect destination{ childScope.x, childScope.y, childScope.width, childScope.height };
    SDL_RenderCopy(_renderer, _texture, nullptr, &destination);
}