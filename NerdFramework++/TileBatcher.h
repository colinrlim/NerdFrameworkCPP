#pragma once

#include <SDL.h>
#include <map>
#include "Image4.h"
#include "Grid2.h"
#include "Rect2.h"

class TileBatcher {
private:
    SDL_Renderer* _renderer;

    std::map<uint8_t, Image4> _tileTypes;
    std::map<uint8_t, SDL_Texture*> _tileTypesTextures;
    Grid2<uint8_t> _grid;

    TileBatcher(const TileBatcher& rhs);
    TileBatcher& operator=(const TileBatcher& rhs);
    TileBatcher& operator=(TileBatcher&& rhs);

    SDL_Texture* createTexture(const Image4& image) const;
public:
    TileBatcher(SDL_Renderer* renderer);
    TileBatcher(TileBatcher&& rhs);
    ~TileBatcher();

    uint8_t* data() const;
    uint8_t& at(size_t x, size_t y) const;
    size_t size() const;

    void setGrid(const Grid2<uint8_t>& grid);
    void setGrid(Grid2<uint8_t>&& grid);
    void setTileTypes(const std::map<uint8_t, Image4>& tileTypes);
    void setTileTypes(std::map<uint8_t, Image4>&& tileTypes);

    void draw(Image4& screen, const Rect2<double>& bounds);
    void draw(SDL_Renderer* renderer, const Rect2<double>& bounds);
    void draw(Image4& screen, const std::function<const Rect2<double>(size_t x, size_t y)>& boundsFunction);
    void draw(SDL_Renderer* renderer, const std::function<const SDL_Rect(size_t x, size_t y)>& boundsFunction);
};

