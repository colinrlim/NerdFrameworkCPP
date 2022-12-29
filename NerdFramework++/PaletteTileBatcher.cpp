#include "PaletteTileBatcher.h"
#include "Math.h"

PaletteTileBatcher::PaletteTileBatcher(const PaletteTileBatcher& rhs) :
    _renderer(nullptr),
    _grid(1, 1),
    _paletteGrid(1, 1)
{ }
PaletteTileBatcher& PaletteTileBatcher::operator=(const PaletteTileBatcher& rhs) { return *this; }
PaletteTileBatcher& PaletteTileBatcher::operator=(PaletteTileBatcher&& rhs) { return *this; }

SDL_Texture* PaletteTileBatcher::createTexture(Image4&& image) const {
    SDL_Texture* texture = SDL_CreateTexture(_renderer, SDL_PIXELFORMAT_ABGR8888, SDL_TEXTUREACCESS_STATIC, image.width(), image.height());
    SDL_SetTextureBlendMode(texture, SDL_BLENDMODE_BLEND);
    SDL_UpdateTexture(texture, nullptr, image.data, image.width() * 4);
    return texture;
}

PaletteTileBatcher::PaletteTileBatcher(SDL_Renderer* renderer) :
    _renderer(renderer),
    _grid(1, 1),
    _paletteGrid(1, 1)
{ }
PaletteTileBatcher::PaletteTileBatcher(PaletteTileBatcher&& rhs) :
    _renderer(rhs._renderer),
    _tileTypes(std::move(rhs._tileTypes)),
    _tileTypesTextures(std::move(rhs._tileTypesTextures)),
    _paletteTypes(std::move(rhs._paletteTypes)),
    _grid(std::move(rhs._grid)),
    _paletteGrid(std::move(rhs._paletteGrid))
{ }
PaletteTileBatcher::~PaletteTileBatcher() {
    for (auto pair = _tileTypesTextures.begin(); pair != _tileTypesTextures.end(); ++pair)
        SDL_DestroyTexture(pair->second);
}

uint8_t* PaletteTileBatcher::gridData() const {
    return _grid.data();
}
uint8_t* PaletteTileBatcher::paletteGridData() const {
    return _paletteGrid.data();
}
uint8_t& PaletteTileBatcher::tileAt(size_t x, size_t y) const {
    return _grid.get(x, y);
}
uint8_t& PaletteTileBatcher::paletteAt(size_t x, size_t y) const {
    return _paletteGrid.get(x, y);
}
size_t PaletteTileBatcher::size() const {
    return _grid.size();
}

void PaletteTileBatcher::setGrid(const Grid2<uint8_t>& grid) {
    _grid = grid;
}
void PaletteTileBatcher::setGrid(Grid2<uint8_t>&& grid) {
    _grid = std::move(grid);
}
void PaletteTileBatcher::setPaletteGrid(const Grid2<uint8_t>& paletteGrid) {
    _paletteGrid = paletteGrid;
}
void PaletteTileBatcher::setPaletteGrid(Grid2<uint8_t>&& paletteGrid) {
    _paletteGrid = std::move(paletteGrid);
}

void PaletteTileBatcher::setTileTypes(const std::map<uint8_t, PaletteImage>& tileTypes) {
    _tileTypes = tileTypes;
}
void PaletteTileBatcher::setTileTypes(std::map<uint8_t, PaletteImage>&& tileTypes) {
    _tileTypes = std::move(tileTypes);
}
void PaletteTileBatcher::setPaletteTypes(const std::vector<Palette<Color4>>& palettes) {
    _paletteTypes = palettes;
}
void PaletteTileBatcher::setPaletteTypes(std::vector<Palette<Color4>>&& palettes) {
    _paletteTypes = std::move(palettes);
}

