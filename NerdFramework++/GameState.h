#pragma once

#include <cstdint>
#include <chrono>
#include "PaletteTileBatch.h"

class GameState {
private:
	GameState();

	std::chrono::steady_clock::time_point _fruitTimestamp;
	std::chrono::steady_clock::time_point _powerTimestamp;
	std::chrono::steady_clock::time_point _winTimestamp;
public:
	PaletteTileBatch* tileBatch;

	uint8_t level;
	uint8_t pellets; 

	uint32_t score; 
	uint32_t highscore;

	static GameState& getInstance() {
		static GameState mine;
		return mine;
	}
	void interactTile(size_t x, size_t y);
	void restart();
};

