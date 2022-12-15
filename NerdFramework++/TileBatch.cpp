#include "TileBatcher.h"
#include "Math.h"

TileBatcher::TileBatcher(const TileBatcher& rhs) :
    _renderer(nullptr),
    grid(1, 1)
{ }
TileBatcher& TileBatcher::operator=(const TileBatcher& rhs) { return *this; }
TileBatcher& TileBatcher::operator=(TileBatcher&& rhs) { return *this; }

SDL_Texture* TileBatcher::createTexture(const Image4& image) const {
    SDL_Texture* texture = SDL_CreateTexture(_renderer, SDL_PIXELFORMAT_ABGR8888, SDL_TEXTUREACCESS_STATIC, image.width(), image.height());
    SDL_UpdateTexture(texture, nullptr, image.data, image.width() * 4);
    return texture;
}

TileBatcher::TileBatcher(SDL_Renderer* renderer, const Grid2<uint8_t>& grid, const std::map<uint8_t, Image4>& tileMap) :
    _imageMap(tileMap),
    _renderer(renderer),
    grid(grid)
{
    for (auto pair = _imageMap.begin(); pair != _imageMap.end(); ++pair)
        _textureMap[pair->first] = createTexture(pair->second);
}
TileBatcher::TileBatcher(SDL_Renderer* renderer, Grid2<uint8_t>&& grid, std::map<uint8_t, Image4>&& tileMap) :
    _imageMap(std::move(tileMap)),
    _renderer(renderer),
    grid(std::move(grid))
{
    for (auto pair = _imageMap.begin(); pair != _imageMap.end(); ++pair)
        _textureMap[pair->first] = createTexture(pair->second);
}
TileBatcher::TileBatcher(SDL_Renderer* renderer, const Grid2<uint8_t>& grid) :
    _renderer(renderer),
    grid(grid)
{ }
TileBatcher::TileBatcher(SDL_Renderer* renderer, Grid2<uint8_t>&& grid) :
    _renderer(renderer),
    grid(std::move(grid))
{ }
TileBatcher::TileBatcher(TileBatcher&& rhs) :
    _imageMap(std::move(rhs._imageMap)),
    _textureMap(std::move(rhs._textureMap)),
    _renderer(rhs._renderer),
    grid(std::move(rhs.grid))
{ }
TileBatcher::~TileBatcher() {
    for (auto pair = _textureMap.begin(); pair != _textureMap.end(); ++pair)
        SDL_DestroyTexture(pair->second);
}

const Image4& TileBatcher::getTileImage(uint8_t key) const {
    return _imageMap.at(key);
}
void TileBatcher::setTileImage(uint8_t key, const Image4& image) {
    _imageMap[key] = image;
    _textureMap[key] = createTexture(_imageMap[key]);
}
void TileBatcher::setTileImage(uint8_t key, Image4&& image) {
    _imageMap[key] = std::move(image);
    _textureMap[key] = createTexture(_imageMap[key]);
}

void TileBatcher::draw(Image4& screen, const Rect2<double>& bounds) {
    const double maxWidth = screen.width();
    const double maxHeight = screen.height();

    size_t width = grid.width();
    size_t height = grid.height();

    Rect2<double> destination = bounds;
    for (size_t y = 0; y < height; y++) {
        for (size_t x = 0; x < width; x++) {
            auto pair = _imageMap.find(grid.get(x, y));
            if (pair == _imageMap.end()) continue;
            const Image4& image = pair->second;

            destination.x = bounds.x + x * bounds.width;
            destination.y = bounds.y + y * bounds.height;

            // Fit to screen bounds
            double xMinConstrained = Math::max(0.0, destination.x);
            double yMinConstrained = Math::max(0.0, destination.y);
            double xMaxConstrained = Math::min(destination.x + destination.width, maxWidth - 1.0);
            double yMaxConstrained = Math::min(destination.y + destination.height, maxHeight - 1.0);

            // Render object fill color (image) on top of pre-existing
            for (size_t y = (int)yMinConstrained; y <= (int)yMaxConstrained; y++) {
                double s = (y - destination.y) / destination.height;
                for (size_t x = (int)xMinConstrained; x <= (int)xMaxConstrained; x++) {
                    double t = (x - destination.x) / destination.width;
                    void* pixel = screen.pixelAt(x, y);
                    Color4::flatten(pixel, image.colorAt(t, s));
                }
            }
        }
    }
}

void TileBatcher::draw(SDL_Renderer* renderer, const Rect2<double>& bounds) {
    size_t width = grid.width();
    size_t height = grid.height();

    SDL_Rect destination{ (int)bounds.x, (int)bounds.y, (int)bounds.width, (int)bounds.height };
    for (size_t y = 0; y < height; y++) {
        for (size_t x = 0; x < width; x++) {
            auto pair = _textureMap.find(grid.get(x, y));
            if (pair == _textureMap.end()) continue;
            destination.x = (int)(bounds.x + x * bounds.width);
            destination.y = (int)(bounds.y + y * bounds.height);
            SDL_RenderCopy(renderer, pair->second, nullptr, &destination);
        }
    }
}