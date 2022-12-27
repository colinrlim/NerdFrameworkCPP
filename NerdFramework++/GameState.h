#pragma once

#include <cstdint>
#include "PaletteTileBatcher.h"
#include "Timer.h"

class GameState {
public:
	Timer levelStart;
	Timer levelEnd;
	Timer fruitGrab;
	Timer powerGrab;

	uint8_t level;
	uint8_t pellets; 

	uint32_t score; 
	uint32_t highscore;

	uint8_t ghostmode;

	GameState();

	void interactTile(size_t x, size_t y);
	void updateScore(uint32_t score);
	void restart();
};

