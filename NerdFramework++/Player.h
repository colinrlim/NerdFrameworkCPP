#pragma once

#include "Entity.h"

class Player : public Entity {
private:
	uint16_t _lastPositionTile;
public:
	void update(double seconds);

	Player(Vector2 position, uint16_t direction = DIRECTION_LEFT, float speed = 10.f);

	void draw(Interface& interface, Image4& screen) const;
	void draw(Interface& interface, SDL_Renderer* renderer) const;
};

