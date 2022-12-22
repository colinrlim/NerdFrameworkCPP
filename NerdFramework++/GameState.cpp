#include "GameState.h"

GameState::GameState() {
	restart();
}

void GameState::restart() {
	level = 0;
	pellets = 0;
}