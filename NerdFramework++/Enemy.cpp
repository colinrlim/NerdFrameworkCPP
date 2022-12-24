#include "PacmanToolbox.h"
#include "Enemy.h"
#include "Math.h"

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
	const double initY = _position.y * 16.0 - 24.0;
	if (_direction == DIRECTION_UP)
		toolbox.ghostUpStamper->draw(basePalette, screen, Rect2<double>{initX, initY, 32, 32});
	else if (_direction == DIRECTION_DOWN)
		toolbox.ghostDownStamper->draw(basePalette, screen, Rect2<double>{initX, initY, 32, 32});
	else if (_direction == DIRECTION_LEFT)
		toolbox.ghostLeftStamper->draw(basePalette, screen, Rect2<double>{initX, initY, 32, 32});
	else if (_direction == DIRECTION_RIGHT)
		toolbox.ghostRightStamper->draw(basePalette, screen, Rect2<double>{initX, initY, 32, 32});
	if (Math::dmod(interface.secondsElapsed(), 0.3) >= 0.15) {
		toolbox.ghostLegsStamper1->draw(basePalette, screen, Rect2<double>{initX, initY + 32.0, 16, 16});
		toolbox.ghostLegsStamper2->draw(basePalette, screen, Rect2<double>{initX + 16.0, initY + 32.0, 16, 16});
	}
	else if (Math::dmod(interface.secondsElapsed(), 0.3) < 0.15) {
		toolbox.ghostLegsStamper3->draw(basePalette, screen, Rect2<double>{initX, initY + 32.0, 16, 16});
		toolbox.ghostLegsStamper4->draw(basePalette, screen, Rect2<double>{initX + 16.0, initY + 32.0, 16, 16});
	}
}
void Enemy::draw(Interface& interface, SDL_Renderer* renderer) {
	PacmanToolbox& toolbox = PacmanToolbox::getInstance();
	const double initX = _position.x * 16.0 - 16.0;
	const double initY = _position.y * 16.0 - 24.0;
	if (_direction == DIRECTION_UP)
		toolbox.ghostUpStamper->draw(basePalette, renderer, Rect2<double>{initX, initY, 32, 32});
	else if (_direction == DIRECTION_DOWN)
		toolbox.ghostDownStamper->draw(basePalette, renderer, Rect2<double>{initX, initY, 32, 32});
	else if (_direction == DIRECTION_LEFT)
		toolbox.ghostLeftStamper->draw(basePalette, renderer, Rect2<double>{initX, initY, 32, 32});
	else if (_direction == DIRECTION_RIGHT)
		toolbox.ghostRightStamper->draw(basePalette, renderer, Rect2<double>{initX, initY, 32, 32});
	if (Math::dmod(interface.secondsElapsed(), 0.3) >= 0.15) {
		toolbox.ghostLegsStamper1->draw(basePalette, renderer, Rect2<double>{initX, initY + 32.0, 16, 16});
		toolbox.ghostLegsStamper2->draw(basePalette, renderer, Rect2<double>{initX + 16.0, initY + 32.0, 16, 16});
	}
	else if (Math::dmod(interface.secondsElapsed(), 0.3) < 0.15) {
		toolbox.ghostLegsStamper3->draw(basePalette, renderer, Rect2<double>{initX, initY + 32.0, 16, 16});
		toolbox.ghostLegsStamper4->draw(basePalette, renderer, Rect2<double>{initX + 16.0, initY + 32.0, 16, 16});
	}
}