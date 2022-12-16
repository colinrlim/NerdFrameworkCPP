#include "TileBatch.h"
#include "Math.h"

TileBatch::TileBatch(const TileBatch& rhs) :
    _renderer(nullptr),
    grid(1, 1)
{ }
TileBatch& TileBatch::operator=(const TileBatch& rhs) { return *this; }
TileBatch& TileBatch::operator=(TileBatch&& rhs) { return *this; }

SDL_Texture* TileBatch::createTexture(const Image4& image) const {
    SDL_Texture* texture = SDL_CreateTexture(_renderer, SDL_PIXELFORMAT_ABGR8888, SDL_TEXTUREACCESS_STATIC, image.width(), image.height());
    SDL_UpdateTexture(texture, nullptr, image.data, image.width() * 4);
    return texture;
}

TileBatch::TileBatch(SDL_Renderer* renderer, const Grid2<uint8_t>& grid, const std::map<uint8_t, Image4>& tileMap) :
    _imageMap(tileMap),
    _renderer(renderer),
    grid(grid)
{
    for (auto pair = _imageMap.begin(); pair != _imageMap.end(); ++pair)
        _textureMap[pair->first] = createTexture(pair->second);
}
TileBatch::TileBatch(SDL_Renderer* renderer, Grid2<uint8_t>&& grid, std::map<uint8_t, Image4>&& tileMap) :
    _imageMap(std::move(tileMap)),
    _renderer(renderer),
    grid(std::move(grid))
{
    for (auto pair = _imageMap.begin(); pair != _imageMap.end(); ++pair)
        _textureMap[pair->first] = createTexture(pair->second);
}
TileBatch::TileBatch(SDL_Renderer* renderer, const Grid2<uint8_t>& grid) :
    _renderer(renderer),
    grid(grid)
{ }
TileBatch::TileBatch(SDL_Renderer* renderer, Grid2<uint8_t>&& grid) :
    _renderer(renderer),
    grid(std::move(grid))
{ }
TileBatch::TileBatch(TileBatch&& rhs) :
    _imageMap(std::move(rhs._imageMap)),
    _textureMap(std::move(rhs._textureMap)),
    _renderer(rhs._renderer),
    grid(std::move(rhs.grid))
{ }
TileBatch::~TileBatch() {
    for (auto pair = _textureMap.begin(); pair != _textureMap.end(); ++pair)
        SDL_DestroyTexture(pair->second);
}

const Image4& TileBatch::getTileImage(uint8_t key) const {
    return _imageMap.at(key);
}
void TileBatch::setTileImage(uint8_t key, const Image4& image) {
    _imageMap[key] = image;
    _textureMap[key] = createTexture(_imageMap[key]);
}
void TileBatch::setTileImage(uint8_t key, Image4&& image) {
    _imageMap[key] = std::move(image);
    _textureMap[key] = createTexture(_imageMap[key]);
}

void TileBatch::draw(Image4& screen, const Rect2<double>& bounds) {
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

void TileBatch::draw(SDL_Renderer* renderer, const Rect2<double>& bounds) {
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