void PaletteTileBatcher::draw(Image4& screen, const Rect2<double>& bounds) {
    const double maxWidth = screen.width();
    const double maxHeight = screen.height();

    size_t width = _grid.width();
    size_t height = _grid.height();

    Rect2<double> destination = bounds;
    for (size_t y = 0; y < height; y++) {
        for (size_t x = 0; x < width; x++) {
            auto pair = _tileTypes.find(_grid.get(x, y));
            if (pair == _tileTypes.end()) continue;
            PaletteImage& image = pair->second;
            Palette<Color4>& palette = _paletteTypes[_paletteGrid.get(x, y)];

            destination.x = bounds.x + x * bounds.width;
            destination.y = bounds.y + y * bounds.height;

            // Fit to screen bounds
            double xMinConstrained = Math::max(0.0, destination.x);
            double yMinConstrained = Math::max(0.0, destination.y);
            double xMaxConstrained = Math::min(destination.x + destination.width, maxWidth);
            double yMaxConstrained = Math::min(destination.y + destination.height, maxHeight);

            // Render object fill color (image) on top of pre-existing
            for (size_t y = (int)yMinConstrained; y < (int)yMaxConstrained; y++) {
                double s = (y - destination.y) / destination.height;
                for (size_t x = (int)xMinConstrained; x < (int)xMaxConstrained; x++) {
                    double t = (x - destination.x) / destination.width;
                    void* pixel = screen.pixelAt(x, y);
                    Color4::flatten(pixel, palette[image.atParameterization(t, s)]);
                }
            }
        }
    }
}
void PaletteTileBatcher::draw(SDL_Renderer* renderer, const Rect2<double>& bounds) {
    size_t width = _grid.width();
    size_t height = _grid.height();

    SDL_Rect destination{ (int)bounds.x, (int)bounds.y, (int)bounds.width, (int)bounds.height };
    for (size_t y = 0; y < height; y++) {
        for (size_t x = 0; x < width; x++) {
            auto key = std::make_pair(_grid.get(x, y), _paletteGrid.get(x, y));
            if (_tileTypesTextures.find(key) == _tileTypesTextures.end())
                _tileTypesTextures[key] = createTexture(std::move(Image4(_tileTypes[key.first], _paletteTypes[key.second])));
            destination.x = (int)(bounds.x + x * bounds.width);
            destination.y = (int)(bounds.y + y * bounds.height);
            SDL_RenderCopy(renderer, _tileTypesTextures[key], nullptr, &destination);
        }
    }
}

void PaletteTileBatcher::draw(Image4& screen, const std::function<const Rect2<double>(size_t x, size_t y)>& boundsFunction) {
    const double maxWidth = screen.width();
    const double maxHeight = screen.height();

    size_t width = _grid.width();
    size_t height = _grid.height();

    for (size_t y = 0; y < height; y++) {
        for (size_t x = 0; x < width; x++) {
            auto pair = _tileTypes.find(_grid.get(x, y));
            if (pair == _tileTypes.end()) continue;
            PaletteImage& image = pair->second;
            Palette<Color4>& palette = _paletteTypes[_paletteGrid.get(x, y)];
            const Rect2<double> destination(boundsFunction(x, y));

            // Fit to screen bounds
            double xMinConstrained = Math::max(0.0, destination.x);
            double yMinConstrained = Math::max(0.0, destination.y);
            double xMaxConstrained = Math::min(destination.x + destination.width, maxWidth);
            double yMaxConstrained = Math::min(destination.y + destination.height, maxHeight);

            // Render object fill color (image) on top of pre-existing
            for (size_t y = (int)yMinConstrained; y < (int)yMaxConstrained; y++) {
                double s = (y - destination.y) / destination.height;
                for (size_t x = (int)xMinConstrained; x < (int)xMaxConstrained; x++) {
                    double t = (x - destination.x) / destination.width;
                    void* pixel = screen.pixelAt(x, y);
                    Color4::flatten(pixel, palette[image.atParameterization(t, s)]);
                }
            }
        }
    }
}
void PaletteTileBatcher::draw(SDL_Renderer* renderer, const std::function<const SDL_Rect(size_t x, size_t y)>& boundsFunction) {
    size_t width = _grid.width();
    size_t height = _grid.height();

    for (size_t y = 0; y < height; y++) {
        for (size_t x = 0; x < width; x++) {
            auto key = std::make_pair(_grid.get(x, y), _paletteGrid.get(x, y));
            if (_tileTypesTextures.find(key) == _tileTypesTextures.end())
                _tileTypesTextures[key] = createTexture(std::move(Image4(_tileTypes[key.first], _paletteTypes[key.second])));
            const SDL_Rect destination(boundsFunction(x, y));
            SDL_RenderCopy(renderer, _tileTypesTextures[key], nullptr, &destination);
        }
    }
}