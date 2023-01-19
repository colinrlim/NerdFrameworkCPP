#include "PaletteParticleBatcher.h"
#include <iostream>

PaletteParticleBatcher::Particle::Particle(const Kinematics<Vector2>& position, const Kinematics<double>& rotation, const Kinematics<double>& size, Particle* next) :
	position(position),
	rotation(rotation),
	size(size),
	next(next)
{
	init.tickNow();
}

void PaletteParticleBatcher::Particle::update(double delta) {
	position.update(delta);
	rotation.update(delta);
	size.update(delta);
}

const Rect2<double> PaletteParticleBatcher::getBounds(const Rect2<double>& bounds, const Particle& particle) const {
	const double particleWidth = bounds.width * particle.size.displacement;
	const double particleHeight = bounds.height * particle.size.displacement;
	if (particleLockedToBatcher)
		return Rect2<double>(position.x + particle.position.displacement.x - particleWidth / 2.0, position.y + particle.position.displacement.y - particleHeight / 2.0, particleWidth, particleHeight);
	else
		return Rect2<double>(particle.position.displacement.x - particleWidth / 2.0, particle.position.displacement.y - particleHeight / 2.0, particleWidth, particleHeight);
}

PaletteParticleBatcher::PaletteParticleBatcher(PaletteStamper* stamper, NumericRange<Kinematics<Vector2>> initialTranslational, NumericRange<Kinematics<double>> initialRotational, NumericRange<Kinematics<double>> initialSize) :
	stamper(stamper),
	initialTranslational(initialTranslational),
	initialRotational(initialRotational),
	initialSize(initialSize),
	particleRate(0.1),
	particleLifespan(4.0),
	particleLockedToBatcher(false),
	_back(nullptr),
	_front(nullptr)
{
	lastGenerated.tickNow();
}

PaletteParticleBatcher::Particle* PaletteParticleBatcher::getFront() {
	return _front;
}
PaletteParticleBatcher::Particle* PaletteParticleBatcher::getBack() {
	return _back;
}

void PaletteParticleBatcher::generate() {
	if (_front) {
		_back->next = new Particle(Kinematics<Vector2>::fromRandom(initialTranslational.min, initialTranslational.max), Kinematics<double>::fromRandomArithmetic(initialRotational.min, initialRotational.max), Kinematics<double>::fromRandomArithmetic(initialSize.min, initialSize.max));
		_back = _back->next;
	} else {
		_front = _back = new Particle(Kinematics<Vector2>::fromRandom(initialTranslational.min, initialTranslational.max), Kinematics<double>::fromRandomArithmetic(initialRotational.min, initialRotational.max), Kinematics<double>::fromRandomArithmetic(initialSize.min, initialSize.max));
	}
	if (!particleLockedToBatcher)
		_back->position.displacement += position;
}
void PaletteParticleBatcher::update(double delta) {
	while (_front) {
		if (_front->init.tock() > particleLifespan) {
			Particle* temp = _front;
			_front = _front->next;
			delete temp;
		} else
			break;
	}
	Particle* iterator = _front;
	while (iterator) {
		iterator->update(delta);
		iterator = iterator->next;
	}
	for (double tock = lastGenerated.tock(); tock >= particleRate; tock -= particleRate) {
		lastGenerated.tickForward(particleRate);
		generate();
	}
}

void PaletteParticleBatcher::draw(Image4& screen, const Rect2<double>& bounds) {
	Particle* iterator = _front;
	while (iterator) {
		const Particle& particle = *iterator;
		stamper->draw(screen, getBounds(bounds, particle), particle.rotation.displacement, rotationOrigin, Stamper::ImageFlipOptions::FLIP_NONE, Stamper::ImageScaleType::STRETCH);
		iterator = particle.next;
	}
}
void PaletteParticleBatcher::draw(SDL_Renderer* renderer, const Rect2<double>& bounds) {
	Particle* iterator = _front;
	while (iterator) {
		const Particle& particle = *iterator;
		stamper->draw(renderer, getBounds(bounds, particle), particle.rotation.displacement, rotationOrigin, Stamper::ImageFlipOptions::FLIP_NONE, Stamper::ImageScaleType::STRETCH);
		iterator = particle.next;
	}
}
void PaletteParticleBatcher::draw(Palette<Color4>& palette, Image4& screen, const Rect2<double>& bounds) {
	Particle* iterator = _front;
	while (iterator) {
		const Particle& particle = *iterator;
		stamper->draw(palette, screen, getBounds(bounds, particle), particle.rotation.displacement, rotationOrigin, Stamper::ImageFlipOptions::FLIP_NONE, Stamper::ImageScaleType::STRETCH);
		iterator = particle.next;
	}
}
void PaletteParticleBatcher::draw(Palette<Color4>& palette, SDL_Renderer* renderer, const Rect2<double>& bounds) {
	Particle* iterator = _front;
	while (iterator) {
		const Particle& particle = *iterator;
		stamper->draw(palette, renderer, getBounds(bounds, particle), particle.rotation.displacement, rotationOrigin, Stamper::ImageFlipOptions::FLIP_NONE, Stamper::ImageScaleType::STRETCH);
		iterator = particle.next;
	}
}