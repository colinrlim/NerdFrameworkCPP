#include "PacmanToolbox.h"
#include "GameState.h"
#include "Entity.h"
#include "Math.h"

bool Entity::isDirectionValid(uint16_t direction) {
	if (direction == DIRECTION_UP)
		return PacmanToolbox::getInstance().tileBatcher->tileAt((size_t)_position.x, (size_t)_position.y - 1) % 10 == 0;
	else if (direction == DIRECTION_DOWN)
		return PacmanToolbox::getInstance().tileBatcher->tileAt((size_t)_position.x, (size_t)_position.y + 1) % 10 == 0;
	else if (direction == DIRECTION_LEFT)
		return PacmanToolbox::getInstance().tileBatcher->tileAt((size_t)_position.x - 1, (size_t)_position.y) % 10 == 0;
	else// if (direction == DIRECTION_RIGHT)
		return PacmanToolbox::getInstance().tileBatcher->tileAt((size_t)_position.x + 1, (size_t)_position.y) % 10 == 0;
}
void Entity::updateDirection() {

}

Entity::Entity(Vector2 position, uint16_t direction, float speed) :
	_position(position),
	_direction(direction),
	speed(speed)
{ }

const Vector2& Entity::getPosition() const {
	return _position;
}
uint16_t Entity::getDirection() const {
	return _direction;
}

void Entity::update(double seconds) {
	const uint16_t oldPosition = _position.toInteger();
	const double xIncrement = Math::dmod(_position.x, 1.0);
	const double yIncrement = Math::dmod(_position.y, 1.0);
	if (_direction == DIRECTION_UP) {
		_position.y -= speed * seconds;
		if (yIncrement < 0.50 && _lastPositionTile != _positionTile) {
			_lastPositionTile = _positionTile;
			updateDirection();
			if (_direction != DIRECTION_UP && _direction != DIRECTION_DOWN)
				_position.y += 0.5 - yIncrement;
		}
	} else if (_direction == DIRECTION_DOWN) {
		_position.y += speed * seconds;
		if (yIncrement > 0.50 && _lastPositionTile != _positionTile) {
			_lastPositionTile = _positionTile;
			updateDirection();
			if (_direction != DIRECTION_UP && _direction != DIRECTION_DOWN)
				_position.y += 0.5 - yIncrement;
		}
	} else if (_direction == DIRECTION_LEFT) {
		_position.x -= speed * seconds;
		if (xIncrement < 0.50 && _lastPositionTile != _positionTile && _position.x >= 1.0) {
			_lastPositionTile = _positionTile;
			updateDirection();
			if (_direction != DIRECTION_LEFT && _direction != DIRECTION_RIGHT)
				_position.x += 0.5 - xIncrement;
		}
	} else if (_direction == DIRECTION_RIGHT) {
		_position.x += speed * seconds;
		if (xIncrement > 0.50 && _lastPositionTile != _positionTile && _position.x < 27.0) {
			_lastPositionTile = _positionTile;
			updateDirection();
			if (_direction != DIRECTION_LEFT && _direction != DIRECTION_RIGHT)
				_position.x += 0.5 - xIncrement;
		}
	}

	_position.toInteger(_positionTile);
	if (oldPosition != _position) {
		if (_position.x > 28.0)
			_position.x -= 28.0;
		else if (_position.x < 0.0)
			_position.x += 28.0;
	}
}