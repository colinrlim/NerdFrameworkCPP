#pragma once

#include <functional>
#include <cstdint>
#include "Interface.h"
#include "Vector2.h"

class Entity {
protected:
	Vector2 _position;
	uint16_t _positionTile;
	uint16_t _lastPositionTile;
	uint16_t _direction;

	bool isDirectionValid(uint16_t direction);
	virtual void updateDirection();
public:
	static constexpr uint16_t DIRECTION_UP = 0x00FF;
	static constexpr uint16_t DIRECTION_LEFT = 0xFF00;
	static constexpr uint16_t DIRECTION_DOWN = 0x0001;
	static constexpr uint16_t DIRECTION_RIGHT = 0x0100;

	float speed;

	Entity(Vector2 position, uint16_t direction = DIRECTION_LEFT, float speed = 10.f);

	const Vector2& getPosition();
	uint16_t getDirection();

	void update(double seconds);
	virtual void draw(Interface& interface, Image4& screen) = 0;
	virtual void draw(Interface& interface, SDL_Renderer* renderer) = 0;
};

