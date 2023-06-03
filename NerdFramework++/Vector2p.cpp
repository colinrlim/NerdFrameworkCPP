#include "Vector2p.h"
#include "Math.h"

Vector2p::Vector2p(double r, double theta) : r(r), theta(theta) { }
Vector2p::Vector2p(double s) : r(s), theta(0.0) { };
Vector2p::Vector2p(const Vector2& rectangular) : r(rectangular.magnitude()), theta(atan(rectangular.y / rectangular.x)) { }

const Vector2 Vector2::zero(0.0, 0.0);

Vector2 Vector2p::asRectangular() const {
	return Vector2(r * cos(theta), r * sin(theta));
}
double Vector2p::hashTheta() const {
	return Math::dmod(theta + (r < 0.0 ? PI : 0.0), TWO_PI);
}

void Vector2p::rotate(double radians) {
	this->theta += radians;
}
Vector2p Vector2p::rotated(double radians) const {
	Vector2p newVec(this->r, this->theta + radians);
	return newVec;
}

template <typename iter>
void Vector2::rotate(iter begin, iter end, double radians) {
	while (begin != end) {
		Vector2& vec = *begin;
		vec.theta += radians;
		++begin;
	}
}
template <typename iter, typename d_iter>
void Vector2::rotated(iter begin, iter end, d_iter dest, double radians) {
	while (begin != end) {
		*dest = begin->rotated(radians);
		++begin;
		++dest;
	}
}

Vector2p Vector2p::lerp(const Vector2p& a, const Vector2p& b, double alpha) {
	return Vector2p(a.r * (1 - alpha) + b.r * alpha, a.theta * (1 - alpha) + b.theta * alpha);
}
Vector2p Vector2p::fromRandom(const Vector2p& min, const Vector2p& max) {
	return Vector2p(Math::random(min.r, max.r), Math::random(min.theta, max.theta));
}

bool Vector2p::operator==(const Vector2p& rhs) const {
	return Math::abs(this->hash() - rhs.hash()) <= 0.00001;
}
bool Vector2p::operator!=(const Vector2p& rhs) const {
	return Math::abs(this->hash() - rhs.hash()) > 0.00001;
}

std::ostream& operator<<(std::ostream& stream, const Vector2& rhs) {
	return stream << "{ " << rhs.x << ", " << rhs.y << " }";
}