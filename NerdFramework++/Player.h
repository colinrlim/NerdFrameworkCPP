#pragma once

#include "Entity.h"

class Player : public Entity {
private:
	uint16_t _lastPositionTile;
public:
	void update(double seconds);
};

