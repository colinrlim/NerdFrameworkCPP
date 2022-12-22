#include "PaletteTileBatch.h"
#include "Math.h"

PaletteTileBatch::PaletteTileBatch(const PaletteTileBatch& rhs) :
    _renderer(nullptr),
    _grid(1, 1),
    _paletteGrid(1, 1)
{ }
PaletteTileBatch& PaletteTileBatch::operator=(const PaletteTileBatch& rhs) { return *this; }
PaletteTileBatch& PaletteTileBatch::operator=(PaletteTileBatch&& rhs) { return *this; }

SDL_Texture* PaletteTileBatch::createTexture(Image4&& image) const {
    SDL_Texture* texture = SDL_CreateTexture(_renderer, SDL_PIXELFORMAT_ABGR8888, SDL_TEXTUREACCESS_STATIC, image.width(), image.height());
    SDL_UpdateTexture(texture, nullptr, image.data, image.width() * 4);
    return texture;
}
void PaletteTileBatch::updateTileTypeTextures() {
    for (auto tileTypePair = _tileTypes.begin(); tileTypePair != _tileTypes.end(); ++tileTypePair)
        for (auto paletteTypePair = _paletteTypes.begin(); paletteTypePair != _paletteTypes.end(); ++paletteTypePair)
            _tileTypesTextures[std::make_pair(tileTypePair->first, paletteTypePair->first)] = createTexture(Image4(tileTypePair->second, paletteTypePair->second));
}

PaletteTileBatch::PaletteTileBatch(SDL_Renderer* renderer) :
    _renderer(renderer),
    _grid(1, 1),
    _paletteGrid(1, 1)
{ }
PaletteTileBatch::PaletteTileBatch(PaletteTileBatch&& rhs) :
    _renderer(rhs._renderer),
    _tileTypes(std::move(rhs._tileTypes)),
    _tileTypesTextures(std::move(rhs._tileTypesTextures)),
    _paletteTypes(std::move(rhs._paletteTypes)),
    _grid(std::move(rhs._grid)),
    _paletteGrid(std::move(rhs._paletteGrid))
{ }
PaletteTileBatch::~PaletteTileBatch() {
    for (auto pair = _tileTypesTextures.begin(); pair != _tileTypesTextures.end(); ++pair)
        SDL_DestroyTexture(pair->second);
}

uint8_t* PaletteTileBatch::gridData() const {
    return _grid.data();
}
uint8_t* PaletteTileBatch::paletteGridData() const {
    return _paletteGrid.data();
}
uint8_t& PaletteTileBatch::tileAt(size_t x, size_t y) const {
    return _grid.get(x, y);
}
uint8_t& PaletteTileBatch::paletteAt(size_t x, size_t y) const {
    return _paletteGrid.get(x, y);
}

void PaletteTileBatch::setGrid(const Grid2<uint8_t>& grid) {
    _grid = grid;
}
void PaletteTileBatch::setGrid(Grid2<uint8_t>&& grid) {
    _grid = std::move(grid);
}
void PaletteTileBatch::setPaletteGrid(const Grid2<uint8_t>& paletteGrid) {
    _paletteGrid = paletteGrid;
}
void PaletteTileBatch::setPaletteGrid(Grid2<uint8_t>&& paletteGrid) {
    _paletteGrid = std::move(paletteGrid);
}

void PaletteTileBatch::setTileTypes(const std::map<uint8_t, PaletteImage>& tileTypes) {
    _tileTypes = tileTypes;
    updateTileTypeTextures();
}
void PaletteTileBatch::setTileTypes(std::map<uint8_t, PaletteImage>&& tileTypes) {
    _tileTypes = std::move(tileTypes);
    updateTileTypeTextures();
}
void PaletteTileBatch::setPaletteTypes(const std::map<uint8_t, Palette<Color4>>& palettes) {
    _paletteTypes = palettes;
    updateTileTypeTextures();
}
void PaletteTileBatch::setPaletteTypes(std::map<uint8_t, Palette<Color4>>&& palettes) {
    _paletteTypes = std::move(palettes);
    updateTileTypeTextures();
}

void PaletteTileBatch::draw(Image4& screen, const Rect2<double>& bounds) {
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

void PaletteTileBatch::draw(SDL_Renderer* renderer, const Rect2<double>& bounds) {
    size_t width = _grid.width();
    size_t height = _grid.height();

    SDL_Rect destination{ (int)bounds.x, (int)bounds.y, (int)bounds.width, (int)bounds.height };
    for (size_t y = 0; y < height; y++) {
        for (size_t x = 0; x < width; x++) {
            auto pair = _tileTypesTextures.find(std::make_pair(_grid.get(x, y), _paletteGrid.get(x, y)));
            if (pair == _tileTypesTextures.end()) continue;
            destination.x = (int)(bounds.x + x * bounds.width);
            destination.y = (int)(bounds.y + y * bounds.height);
            SDL_RenderCopy(renderer, pair->second, nullptr, &destination);
        }
    }
}