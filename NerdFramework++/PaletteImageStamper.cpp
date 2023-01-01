#include "PaletteImageStamper.h"
#include "Triangle2.h"
#include "Math.h"
#include <iostream>
#include "Triangle3.h"

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
    const double xMinConstrained = Math::max(0.0, bounds.x);
    const double yMinConstrained = Math::max(0.0, bounds.y);
    const double xMaxConstrained = Math::min(bounds.x + bounds.width, maxWidth);
    const double yMaxConstrained = Math::min(bounds.y + bounds.height, maxHeight);

    // Render object fill color (image) on top of pre-existing
    for (size_t y = (int)yMinConstrained, virtY = y - (size_t)bounds.y; y < (int)yMaxConstrained; y++, virtY++) {
        const double s = virtY / bounds.height;
        for (size_t x = (int)xMinConstrained, virtX = x - (size_t)bounds.x; x < (int)xMaxConstrained; x++, virtX++) {
            const double t = virtX / bounds.width;
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
void PaletteImageStamper::draw(const Palette<Color4>& palette, Image4& screen, const Rect2<double>& bounds, ImageFlipOptions flipOptions, ImageScaleType scaleType) {
    if (scaleType == ImageScaleType::FIT) {
        const double imageRatio = (double)_image.width() / (double)_image.height();
        const double boundsRatio = bounds.width / bounds.height;
        if (boundsRatio > imageRatio)
            draw(palette, screen, Rect2<double>{ bounds.x, bounds.y, imageRatio * bounds.height, bounds.height }, flipOptions, ImageScaleType::STRETCH);
        else
            draw(palette, screen, Rect2<double>{ bounds.x, bounds.y, bounds.width, bounds.width / imageRatio }, flipOptions, ImageScaleType::STRETCH);
        return;
    }

    // Fit to screen bounds
    const double maxWidth = screen.width();
    const double maxHeight = screen.height();
    const double xMinConstrained = Math::max(0.0, bounds.x);
    const double yMinConstrained = Math::max(0.0, bounds.y);
    double xMaxConstrained = Math::min(bounds.x + bounds.width, maxWidth);
    double yMaxConstrained = Math::min(bounds.y + bounds.height, maxHeight);

    // Render object fill color (image) on top of pre-existing
    if (scaleType == ImageScaleType::STRETCH) {
        for (size_t y = (int)yMinConstrained, virtY = y - (size_t)bounds.y; y < (int)yMaxConstrained; y++, virtY++) {
            const double s = transformedS(virtY / bounds.height, flipOptions);
            for (size_t x = (int)xMinConstrained, virtX = x - (size_t)bounds.x; x < (int)xMaxConstrained; x++, virtX++) {
                const double t = transformedT(virtX / bounds.width, flipOptions);
                void* pixel = screen.pixelAt(x, y);
                Color4::flatten(pixel, palette[_image.atParameterization(t, s)]);
            }
        }
    } else if (scaleType == ImageScaleType::TILE) {
        for (size_t y = (int)yMinConstrained, virtY = y - (size_t)bounds.y; y < (int)yMaxConstrained; y++, virtY++) {
            const size_t transY = transformedY(virtY % _image.height(), _image.height(), flipOptions);
            for (size_t x = (int)xMinConstrained, virtX = x - (size_t)bounds.x; x < (int)xMaxConstrained; x++, virtX++) {
                const size_t transX = transformedX(virtX % _image.height(), _image.width(), flipOptions);
                void* pixel = screen.pixelAt(x, y);
                Color4::flatten(pixel, palette[*_image.pixelAt(transX, transY)]);
            }
        }
    } else if (scaleType == ImageScaleType::CROP) {
        if (xMaxConstrained - xMinConstrained > _image.width())
            xMaxConstrained = xMinConstrained + _image.width();
        if (yMaxConstrained - yMinConstrained > _image.height())
            yMaxConstrained = yMinConstrained + _image.height();
        for (size_t y = (int)yMinConstrained, virtY = y - (size_t)bounds.y; y < (int)yMaxConstrained; y++, virtY++) {
            const size_t transY = transformedY(virtY, _image.height(), flipOptions);
            for (size_t x = (int)xMinConstrained, virtX = x - (size_t)bounds.x; x < (int)xMaxConstrained; x++, virtX++) {
                const size_t transX = transformedX(virtX, _image.width(), flipOptions);
                void* pixel = screen.pixelAt(x, y);
                Color4::flatten(pixel, palette[*_image.pixelAt(transX, transY)]);
            }
        }
    }
}
void PaletteImageStamper::draw(const Palette<Color4>& palette, SDL_Renderer* renderer, const Rect2<double>& bounds, ImageFlipOptions flipOptions, ImageScaleType scaleType) {
    const Palette<Color4>* palettePtr = &palette;
    SDL_Rect destination{ (int)bounds.x, (int)bounds.y, (int)bounds.width, (int)bounds.height };
    if (_textures.find(palettePtr) == _textures.end())
        _textures.emplace(palettePtr, createTexture(palette));
    
    if (scaleType == ImageScaleType::STRETCH) {
        SDL_Rect destination{ (int)bounds.x, (int)bounds.y, (int)bounds.width, (int)bounds.height };
        SDL_RenderCopyEx(renderer, _textures[palettePtr], nullptr, &destination, 0, nullptr, (SDL_RendererFlip)flipOptions);
    } else if (scaleType == ImageScaleType::TILE) {
        int imageWidth = _image.width(), imageHeight = _image.height();
        SDL_Rect destination{ (int)bounds.x, (int)bounds.y, _image.width(), _image.height() };
        const double yEnd = bounds.y + bounds.height;
        while (destination.y <= yEnd) {
            SDL_Rect source{ 0, 0, destination.w, destination.h };
            if (destination.y + destination.h > yEnd) {
                destination.h = (int)(yEnd - destination.y);
                source.h = destination.h;
            }
            const double xEnd = bounds.x + bounds.width;
            while (destination.x <= xEnd) {
                if (destination.x + destination.w > xEnd) {
                    destination.w = (int)(xEnd - destination.x);
                    source.w = destination.w;
                }
                SDL_RenderCopyEx(renderer, _textures[palettePtr], &source, &destination, 0, nullptr, (SDL_RendererFlip)flipOptions);
                destination.x += imageWidth;
            }
            destination.x = (int)bounds.x;
            destination.y += imageHeight;
            destination.w = imageWidth;
            destination.h = imageHeight;
        }
    } else if (scaleType == ImageScaleType::FIT) {
        const double imageRatio = (double)_image.width() / (double)_image.height();
        const double boundsRatio = bounds.width / bounds.height;
        if (boundsRatio > imageRatio) {
            SDL_Rect destination{ (int)bounds.x, (int)bounds.y, (int)(imageRatio * bounds.height), (int)bounds.height };
            SDL_RenderCopyEx(renderer, _textures[palettePtr], nullptr, &destination, 0, nullptr, (SDL_RendererFlip)flipOptions);
        } else {
            SDL_Rect destination{ (int)bounds.x, (int)bounds.y, (int)bounds.width, (int)(bounds.width / imageRatio) };
            SDL_RenderCopyEx(renderer, _textures[palettePtr], nullptr, &destination, 0, nullptr, (SDL_RendererFlip)flipOptions);
        }
    } else if (scaleType == ImageScaleType::CROP) {
        SDL_Rect source{ 0, 0, bounds.width < _image.width() ? (int)bounds.width : _image.width(), bounds.height < _image.height() ? (int)bounds.height : _image.height() };
        SDL_Rect destination{ (int)bounds.x, (int)bounds.y, source.w, source.h };
        SDL_RenderCopyEx(renderer, _textures[palettePtr], &source, &destination, 0, nullptr, (SDL_RendererFlip)flipOptions);
    }
}
void PaletteImageStamper::draw(const Palette<Color4>& palette, Image4& screen, const Rect2<double>& source, const Rect2<double>& destination, double degrees, const Vector2& origin, ImageFlipOptions flipOptions) const {
    // Define corner positions of image, offset by origin
    Vector2 topLeft(-origin.x, -origin.y);
    Vector2 topRight(destination.width - origin.x, -origin.y);
    Vector2 bottomLeft(-origin.x, destination.height - origin.y);
    Vector2 bottomRight(destination.width - origin.x, destination.height - origin.y);
    // Rotate all corners
    double radians = Math::degreesToRadians(degrees);
    topLeft.rotate(radians);
    topRight.rotate(radians);
    bottomLeft.rotate(radians);
    bottomRight.rotate(radians);
    // Unoffset corners
    Vector2 offset(destination.x + origin.x, destination.y + origin.y);
    topLeft += offset;
    topRight += offset;
    bottomLeft += offset;
    bottomRight += offset;

    // Parameterize area
    Vector2 xAxis(topRight - topLeft);
    Vector2 yAxis(bottomLeft - topLeft);
    
    // Get new image bounds
    Vector2 newTopLeft(Math::min(std::vector<double>{ topLeft.x, topRight.x, bottomLeft.x, bottomRight.x, destination.x }), Math::min(std::vector<double>{ topLeft.y, topRight.y, bottomLeft.y, bottomRight.y, destination.y }));
    Vector2 newBottomRight(Math::max(std::vector<double>{ topLeft.x, topRight.x, bottomLeft.x, bottomRight.x, destination.x + destination.width }), Math::max(std::vector<double>{ topLeft.y, topRight.y, bottomLeft.y, bottomRight.y, destination.y + destination.width }));
    double newWidth = newBottomRight.x - newTopLeft.x;
    double newHeight = newBottomRight.y - newTopLeft.y;

    // Fit to screen bounds
    const double maxWidth = screen.width();
    const double maxHeight = screen.height();
    const double xMinConstrained = Math::max(0.0, newTopLeft.x);
    const double yMinConstrained = Math::max(0.0, newTopLeft.y);
    const double xMaxConstrained = Math::min(newBottomRight.x, maxWidth);
    const double yMaxConstrained = Math::min(newBottomRight.y, maxHeight);

    const double imageClipWidthRatio = (source.width / _image.width());
    const double imageClipHeightRatio = (source.height / _image.height());
    for (size_t y = (int)yMinConstrained; y < (int)yMaxConstrained; y++) {
        for (size_t x = (int)xMinConstrained; x < (int)xMaxConstrained; x++) {
            Vector2 pos(x - topLeft.x, y - topLeft.y);

            /* Project position onto virtual axes
             * a⋅b = |a||b|cos(theta)
             * a⋅b/|a| = |b|cos(theta) -> projection of B onto A
             */
            double t = (Vector2::dot(xAxis, pos) / destination.width) / destination.width;
            double s = (Vector2::dot(yAxis, pos) / destination.height) / destination.height;

            // Check if parameterization is within image bounds
            if (t >= 1.0 || s >= 1.0 || t < 0.0 || s < 0.0) continue;

            t = transformedT(t * imageClipWidthRatio, flipOptions);
            s = transformedS(s * imageClipHeightRatio, flipOptions);
            void* pixel = screen.pixelAt(x, y);
            Color4::flatten(pixel, palette[_image.atParameterization(t, s)]);
        }
    }
}
void PaletteImageStamper::draw(const Palette<Color4>& palette, Image4& screen, const Rect2<double>& bounds, double degrees, const Vector2i& origin, ImageFlipOptions flipOptions, ImageScaleType scaleType) {
    if (scaleType == ImageScaleType::STRETCH) {
        Rect2<double> source(0.0, 0.0, _image.width(), _image.height());
        draw(palette, screen, source, bounds, degrees, origin, flipOptions);
    } else if (scaleType == ImageScaleType::TILE) {
        int imageWidth = _image.width(), imageHeight = _image.height();
        Rect2<double> destination(bounds.x, bounds.y, _image.width(), _image.height());
        const double yEnd = bounds.y + bounds.height;
        while (destination.y <= yEnd) {
            Rect2<double> source(0.0, 0.0, destination.width, destination.height);
            if (destination.y + destination.height > yEnd) {
                destination.height = yEnd - destination.y;
                source.height = destination.height;
            }
            const double xEnd = bounds.x + bounds.width;
            while (destination.x <= xEnd) {
                if (destination.x + destination.width > xEnd) {
                    destination.width = (xEnd - destination.x);
                    source.width = destination.width;
                }
                draw(palette, screen, source, destination, degrees, origin, flipOptions);
                destination.x += imageWidth;
            }
            destination.x = bounds.x;
            destination.y += imageHeight;
            destination.width = imageWidth;
            destination.height = imageHeight;
        }
    } else if (scaleType == ImageScaleType::FIT) {
        Rect2<double> source(0.0, 0.0, _image.width(), _image.height());
        const double imageRatio = (double)_image.width() / (double)_image.height();
        const double boundsRatio = bounds.width / bounds.height;
        if (boundsRatio > imageRatio) {
            Rect2<double> destination{ bounds.x, bounds.y, (imageRatio * bounds.height), bounds.height };
            draw(palette, screen, source, destination, degrees, origin, flipOptions);
        } else {
            Rect2<double> destination{ bounds.x, bounds.y, bounds.width, (bounds.width / imageRatio) };
            draw(palette, screen, source, destination, degrees, origin, flipOptions);
        }
    } else if (scaleType == ImageScaleType::CROP) {
        Rect2<double> source(0, 0, bounds.width < _image.width() ? bounds.width : _image.width(), bounds.height < _image.height() ? bounds.height : _image.height());
        Rect2<double> destination(bounds.x, bounds.y, source.width, source.height);
        draw(palette, screen, source, destination, degrees, origin, flipOptions);
     }
}
void PaletteImageStamper::draw(const Palette<Color4>& palette, SDL_Renderer* renderer, const Rect2<double>& bounds, double degrees, const Vector2i& origin, ImageFlipOptions flipOptions, ImageScaleType scaleType) {
    const Palette<Color4>* palettePtr = &palette;
    if (_textures.find(palettePtr) == _textures.end())
        _textures.emplace(palettePtr, createTexture(palette));

    SDL_Point point{ origin.x, origin.y };
    if (scaleType == ImageScaleType::STRETCH) {
        SDL_Rect destination{ (int)bounds.x, (int)bounds.y, (int)bounds.width, (int)bounds.height };
        SDL_RenderCopyEx(renderer, _textures[palettePtr], nullptr, &destination, degrees, &point, (SDL_RendererFlip)flipOptions);
    } else if (scaleType == ImageScaleType::TILE) {
        int imageWidth = _image.width(), imageHeight = _image.height();
        SDL_Rect destination{ (int)bounds.x, (int)bounds.y, imageWidth, imageHeight };
        const double yEnd = bounds.y + bounds.height;
        while (destination.y <= yEnd) {
            SDL_Rect source{ 0, 0, destination.w, destination.h };
            if (destination.y + destination.h > yEnd) {
                destination.h = (int)(yEnd - destination.y);
                source.h = destination.h;
            }
            const double xEnd = bounds.x + bounds.width;
            while (destination.x <= xEnd) {
                if (destination.x + destination.w > xEnd) {
                    destination.w = (int)(xEnd - destination.x);
                    source.w = destination.w;
                }
                SDL_RenderCopyEx(renderer, _textures[palettePtr], &source, &destination, degrees, &point, (SDL_RendererFlip)flipOptions);
                destination.x += imageWidth;
            }
            destination.x = (int)bounds.x;
            destination.y += imageHeight;
            destination.w = imageWidth;
            destination.h = imageHeight;
        }
    } else if (scaleType == ImageScaleType::FIT) {
        const double imageRatio = (double)_image.width() / (double)_image.height();
        const double boundsRatio = bounds.width / bounds.height;
        if (boundsRatio > imageRatio) {
            SDL_Rect destination{ (int)bounds.x, (int)bounds.y, (int)(imageRatio * bounds.height), (int)bounds.height };
            SDL_RenderCopyEx(renderer, _textures[palettePtr], nullptr, &destination, degrees, &point, (SDL_RendererFlip)flipOptions);
        } else {
            SDL_Rect destination{ (int)bounds.x, (int)bounds.y, (int)bounds.width, (int)(bounds.width / imageRatio) };
            SDL_RenderCopyEx(renderer, _textures[palettePtr], nullptr, &destination, degrees, &point, (SDL_RendererFlip)flipOptions);
        }
    } else if (scaleType == ImageScaleType::CROP) {
        SDL_Rect source{ 0, 0, bounds.width < _image.width() ? (int)bounds.width : _image.width(), bounds.height < _image.height() ? (int)bounds.height : _image.height() };
        SDL_Rect destination{ (int)bounds.x, (int)bounds.y, source.w, source.h };
        SDL_RenderCopyEx(renderer, _textures[palettePtr], &source, &destination, degrees, &point, (SDL_RendererFlip)flipOptions);
     }
}