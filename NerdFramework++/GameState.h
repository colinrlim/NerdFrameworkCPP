#pragma once

#include <cstdint>
#include "TileBatch.h"

class GameState {
private:
	GameState();
public:
	TileBatch* tileBatch;

	uint8_t level;
	uint8_t pellets; 

	static GameState& getInstance() {
		static GameState mine;
		return mine;
	}
	void restart();
};

