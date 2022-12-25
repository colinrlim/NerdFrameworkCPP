#include "PacmanToolbox.h"
#include "Enemy.h"
#include "Math.h"

void Enemy::updateDirection() {
	Vector2i positionTileVector(_position);
	Vector2i targetTileVector(_targetTile);
	SDL_GetMouseState(&targetTileVector.x, &targetTileVector.y);
	targetTileVector /= 16;

	bool upValid = isDirectionValid(DIRECTION_UP) && _direction != DIRECTION_DOWN;
	bool leftValid = isDirectionValid(DIRECTION_LEFT) && _direction != DIRECTION_RIGHT;
	bool downValid = isDirectionValid(DIRECTION_DOWN) && _direction != DIRECTION_UP;
	bool rightValid = isDirectionValid(DIRECTION_RIGHT) && _direction != DIRECTION_LEFT;

	double upDist;
	double leftDist;
	double downDist;
	double rightDist;
	
	if (upValid)
		upDist = (positionTileVector + Vector2i(0, -1) - targetTileVector).magnitude();
	if (leftValid)
		leftDist = (positionTileVector + Vector2i(-1, 0) - targetTileVector).magnitude();
	if (downValid)
		downDist = (positionTileVector + Vector2i(0, 1) - targetTileVector).magnitude();
	if (rightValid)
		rightDist = (positionTileVector + Vector2i(1, 0) - targetTileVector).magnitude();

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
		_direction = DIRECTION_RIGHT;
}

Enemy::Enemy(const Palette<Color4>& basePalette, Vector2 position, uint16_t direction, float speed) :
	Entity(position, direction, speed),
	basePalette(basePalette)
{ }

uint16_t Enemy::getTargetTile() {
	return _targetTile;
}

