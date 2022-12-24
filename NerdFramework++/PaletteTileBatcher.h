#pragma once

#include <SDL.h>
#include <map>
#include "PaletteImage.h"
#include "Palette.h"
#include "Image4.h"
#include "Color4.h"
#include "Grid2.h"
#include "Rect2.h"

class PaletteTileBatcher {
private:
    SDL_Renderer* _renderer;

    std::map<uint8_t, PaletteImage> _tileTypes;
    std::map<std::pair<uint8_t, uint8_t>, SDL_Texture*> _tileTypesTextures;
    std::vector<Palette<Color4>> _paletteTypes;

    Grid2<uint8_t> _grid;
    Grid2<uint8_t> _paletteGrid;

    PaletteTileBatcher(const PaletteTileBatcher& rhs);
    PaletteTileBatcher& operator=(const PaletteTileBatcher& rhs);
    PaletteTileBatcher& operator=(PaletteTileBatcher&& rhs);

    SDL_Texture* createTexture(Image4&& image) const;
public:
    PaletteTileBatcher(SDL_Renderer* renderer);
    PaletteTileBatcher(PaletteTileBatcher&& rhs);
    ~PaletteTileBatcher();

    uint8_t* gridData() const;
    uint8_t* paletteGridData() const;
    uint8_t& tileAt(size_t x, size_t y) const;
    uint8_t& paletteAt(size_t x, size_t y) const;
    size_t size() const;

    void setGrid(const Grid2<uint8_t>& grid);
    void setGrid(Grid2<uint8_t>&& grid);
    void setPaletteGrid(const Grid2<uint8_t>& paletteGrid);
    void setPaletteGrid(Grid2<uint8_t>&& paletteGrid);

    void setTileTypes(const std::map<uint8_t, PaletteImage>& tileTypes);
    void setTileTypes(std::map<uint8_t, PaletteImage>&& tileTypes);
    void setPaletteTypes(const std::vector<Palette<Color4>>& palettes);
    void setPaletteTypes(std::vector<Palette<Color4>>&& palettes);

    void draw(Image4& screen, const Rect2<double>& bounds);
    void draw(SDL_Renderer* renderer, const Rect2<double>& bounds);
};

