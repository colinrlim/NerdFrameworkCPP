#include "Player.h"

void Player::update(double delta) {
	Entity::update(delta);
	if (_lastPositionTile != _positionTile) {
		_lastPositionTile = _positionTile;

	}
}