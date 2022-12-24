#pragma once

#include <map>
#include <SDL.h>
#include "Image4.h"
#include "Rect2.h"

class PaletteImageMaster {
    PaletteImage _image;
    SDL_Renderer* _renderer;
    std::map<const Palette<Color4>*, SDL_Texture*> _textures;

    PaletteImageMaster(const PaletteImageMaster& rhs);
    PaletteImageMaster& operator=(const PaletteImageMaster& rhs);
    PaletteImageMaster& operator=(PaletteImageMaster&& rhs);

    SDL_Texture* createTexture(const Palette<Color4>& palette) const;
public:
    PaletteImageMaster(SDL_Renderer* renderer, PaletteImage&& image);
    PaletteImageMaster(PaletteImageMaster&& rhs);
    ~PaletteImageMaster();

    const PaletteImage& getImage() const;
    void setImage(PaletteImage&& image);

    void draw(const Palette<Color4>& palette, Image4& screen, const Rect2<double>& bounds);
    void draw(const Palette<Color4>& palette, SDL_Renderer* renderer, const Rect2<double>& bounds);
};

