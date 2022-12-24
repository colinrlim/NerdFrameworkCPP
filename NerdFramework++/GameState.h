#pragma once

#include <cstdint>
#include <chrono>
#include "PaletteTileBatch.h"

class GameState {
private:
	std::chrono::steady_clock::time_point _fruitTimestamp;
	std::chrono::steady_clock::time_point _powerTimestamp;
	std::chrono::steady_clock::time_point _winTimestamp;
public:
	uint8_t level;
	uint8_t pellets; 

	uint32_t score; 
	uint32_t highscore;

	GameState();

	void interactTile(size_t x, size_t y);
	void updateScore(uint32_t score);
	void restart();
};

