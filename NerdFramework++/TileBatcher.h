#pragma once

#include <SDL.h>
#include <map>
#include "Image4.h"
#include "Grid2.h"
#include "Rect2.h"

class TileBatch {
private:
    SDL_Renderer* _renderer;

    std::map<uint8_t, Image4> _tileTypes;
    std::map<uint8_t, SDL_Texture*> _tileTypesTextures;
    Grid2<uint8_t> _grid;

    TileBatch(const TileBatch& rhs);
    TileBatch& operator=(const TileBatch& rhs);
    TileBatch& operator=(TileBatch&& rhs);

    SDL_Texture* createTexture(const Image4& image) const;
    void updateTileTypeTextures();
public:
    TileBatch(SDL_Renderer* renderer);
    TileBatch(TileBatch&& rhs);
    ~TileBatch();

    uint8_t* data() const;
    uint8_t& at(size_t x, size_t y) const;
    size_t size() const;

    void setGrid(const Grid2<uint8_t>& grid);
    void setGrid(Grid2<uint8_t>&& grid);
    void setTileTypes(const std::map<uint8_t, Image4>& tileTypes);
    void setTileTypes(std::map<uint8_t, Image4>&& tileTypes);

    void draw(Image4& screen, const Rect2<double>& bounds);
    void draw(SDL_Renderer* renderer, const Rect2<double>& bounds);
};

