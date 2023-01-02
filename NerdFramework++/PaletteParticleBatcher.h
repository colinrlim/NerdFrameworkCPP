#pragma once

#include <deque>
#include "ColorSequence4.h"
#include "PaletteStamper.h"
#include "NumericRange.h"
#include "Kinematics.h"
#include "Vector2.h"
#include "Timer.h"

class PaletteParticleBatcher {
public:
	struct Particle {
		Timer init;
		Kinematics<Vector2> position;
		Kinematics<double> rotation;
		Kinematics<double> size;

		Particle(const Kinematics<Vector2>& position, const Kinematics<double>& rotation, const Kinematics<double>& size);

		void update(double delta);
	};
private:
	std::deque<Particle> _particles;

	const Rect2<double> getBounds(const Rect2<double>& bounds, const Particle& particle) const;
public:
	PaletteStamper* stamper;
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

	PaletteParticleBatcher(PaletteStamper* stamper, NumericRange<Kinematics<Vector2>> initialTranslational, NumericRange<Kinematics<double>> initialRotational, NumericRange<Kinematics<double>> initialSize);

	std::deque<Particle>& getParticles();

	void generate();
	void update(double delta);

	void draw(Image4& screen, const Rect2<double>& bounds);
	void draw(SDL_Renderer* renderer, const Rect2<double>& bounds);
	void draw(Palette<Color4>& palette, Image4& screen, const Rect2<double>& bounds);
	void draw(Palette<Color4>& palette, SDL_Renderer* renderer, const Rect2<double>& bounds);
};

