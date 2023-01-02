#pragma once

template <typename T>
struct Kinematics {
	T displacement;
	T velocity;
	T acceleration;
	T jerk;

	Kinematics() :
		displacement(),
		velocity(),
		acceleration(),
		jerk()
	{ }
	Kinematics(const T& displacement) :
		displacement(displacement),
		velocity(),
		acceleration(),
		jerk()
	{ }
	Kinematics(const T& displacement, const T& velocity) :
		displacement(displacement),
		velocity(velocity),
		acceleration(),
		jerk()
	{ }
	Kinematics(const T& displacement, const T& velocity, const T& acceleration) :
		displacement(displacement),
		velocity(velocity),
		acceleration(acceleration),
		jerk()
	{ }
	Kinematics(const T& displacement, const T& velocity, const T& acceleration, const T& jerk) :
		displacement(displacement),
		velocity(velocity),
		acceleration(acceleration),
		jerk(jerk)
	{ }

	static Kinematics<T> fromRandom(const Kinematics<T>& min, const Kinematics<T>& max) {
		return Kinematics<T>(
			T::fromRandom(min.displacement, max.displacement),
			T::fromRandom(min.velocity, max.velocity),
			T::fromRandom(min.acceleration, max.acceleration),
			T::fromRandom(min.jerk, max.jerk)
		);
	}
	static Kinematics<T> fromRandomArithmetic(const Kinematics<T>& min, const Kinematics<T>& max) {
		return Kinematics<T>(
			Math::random(min.displacement, max.displacement),
			Math::random(min.velocity, max.velocity),
			Math::random(min.acceleration, max.acceleration),
			Math::random(min.jerk, max.jerk)
		);
	}
	void update(double delta) {
		acceleration += jerk * delta;
		velocity += acceleration * delta;
		displacement += velocity * delta;
	}
};