void Enemy::draw(Interface& interface, Image4& screen) {
	PacmanToolbox& toolbox = PacmanToolbox::getInstance();
	const double initX = _position.x * 16.0 - 16.0;
	const double initY = _position.y * 16.0 - 22.0;
	const double initX1 = initX - 28.0 * 16.0;
	const double initX2 = initX + 28.0 * 16.0;
	const Palette<Color4>& palette = (state == FRIGHTENED ? toolbox.palettes[1] : (state == EATEN ? toolbox.palettes[10] : basePalette));
	if (state == FRIGHTENED) {
		toolbox.ghostFrightStamper->draw(palette, screen, Rect2<double>{initX, initY, 32, 32});
		toolbox.ghostFrightStamper->draw(palette, screen, Rect2<double>{initX1, initY, 32, 32});
		toolbox.ghostFrightStamper->draw(palette, screen, Rect2<double>{initX2, initY, 32, 32});
	} else if (_direction == DIRECTION_UP) {
		toolbox.ghostUpStamper->draw(palette, screen, Rect2<double>{initX, initY, 32, 32});
		toolbox.ghostUpStamper->draw(palette, screen, Rect2<double>{initX1, initY, 32, 32});
		toolbox.ghostUpStamper->draw(palette, screen, Rect2<double>{initX2, initY, 32, 32});
	} else if (_direction == DIRECTION_DOWN) {
		toolbox.ghostDownStamper->draw(palette, screen, Rect2<double>{initX, initY, 32, 32});
		toolbox.ghostDownStamper->draw(palette, screen, Rect2<double>{initX1, initY, 32, 32});
		toolbox.ghostDownStamper->draw(palette, screen, Rect2<double>{initX2, initY, 32, 32});
	} else if (_direction == DIRECTION_LEFT) {
		toolbox.ghostLeftStamper->draw(palette, screen, Rect2<double>{initX, initY, 32, 32});
		toolbox.ghostLeftStamper->draw(palette, screen, Rect2<double>{initX1, initY, 32, 32});
		toolbox.ghostLeftStamper->draw(palette, screen, Rect2<double>{initX2, initY, 32, 32});
	} else if (_direction == DIRECTION_RIGHT) {
		toolbox.ghostRightStamper->draw(palette, screen, Rect2<double>{initX, initY, 32, 32});
		toolbox.ghostRightStamper->draw(palette, screen, Rect2<double>{initX1, initY, 32, 32});
		toolbox.ghostRightStamper->draw(palette, screen, Rect2<double>{initX2, initY, 32, 32});
	}
	if (Math::dmod(interface.secondsElapsed(), 0.3) >= 0.15) {
		toolbox.ghostLegsStamper1->draw(palette, screen, Rect2<double>{initX, initY + 32.0, 16, 16});
		toolbox.ghostLegsStamper2->draw(palette, screen, Rect2<double>{initX + 16.0, initY + 32.0, 16, 16});
		toolbox.ghostLegsStamper1->draw(palette, screen, Rect2<double>{initX1, initY + 32.0, 16, 16});
		toolbox.ghostLegsStamper2->draw(palette, screen, Rect2<double>{initX1 + 16.0, initY + 32.0, 16, 16});
		toolbox.ghostLegsStamper1->draw(palette, screen, Rect2<double>{initX2, initY + 32.0, 16, 16});
		toolbox.ghostLegsStamper2->draw(palette, screen, Rect2<double>{initX2 + 16.0, initY + 32.0, 16, 16});
	}
	else if (Math::dmod(interface.secondsElapsed(), 0.3) < 0.15) {
		toolbox.ghostLegsStamper3->draw(palette, screen, Rect2<double>{initX, initY + 32.0, 16, 16});
		toolbox.ghostLegsStamper4->draw(palette, screen, Rect2<double>{initX + 16.0, initY + 32.0, 16, 16});
		toolbox.ghostLegsStamper3->draw(palette, screen, Rect2<double>{initX1, initY + 32.0, 16, 16});
		toolbox.ghostLegsStamper4->draw(palette, screen, Rect2<double>{initX1 + 16.0, initY + 32.0, 16, 16});
		toolbox.ghostLegsStamper3->draw(palette, screen, Rect2<double>{initX2, initY + 32.0, 16, 16});
		toolbox.ghostLegsStamper4->draw(palette, screen, Rect2<double>{initX2 + 16.0, initY + 32.0, 16, 16});
	}
}
void Enemy::draw(Interface& interface, SDL_Renderer* renderer) {
	PacmanToolbox& toolbox = PacmanToolbox::getInstance();
	const double initX = _position.x * 16.0 - 16.0;
	const double initY = _position.y * 16.0 - 22.0;
	const double initX1 = initX - 28.0 * 16.0;
	const double initX2 = initX + 28.0 * 16.0;
	const Palette<Color4>& palette = (state == FRIGHTENED ? toolbox.palettes[1] : (state == EATEN ? toolbox.palettes[10] : basePalette));
	if (state == FRIGHTENED) {
		toolbox.ghostFrightStamper->draw(palette, renderer, Rect2<double>{initX, initY, 32, 32});
		toolbox.ghostFrightStamper->draw(palette, renderer, Rect2<double>{initX1, initY, 32, 32});
		toolbox.ghostFrightStamper->draw(palette, renderer, Rect2<double>{initX2, initY, 32, 32});
	} else if (_direction == DIRECTION_UP) {
		toolbox.ghostUpStamper->draw(palette, renderer, Rect2<double>{initX, initY, 32, 32});
		toolbox.ghostUpStamper->draw(palette, renderer, Rect2<double>{initX1, initY, 32, 32});
		toolbox.ghostUpStamper->draw(palette, renderer, Rect2<double>{initX2, initY, 32, 32});
	} else if (_direction == DIRECTION_DOWN) {
		toolbox.ghostDownStamper->draw(palette, renderer, Rect2<double>{initX, initY, 32, 32});
		toolbox.ghostDownStamper->draw(palette, renderer, Rect2<double>{initX1, initY, 32, 32});
		toolbox.ghostDownStamper->draw(palette, renderer, Rect2<double>{initX2, initY, 32, 32});
	} else if (_direction == DIRECTION_LEFT) {
		toolbox.ghostLeftStamper->draw(palette, renderer, Rect2<double>{initX, initY, 32, 32});
		toolbox.ghostLeftStamper->draw(palette, renderer, Rect2<double>{initX1, initY, 32, 32});
		toolbox.ghostLeftStamper->draw(palette, renderer, Rect2<double>{initX2, initY, 32, 32});
	} else if (_direction == DIRECTION_RIGHT) {
		toolbox.ghostRightStamper->draw(palette, renderer, Rect2<double>{initX, initY, 32, 32});
		toolbox.ghostRightStamper->draw(palette, renderer, Rect2<double>{initX1, initY, 32, 32});
		toolbox.ghostRightStamper->draw(palette, renderer, Rect2<double>{initX2, initY, 32, 32});
	}
	if (Math::dmod(interface.secondsElapsed(), 0.3) >= 0.15) {
		toolbox.ghostLegsStamper1->draw(palette, renderer, Rect2<double>{initX, initY + 32.0, 16, 16});
		toolbox.ghostLegsStamper2->draw(palette, renderer, Rect2<double>{initX + 16.0, initY + 32.0, 16, 16});
		toolbox.ghostLegsStamper1->draw(palette, renderer, Rect2<double>{initX1, initY + 32.0, 16, 16});
		toolbox.ghostLegsStamper2->draw(palette, renderer, Rect2<double>{initX1 + 16.0, initY + 32.0, 16, 16});
		toolbox.ghostLegsStamper1->draw(palette, renderer, Rect2<double>{initX2, initY + 32.0, 16, 16});
		toolbox.ghostLegsStamper2->draw(palette, renderer, Rect2<double>{initX2 + 16.0, initY + 32.0, 16, 16});
	}
	else if (Math::dmod(interface.secondsElapsed(), 0.3) < 0.15) {
		toolbox.ghostLegsStamper3->draw(palette, renderer, Rect2<double>{initX, initY + 32.0, 16, 16});
		toolbox.ghostLegsStamper4->draw(palette, renderer, Rect2<double>{initX + 16.0, initY + 32.0, 16, 16});
		toolbox.ghostLegsStamper3->draw(palette, renderer, Rect2<double>{initX1, initY + 32.0, 16, 16});
		toolbox.ghostLegsStamper4->draw(palette, renderer, Rect2<double>{initX1 + 16.0, initY + 32.0, 16, 16});
		toolbox.ghostLegsStamper3->draw(palette, renderer, Rect2<double>{initX2, initY + 32.0, 16, 16});
		toolbox.ghostLegsStamper4->draw(palette, renderer, Rect2<double>{initX2 + 16.0, initY + 32.0, 16, 16});
	}
}