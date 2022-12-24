#pragma once

#include "Entity.h"

class Enemy : public Entity {
private:
	uint16_t _targetTile;
public:
	std::function<uint16_t(const Entity&)> calculateTargetTile;
	const Palette<Color4>& basePalette;

	Enemy(const Palette<Color4>& basePalette, Vector2 position, uint16_t direction = DIRECTION_LEFT, float speed = 10.f);

	uint16_t getTargetTile();

	void draw(Interface& interface, Image4& screen);
	void draw(Interface& interface, SDL_Renderer* renderer);
};

