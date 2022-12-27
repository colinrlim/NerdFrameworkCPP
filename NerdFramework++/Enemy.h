#pragma once

#include "Entity.h"

class Enemy : public Entity {
private:
	uint16_t _targetTile;

	void updateDirection();
public:
	enum State {
		CHASE,
		SCATTER,
		FRIGHTENED,
		EATEN
	};

	std::function<uint16_t(const Enemy&)> calculateTargetTile;
	const Palette<Color4>& basePalette;
	State state;

	Enemy(const Palette<Color4>& basePalette, Vector2 position, uint16_t direction = DIRECTION_LEFT, float speed = 10.f);

	uint16_t getTargetTile() const;
	void reverseDirection();

	void draw(Interface& interface, Image4& screen) const;
	void draw(Interface& interface, SDL_Renderer* renderer) const;
};

