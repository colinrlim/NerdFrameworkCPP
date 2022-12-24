#include "PacmanToolbox.h"
#include "GameState.h"
#include "Entity.h"
#include "Math.h"

bool Entity::isDirectionValid(uint16_t direction) {
	const uint8_t* positionComponents = (uint8_t*)&_positionTile;
	uint16_t nextTile(direction);
	uint8_t* nextTileComponents = (uint8_t*)&nextTile;
	nextTileComponents[0] += positionComponents[0];
	nextTileComponents[1] += positionComponents[1];
	return PacmanToolbox::getInstance().tileBatch->tileAt(nextTileComponents[0], nextTileComponents[1]) % 10 == 0;
}
void Entity::updateDirection() {
	/*const uint8_t* positionComponents = (uint8_t*)&_positionTile;
	const uint8_t* targetComponents = (uint8_t*)&_targetTile;

	bool upValid = isDirectionValid(DIRECTION_UP);
	bool leftValid = isDirectionValid(DIRECTION_LEFT);
	bool downValid = isDirectionValid(DIRECTION_DOWN);
	bool rightValid = isDirectionValid(DIRECTION_RIGHT);

	uint16_t normDistX = (uint16_t)(targetComponents[1] - positionComponents[1]) * (uint16_t)(targetComponents[1] - positionComponents[1]);
	uint16_t normDistY = (uint16_t)(targetComponents[0] - positionComponents[0]) * (uint16_t)(targetComponents[0] - positionComponents[0]);
	double upDist;
	double leftDist;
	double downDist;
	double rightDist;
	
	if (upValid)
		upDist = Math::sqrt(normDistX + (uint16_t)(targetComponents[0] - (positionComponents[0] - 1)) * (uint16_t)(targetComponents[0] - (positionComponents[0] - 1)));
	if (leftValid)
		leftDist = Math::sqrt((uint16_t)(targetComponents[1] - (positionComponents[1] + 1)) * (uint16_t)(targetComponents[1] - (positionComponents[1] + 1)) + normDistY);
	if (downValid)
		downDist = Math::sqrt(normDistX + (uint16_t)(targetComponents[0] - (positionComponents[0] + 1)) * (uint16_t)(targetComponents[0] - (positionComponents[0] + 1)));
	if (rightValid)
		rightDist = Math::sqrt((uint16_t)(targetComponents[1] - (positionComponents[1] - 1)) * (uint16_t)(targetComponents[1] - (positionComponents[1] - 1)) + normDistY);

	if (upValid &&
		(!leftValid || upDist <= leftDist) &&
		(!downValid || upDist <= downDist) &&
		(!rightValid || upDist <= rightDist))
		_direction = DIRECTION_UP;
	else if (leftValid &&
		(!downValid || leftDist <= downDist) &&
		(!rightValid || leftDist <= rightDist))
		_direction = DIRECTION_LEFT;
	else if (downValid &&
		(!rightValid || downDist <= rightDist))
		_direction = DIRECTION_DOWN;
	else
		_direction = DIRECTION_RIGHT;*/
}
Entity::Entity(Vector2 position, uint16_t direction, float speed) :
	_position(position),
	_direction(direction),
	speed(speed)
{ }

const Vector2& Entity::getPosition() {
	return _position;
}
uint16_t Entity::getDirection() {
	return _direction;
}

void Entity::update(double seconds) {
	_position += speed * seconds;
}