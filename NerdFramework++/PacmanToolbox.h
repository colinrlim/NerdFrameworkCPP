#pragma once

#include "PaletteImageMaster.h"
#include "PaletteTileBatch.h"

class PacmanToolbox {
public:
	PaletteTileBatch* tileBatch;

	PaletteImageMaster* ghostUpMaster;
	PaletteImageMaster* ghostDownMaster;
	PaletteImageMaster* ghostLeftMaster;
	PaletteImageMaster* ghostRightMaster;
	PaletteImageMaster* ghostFrightMaster;
	PaletteImageMaster* ghostLegsMaster1;
	PaletteImageMaster* ghostLegsMaster2;
	PaletteImageMaster* ghostLegsMaster3;
	PaletteImageMaster* ghostLegsMaster4;

	PacmanToolbox();
	~PacmanToolbox();

	static PacmanToolbox& getInstance() {
		static PacmanToolbox mine;
		return mine;
	}
};

