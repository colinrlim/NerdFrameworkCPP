#include "PacmanToolbox.h"
#include "Enemy.h"
#include "Math.h"

void Enemy::updateDirection() {
	static const uint16_t RESTRICTED_TILE1 = Vector2i(12, 14).toInteger();
	static const uint16_t RESTRICTED_TILE2 = Vector2i(15, 14).toInteger();
	static const uint16_t RESTRICTED_TILE3 = Vector2i(12, 26).toInteger();
	static const uint16_t RESTRICTED_TILE4 = Vector2i(15, 26).toInteger();

	bool upValid = isDirectionValid(DIRECTION_UP) && _direction != DIRECTION_DOWN
		&& _position != RESTRICTED_TILE1 && _position != RESTRICTED_TILE2 && _position != RESTRICTED_TILE3 && _position != RESTRICTED_TILE4;
	bool leftValid = isDirectionValid(DIRECTION_LEFT) && _direction != DIRECTION_RIGHT;
	bool downValid = isDirectionValid(DIRECTION_DOWN) && _direction != DIRECTION_UP;
	bool rightValid = isDirectionValid(DIRECTION_RIGHT) && _direction != DIRECTION_LEFT;

	if (state == FRIGHTENED) {
		for (int x = 0, y = 0; y < 1000; x = rand() % 4, y++) {
			if (x == 0 && upValid) {
				_direction = DIRECTION_UP;
				return;
			} else if (x == 1 && leftValid) {
				_direction = DIRECTION_LEFT;
				return;
			} else if (x == 2 && downValid) {
				_direction = DIRECTION_DOWN;
				return;
			} else if (x == 3 && rightValid) {
				_direction = DIRECTION_RIGHT;
				return;
			}
		}
	}

	static const uint16_t EATEN_TARGET_TILE = Vector2i(13, 14).toInteger();
	if (state == EATEN)
		_targetTile = EATEN_TARGET_TILE;
	else
		_targetTile = calculateTargetTile(*this);

	const Vector2i positionTileVector(_position);
	const Vector2i targetTileVector(_targetTile);

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
	basePalette(basePalette),
	state(SCATTER)
{ }

uint16_t Enemy::getTargetTile() const {
	return _targetTile;
}
void Enemy::reverseDirection() {
	_direction = (Vector2i(_direction) * -1).toInteger();
	update(0.0);
}

void Enemy::draw(Interface& interface, Image4& screen) const {
	PacmanToolbox& toolbox = PacmanToolbox::getInstance();
	const double initX = _position.x * 16.0 - 16.0;
	const double initY = _position.y * 16.0 - 20.0;
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
	toolbox.ghostLegsAnim1->draw(palette, screen, Rect2<double>{initX, initY + 32.0, 16, 16});
	toolbox.ghostLegsAnim2->draw(palette, screen, Rect2<double>{initX + 16.0, initY + 32.0, 16, 16});
	toolbox.ghostLegsAnim1->draw(palette, screen, Rect2<double>{initX1, initY + 32.0, 16, 16});
	toolbox.ghostLegsAnim2->draw(palette, screen, Rect2<double>{initX1 + 16.0, initY + 32.0, 16, 16});
	toolbox.ghostLegsAnim1->draw(palette, screen, Rect2<double>{initX2, initY + 32.0, 16, 16});
	toolbox.ghostLegsAnim2->draw(palette, screen, Rect2<double>{initX2 + 16.0, initY + 32.0, 16, 16});
}
void Enemy::draw(Interface& interface, SDL_Renderer* renderer) const {
	PacmanToolbox& toolbox = PacmanToolbox::getInstance();
	const double initX = _position.x * 16.0 - 16.0;
	const double initY = _position.y * 16.0 - 20.0;
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
	toolbox.ghostLegsAnim1->draw(palette, renderer, Rect2<double>{initX, initY + 32.0, 16, 16});
	toolbox.ghostLegsAnim2->draw(palette, renderer, Rect2<double>{initX + 16.0, initY + 32.0, 16, 16});
	toolbox.ghostLegsAnim1->draw(palette, renderer, Rect2<double>{initX1, initY + 32.0, 16, 16});
	toolbox.ghostLegsAnim2->draw(palette, renderer, Rect2<double>{initX1 + 16.0, initY + 32.0, 16, 16});
	toolbox.ghostLegsAnim1->draw(palette, renderer, Rect2<double>{initX2, initY + 32.0, 16, 16});
	toolbox.ghostLegsAnim2->draw(palette, renderer, Rect2<double>{initX2 + 16.0, initY + 32.0, 16, 16});
}