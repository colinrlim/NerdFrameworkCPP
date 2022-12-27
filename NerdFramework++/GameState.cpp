#include <cmath>
#include "PacmanToolbox.h"
#include "GameState.h"

GameState::GameState() :
	levelStart(),
	levelEnd(),
	fruitGrab(),
	powerGrab(),
	highscore()
{
	restart();
}

void GameState::interactTile(size_t x, size_t y) {
	PacmanToolbox& toolbox = PacmanToolbox::getInstance();
	uint8_t& tile = toolbox.tileBatcher->tileAt(x, y);
	uint8_t& palette = toolbox.tileBatcher->paletteAt(x, y);
	if (tile == 10 && palette != 0) {
		palette = 0;
		pellets++;
		updateScore(++score);
	}
	else if (tile == 30 && palette != 0) {
		palette = 0;
		powerGrab.tickNow();
	}
}
void GameState::updateScore(uint32_t score) {
	PacmanToolbox& toolbox = PacmanToolbox::getInstance();
	uint8_t* data = toolbox.tileBatcher->gridData();
	this->score = score;
	
	std::string stringized = std::to_string(score);
	std::move(stringized.data(), stringized.data() + stringized.length(), data + 34 - stringized.length());
	if (highscore <= score) {
		highscore = score;
		std::move(stringized.data(), stringized.data() + stringized.length(), data + 44 - stringized.length());
	}
}
void GameState::restart() {
	level = 0;
	pellets = 0;
	ghostmode = 0;
	updateScore(0);
	levelStart.tickNow();
}