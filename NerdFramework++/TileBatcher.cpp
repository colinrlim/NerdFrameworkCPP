#include "TileBatcher.h"
#include "Math.h"

TileBatcher::TileBatcher(const TileBatcher& rhs) :
    _renderer(nullptr),
    _grid(1, 1)
{ }
TileBatcher& TileBatcher::operator=(const TileBatcher& rhs) { return *this; }
TileBatcher& TileBatcher::operator=(TileBatcher&& rhs) { return *this; }

SDL_Texture* TileBatcher::createTexture(const Image4& image) const {
    SDL_Texture* texture = SDL_CreateTexture(_renderer, SDL_PIXELFORMAT_ABGR8888, SDL_TEXTUREACCESS_STATIC, image.width(), image.height());
    SDL_SetTextureBlendMode(texture, SDL_BLENDMODE_BLEND);
    SDL_UpdateTexture(texture, nullptr, image.data, image.width() * 4);
    return texture;
}

TileBatcher::TileBatcher(SDL_Renderer* renderer) :
    _renderer(renderer),
    _grid(1, 1)
{ }
TileBatcher::TileBatcher(TileBatcher&& rhs) :
    _tileTypes(std::move(rhs._tileTypes)),
    _tileTypesTextures(std::move(rhs._tileTypesTextures)),
    _renderer(rhs._renderer),
    _grid(std::move(rhs._grid))
{ }
TileBatcher::~TileBatcher() {
    for (auto pair = _tileTypesTextures.begin(); pair != _tileTypesTextures.end(); ++pair)
        SDL_DestroyTexture(pair->second);
}

uint8_t* TileBatcher::data() const {
    return _grid.data();
}
uint8_t& TileBatcher::at(size_t x, size_t y) const {
    return _grid.get(x, y);
}
size_t TileBatcher::size() const {
    return _grid.size();
}

void TileBatcher::setGrid(const Grid2<uint8_t>& grid) {
    _grid = grid;
}
void TileBatcher::setGrid(Grid2<uint8_t>&& grid) {
    _grid = std::move(grid);
}
void TileBatcher::setTileTypes(const std::map<uint8_t, Image4>& tileTypes) {
    _tileTypes = tileTypes;
}
void TileBatcher::setTileTypes(std::map<uint8_t, Image4>&& tileTypes) {
    _tileTypes = std::move(tileTypes);
}

void TileBatcher::draw(Image4& screen, const Rect2<double>& bounds) {
    const double maxWidth = screen.width();
    const double maxHeight = screen.height();

    size_t width = _grid.width();
    size_t height = _grid.height();

    Rect2<double> destination = bounds;
    for (size_t y = 0; y < height; y++) {
        for (size_t x = 0; x < width; x++) {
            auto pair = _tileTypes.find(_grid.get(x, y));
            if (pair == _tileTypes.end()) continue;
            const Image4& image = pair->second;

            destination.x = bounds.x + x * bounds.width;
            destination.y = bounds.y + y * bounds.height;

            // Fit to screen bounds
            double xMinConstrained = Math::max(0.0, destination.x);
            double yMinConstrained = Math::max(0.0, destination.y);
            double xMaxConstrained = Math::min(destination.x + destination.width, maxWidth - 1.0);
            double yMaxConstrained = Math::min(destination.y + destination.height, maxHeight - 1.0);

            // Render object fill color (image) on top of pre-existing
            for (size_t y = (int)yMinConstrained; y < (int)yMaxConstrained; y++) {
                double s = (y - destination.y) / destination.height;
                for (size_t x = (int)xMinConstrained; x < (int)xMaxConstrained; x++) {
                    double t = (x - destination.x) / destination.width;
                    void* pixel = screen.pixelAt(x, y);
                    Color4::flatten(pixel, image.atParameterization(t, s));
                }
            }
        }
    }
}
void TileBatcher::draw(SDL_Renderer* renderer, const Rect2<double>& bounds) {
    size_t width = _grid.width();
    size_t height = _grid.height();

    SDL_Rect destination{ (int)bounds.x, (int)bounds.y, (int)bounds.width, (int)bounds.height };
    for (size_t y = 0; y < height; y++) {
        for (size_t x = 0; x < width; x++) {
            const uint8_t& key = _grid.get(x, y);
            if (_tileTypesTextures.find(key) == _tileTypesTextures.end())
                _tileTypesTextures.emplace(key, createTexture(_tileTypes[key]));
            destination.x = (int)(bounds.x + x * bounds.width);
            destination.y = (int)(bounds.y + y * bounds.height);
            SDL_RenderCopy(renderer, _tileTypesTextures[key], nullptr, &destination);
        }
    }
}

void TileBatcher::draw(Image4& screen, const std::function<const Rect2<double>(size_t x, size_t y)>& boundsFunction) {
    const double maxWidth = screen.width();
    const double maxHeight = screen.height();

    size_t width = _grid.width();
    size_t height = _grid.height();

    for (size_t y = 0; y < height; y++) {
        for (size_t x = 0; x < width; x++) {
            auto pair = _tileTypes.find(_grid.get(x, y));
            if (pair == _tileTypes.end()) continue;
            const Image4& image = pair->second;
            const Rect2<double> destination(boundsFunction(x, y));

            // Fit to screen bounds
            double xMinConstrained = Math::max(0.0, destination.x);
            double yMinConstrained = Math::max(0.0, destination.y);
            double xMaxConstrained = Math::min(destination.x + destination.width, maxWidth - 1.0);
            double yMaxConstrained = Math::min(destination.y + destination.height, maxHeight - 1.0);

            // Render object fill color (image) on top of pre-existing
            for (size_t y = (int)yMinConstrained; y < (int)yMaxConstrained; y++) {
                double s = (y - destination.y) / destination.height;
                for (size_t x = (int)xMinConstrained; x < (int)xMaxConstrained; x++) {
                    double t = (x - destination.x) / destination.width;
                    void* pixel = screen.pixelAt(x, y);
                    Color4::flatten(pixel, image.atParameterization(t, s));
                }
            }
        }
    }
}
void TileBatcher::draw(SDL_Renderer* renderer, const std::function<const SDL_Rect(size_t x, size_t y)>& boundsFunction) {
    size_t width = _grid.width();
    size_t height = _grid.height();

    for (size_t y = 0; y < height; y++) {
        for (size_t x = 0; x < width; x++) {
            const uint8_t& key = _grid.get(x, y);
            if (_tileTypesTextures.find(key) == _tileTypesTextures.end())
                _tileTypesTextures.emplace(key, createTexture(_tileTypes[key]));

            const SDL_Rect destination(boundsFunction(x, y));
            SDL_RenderCopy(renderer, _tileTypesTextures[key], nullptr, &destination);
        }
    }
}