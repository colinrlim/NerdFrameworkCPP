#pragma once

#include <SDL.h>
#include <map>
#include "Image4.h"
#include "Grid2.h"
#include "Rect2.h"

class TileBatch {
    std::map<uint8_t, Image4> _imageMap;
    std::map<uint8_t, SDL_Texture*> _textureMap;
    SDL_Renderer* _renderer;

    TileBatch(const TileBatch& rhs);
    TileBatch& operator=(const TileBatch& rhs);
    TileBatch& operator=(TileBatch&& rhs);

    SDL_Texture* createTexture(const Image4& image) const;
public:
    Grid2<uint8_t> grid;

    TileBatch(SDL_Renderer* renderer, const Grid2<uint8_t>& grid, const std::map<uint8_t, Image4>& tileMap);
    TileBatch(SDL_Renderer* renderer, Grid2<uint8_t>&& grid, std::map<uint8_t, Image4>&& tileMap);
    TileBatch(SDL_Renderer* renderer, const Grid2<uint8_t>& grid);
    TileBatch(SDL_Renderer* renderer, Grid2<uint8_t>&& grid);
    TileBatch(TileBatch&& rhs);
    ~TileBatch();

    const Image4& getTileImage(uint8_t key) const;
    void setTileImage(uint8_t key, const Image4& image);
    void setTileImage(uint8_t key, Image4&& image);

    void draw(Image4& screen, const Rect2<double>& bounds);
    void draw(SDL_Renderer* renderer, const Rect2<double>& bounds);
};

