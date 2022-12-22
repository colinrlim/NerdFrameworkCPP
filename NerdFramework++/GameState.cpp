#include "GameState.h"

GameState::GameState() :
	_fruitTimestamp(std::chrono::steady_clock::now()),
	_powerTimestamp(std::chrono::steady_clock::now()),
	_winTimestamp(std::chrono::steady_clock::now()),
	highscore()
{
	restart();
}

void GameState::interactTile(size_t x, size_t y) {
	uint8_t& tile = tileBatch->tileAt(x, y);
	uint8_t& palette = tileBatch->paletteAt(x, y);
	if (tile == 10 && palette != 0) {
		palette = 0;
		pellets++;
	}
	else if (tile == 30 && palette != 0) {
		palette = 0;
		_powerTimestamp = std::chrono::steady_clock::now();
	}
}
void GameState::restart() {
	level = 0;
	pellets = 0;
	score = 0;
}