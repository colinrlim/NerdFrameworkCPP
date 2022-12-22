#pragma once

#include "Entity.h"

class Enemy : public Entity {
private:
	uint16_t _targetTile;
public:
	std::function<uint16_t(const Entity&)> calculateTargetTile;

	uint16_t getTargetTile();

	void draw(Interface& interface, Image4& screen);
	void draw(Interface& interface, SDL_Renderer* renderer);
};

