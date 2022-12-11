#include "Color3.h"
#include "Math.h"

uint8_t Color3::lerpValue(uint8_t x0, uint8_t x1, double alpha) {
	return uint8_t(x0 * (1 - alpha) + x1 * alpha);
}

Color3::Color3(uint8_t r, uint8_t g, uint8_t b) : r(r), g(g), b(b) { }
Color3::Color3(void* pixel) : r(((uint8_t*)pixel)[0]), g(((uint8_t*)pixel)[1]), b(((uint8_t*)pixel)[2]) { }

const Color3 Color3::none(0, 0, 0);
const Color3 Color3::white(255, 255, 255);
const Color3 Color3::black(0, 0, 0);

const Color3 Color3::red(255, 0, 0);
const Color3 Color3::green(0, 255, 0);
const Color3 Color3::blue(0, 0, 255);

const Color3 Color3::lightRed(255, 127, 127);
const Color3 Color3::lightGreen(127, 255, 127);
const Color3 Color3::lightBlue(127, 127, 255);

Color3 Color3::fromVector3(const Vector3& v) {
	return Color3((uint8_t)(v.x * 255), (uint8_t)(v.y * 255), (uint8_t)(v.z * 255));
}
Color3 Color3::lerp(const Color3& a, const Color3& b, double alpha) {
	return Color3(Color3::lerpValue(a.r, b.r, alpha), Color3::lerpValue(a.g, b.g, alpha), Color3::lerpValue(a.b, b.b, alpha));
}
Color3 Color3::average(const Color3& color1, const Color3& color2) {
	return Color3((uint8_t)(color1.r * 0.5 + color2.r * 0.5), (uint8_t)(color1.g * 0.5 + color2.g * 0.5), (uint8_t)(color1.b * 0.5 + color2.b * 0.5));
}
Color3 Color3::average(const std::vector<Color3>& colors) {
	unsigned short r, g, b;
	r = g = b = 0;

	for (size_t i = 0; i < colors.size(); i++) {
		const Color3& color = colors[i];
		r += color.r;
		g += color.g;
		b += color.b;
	}

	return Color3((uint8_t)(r / colors.size()), (uint8_t)(g / colors.size()), (uint8_t)(b / colors.size()));
}
Color3 Color3::fromParameterization(double t, double s, const Color3& a, const Color3& b, const Color3& c) {
	double u = 1.0 - t - s;
	return Color3(
		(uint8_t)(a.r * u + b.r * t + c.r * s),
		(uint8_t)(a.g * u + b.g * t + c.g * s),
		(uint8_t)(a.b * u + b.b * t + c.b * s)
	);
}
uint8_t Color3::valueFromParameterization(double t, double s, const Color3& a, const Color3& b, const Color3& c) {
	double u = 1.0 - t - s;
	return (uint8_t)((a.r*u + a.g*u + a.b*u) / 3 + (b.r*t + b.g*t + b.b*t) / 3 + (c.r*s + c.g*s + c.b*s) / 3);
}

double Color3::luma() const {
	return Math::sqrt(Vector3::dot(Vector3(r / 255.0, g / 255.0, b / 255.0), Vector3(0.299, 0.587, 0.114)));
}
uint8_t Color3::value() const {
	return r / 3 + g / 3 + b / 3;
}
Color3 Color3::modified(std::function<Color3(const Color3&)> func) const {
	return func(*this);
}
Color3 Color3::modified(const Color3& rhs, std::function<Color3(const Color3&, const Color3&)> func) const {
	return func(*this, rhs);
}
Color3 Color3::grayscaled() const {
	int avg = this->value();
	return Color3(avg, avg, avg);
}
Color4 Color3::asColor4(uint8_t alpha) const {
	return Color4(r, g, b, alpha);
}

void Color3::writeToPixel(void* pixel) const {
	auto castedPixel = (uint8_t*)pixel;
	castedPixel[0] = this->r;
	castedPixel[1] = this->g;
	castedPixel[2] = this->b;
}

std::ostream& operator<<(std::ostream& stream, const Color3& rhs) {
	return stream << "{ r: " << rhs.r << ", g: " << rhs.g << ", b: " << rhs.b << " }";
}