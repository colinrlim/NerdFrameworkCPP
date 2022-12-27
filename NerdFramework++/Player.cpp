#include "Player.h"

Player::Player(Vector2 position, uint16_t direction, float speed) :
	Entity(position, direction, speed)
{ }

void Player::draw(Interface& interface, Image4& screen) const {

}
void Player::draw(Interface& interface, SDL_Renderer* renderer) const {

}