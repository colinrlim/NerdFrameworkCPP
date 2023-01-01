#pragma once

#include <deque>
#include <SDL.h>
#include "ColorSequence4.h"
#include "NumericRange.h"
#include "Vector2.h"
#include "Image4.h"
#include "Timer.h"

class ParticleBatcher {
public:
	struct Particle {
		Timer init;
		Vector2 position;
		Vector2 velocity;
		Vector2 acceleration;

		Particle(const Vector2& position, const Vector2& velocity, const Vector2& acceleration) :
			position(position),
			velocity(velocity),
			acceleration(acceleration)
		{
			init.tickNow();
		}

		void update(double delta) {
			position += velocity * delta;
			velocity += acceleration * delta;
		}
	};
private:
	std::deque<Particle> _particles;
public:
	Vector2 position;
	double particleRate;
	Timer lastGenerated;

	// Particle settings
	NumericRange<Vector2> initialOffset;
	NumericRange<Vector2> initialVelocity;
	NumericRange<Vector2> initialAcceleration;
	ColorSequence4 particleColor;
	double lifespan;

	void generate() {
		_particles.push_back(Particle(position + initialOffset.random(), initialVelocity.random(), initialAcceleration.random()));
	}
	void update(double delta) {
		for (auto iterator = _particles.begin(); iterator != _particles.end(); ++iterator) {
			if (iterator->init.tock() > lifespan)
				_particles.pop_front();
			else
				break;
		}
		if (lastGenerated.tock() >= particleRate) {
			lastGenerated.tickForward(particleRate);
			generate();
		}
	}

	void draw(Image4& screen, const Rect2<double>& bounds);
	void draw(SDL_Renderer* renderer, const Rect2<double>& bounds);
};

