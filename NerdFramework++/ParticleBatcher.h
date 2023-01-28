#pragma once

#include "ColorSequence.h"
#include "NumericRange.h"
#include "Kinematics.h"
#include "Stamper.h"
#include "Vector2.h"
#include "Timer.h"

class ParticleBatcher {
public:
	struct Particle {
		Particle* next;

		Timer init;
		Kinematics<Vector2> position;
		Kinematics<double> rotation;
		Kinematics<double> size;

		Particle(const Kinematics<Vector2>& position, const Kinematics<double>& rotation, const Kinematics<double>& size, Particle* next = nullptr);

		void update(double delta);
	};
private:
	Particle* _front;
	Particle* _back;

	const Rect2<double> getBounds(const Rect2<double>& bounds, const Particle& particle) const;
public:
	Stamper* stamper;
	Vector2i rotationOrigin;
	Vector2 position;

	double particleRate;
	double particleLifespan;
	ColorSequence4 particleColor;
	bool particleLockedToBatcher;

	Timer lastGenerated;

	// Particle settings
	NumericRange<Kinematics<Vector2>> initialTranslational;
	NumericRange<Kinematics<double>> initialRotational;
	NumericRange<Kinematics<double>> initialSize;

	ParticleBatcher(Stamper* stamper, NumericRange<Kinematics<Vector2>> initialTranslational, NumericRange<Kinematics<double>> initialRotational, NumericRange<Kinematics<double>> initialSize);

	Particle* getFront();
	Particle* getBack();

	void generate();
	void update(double delta);

	void draw(Image4& screen, const Rect2<double>& bounds);
	void draw(SDL_Renderer* renderer, const Rect2<double>& bounds);
};

