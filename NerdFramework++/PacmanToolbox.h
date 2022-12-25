#pragma once

#include "PaletteImageStamper.h"
#include "PaletteTileBatcher.h"

class PacmanToolbox {
public:
	PaletteTileBatcher* tileBatcher;

	PaletteImageStamper* ghostUpStamper;
	PaletteImageStamper* ghostDownStamper;
	PaletteImageStamper* ghostLeftStamper;
	PaletteImageStamper* ghostRightStamper;
	PaletteImageStamper* ghostFrightStamper;
	PaletteImageStamper* ghostLegsStamper1;
	PaletteImageStamper* ghostLegsStamper2;
	PaletteImageStamper* ghostLegsStamper3;
	PaletteImageStamper* ghostLegsStamper4;

	std::vector<Palette<Color4>> palettes;

	PacmanToolbox();
	~PacmanToolbox();

	static PacmanToolbox& getInstance() {
		static PacmanToolbox mine;
		return mine;
	}
};

