#include "ParticleBatcher.h"

ParticleBatcher::Particle::Particle(const Kinematics<Vector2>& position, const Kinematics<double>& rotation, const Kinematics<double>& size) :
	position(position),
	rotation(rotation),
	size(size)
{
	init.tickNow();
}

void ParticleBatcher::Particle::update(double delta) {
	position.update(delta);
	rotation.update(delta);
	size.update(delta);
}

const Rect2<double> ParticleBatcher::getBounds(const Rect2<double>& bounds, const Particle& particle) const {
	if (particleLockedToBatcher)
		return Rect2<double>(position.x + particle.position.displacement.x, position.y + particle.position.displacement.y, bounds.width * particle.size.displacement, bounds.height * particle.size.displacement);
	else
		return Rect2<double>(particle.position.displacement.x, particle.position.displacement.y, bounds.width * particle.size.displacement, bounds.height * particle.size.displacement);
}

ParticleBatcher::ParticleBatcher(Stamper* stamper, NumericRange<Kinematics<Vector2>> initialTranslational, NumericRange<Kinematics<double>> initialRotational, NumericRange<Kinematics<double>> initialSize) :
	stamper(stamper),
	initialTranslational(initialTranslational),
	initialRotational(initialRotational),
	initialSize(initialSize),
	particleRate(0.1),
	particleLifespan(4.0),
	particleLockedToBatcher(false)
{ }

std::deque<ParticleBatcher::Particle>& ParticleBatcher::getParticles() {
	return _particles;
}

void ParticleBatcher::generate() {
	_particles.push_back(Particle(Kinematics<Vector2>::fromRandom(initialTranslational.min, initialTranslational.max), Kinematics<double>::fromRandomArithmetic(initialRotational.min, initialRotational.max), Kinematics<double>::fromRandomArithmetic(initialSize.min, initialSize.max)));
	if (!particleLockedToBatcher)
		_particles.rbegin()->position.displacement += position;
}
void ParticleBatcher::update(double delta) {
	while (!_particles.empty()) {
		if (_particles.begin()->init.tock() > particleLifespan)
			_particles.pop_front();
		else
			break;
	}
	for (auto iterator = _particles.begin(); iterator != _particles.end(); ++iterator) {
		iterator->update(delta);
	}
	if (lastGenerated.tock() >= particleRate) {
		lastGenerated.tickForward(particleRate);
		generate();
	}
}

void ParticleBatcher::draw(Image4& screen, const Rect2<double>& bounds) {
	for (auto iterator = _particles.begin(); iterator != _particles.end(); ++iterator) {
		const Particle& particle = *iterator;
		stamper->draw(screen, getBounds(bounds, particle), particle.rotation.displacement, rotationOrigin, Stamper::ImageFlipOptions::FLIP_NONE, Stamper::ImageScaleType::STRETCH);
	}
}
void ParticleBatcher::draw(SDL_Renderer* renderer, const Rect2<double>& bounds) {
	for (auto iterator = _particles.begin(); iterator != _particles.end(); ++iterator) {
		const Particle& particle = *iterator;
		stamper->draw(renderer, getBounds(bounds, particle), particle.rotation.displacement, rotationOrigin, Stamper::ImageFlipOptions::FLIP_NONE, Stamper::ImageScaleType::STRETCH);
	}
}