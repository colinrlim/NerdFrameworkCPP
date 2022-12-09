#include "Color4.h"
#include "Math.h"

uint8_t Color4::lerpValue(uint8_t x0, uint8_t x1, double alpha) {
	return uint8_t(x0 * (1 - alpha) + x1 * alpha);
}

Color4::Color4(uint8_t r, uint8_t g, uint8_t b, uint8_t alpha) : r(r), g(g), b(b), alpha(alpha) { }
Color4::Color4(void* pixel) : r(((uint8_t*)pixel)[0]), g(((uint8_t*)pixel)[1]), b(((uint8_t*)pixel)[2]), alpha(((uint8_t*)pixel)[3]) { }

const Color4 Color4::none(0, 0, 0, 0);
const Color4 Color4::white(255, 255, 255);
const Color4 Color4::black(0, 0, 0);

const Color4 Color4::red(255, 0, 0);
const Color4 Color4::green(0, 255, 0);
const Color4 Color4::blue(0, 0, 255);

const Color4 Color4::lightRed(255, 127, 127);
const Color4 Color4::lightGreen(127, 255, 127);
const Color4 Color4::lightBlue(127, 127, 255);

Color4 Color4::fromVector3(const Vector3& v) {
	return Color4((uint8_t)(v.x * 255), (uint8_t)(v.y * 255), (uint8_t)(v.z * 255));
}
Color4 Color4::lerp(const Color4& a, const Color4& b, double alpha) {
	return Color4(Color4::lerpValue(a.r, b.r, alpha), Color4::lerpValue(a.g, b.g, alpha), Color4::lerpValue(a.b, b.b, alpha), Color4::lerpValue(a.alpha, b.alpha, alpha));
}
Color4 Color4::average(const Color4& color1, const Color4& color2) {
	return Color4((uint8_t)(color1.r * 0.5 + color2.r * 0.5), (uint8_t)(color1.g * 0.5 + color2.g * 0.5), (uint8_t)(color1.b * 0.5 + color2.b * 0.5), (uint8_t)(color1.alpha * 0.5 + color2.alpha * 0.5));
}
Color4 Color4::average(const std::vector<Color4>& colors) {
	int r, g, b, a;
	r = g = b = a = 0;

	for (size_t i = 0; i < colors.size(); i++) {
		const Color4& color = colors[i];
		r += color.r;
		g += color.g;
		b += color.b;
		a += color.alpha;
	}

	return Color4((uint8_t)(r / colors.size()), (uint8_t)(g / colors.size()), (uint8_t)(b / colors.size()), (uint8_t)(a / colors.size()));
}
Color4 Color4::fromParameterization(double t, double s, const Color4& a, const Color4& b, const Color4& c) {
	double u = 1.0 - t - s;
	return Color4(
		(uint8_t)(a.r * u + b.r * t + c.r * s),
		(uint8_t)(a.g * u + b.g * t + c.g * s),
		(uint8_t)(a.b * u + b.b * t + c.b * s),
		(uint8_t)(a.alpha * u + b.alpha * t + c.alpha * s)
	);
}
uint8_t Color4::valueFromParameterization(double t, double s, const Color4& a, const Color4& b, const Color4& c) {
	double u = 1.0 - t - s;
	return (uint8_t)((a.r * u + a.g * u + a.b * u) / 3 + (b.r * t + b.g * t + b.b * t) / 3 + (c.r * s + c.g * s + c.b * s) / 3);
}

void Color4::flatten(uint8_t& b_r, uint8_t& b_g, uint8_t& b_b, uint8_t& b_a,
	                 uint8_t  t_r, uint8_t  t_g, uint8_t  t_b, uint8_t  t_a) {
	double bAlpha = b_a / 255.0;
	double tAlpha = t_a / 255.0;
	uint8_t topAlphaInv = 255 - t_a;
	b_r = (uint8_t)(t_r * tAlpha + b_r * bAlpha * topAlphaInv);
	b_g = (uint8_t)(t_g * tAlpha + b_g * bAlpha * topAlphaInv);
	b_b = (uint8_t)(t_b * tAlpha + b_b * bAlpha * topAlphaInv);
	b_a = (uint8_t)(t_a * tAlpha + b_a * bAlpha * topAlphaInv);
}
Color4 Color4::flattened(uint8_t b_r, uint8_t b_g, uint8_t b_b, uint8_t b_a,
                    	 uint8_t t_r, uint8_t t_g, uint8_t t_b, uint8_t t_a) {
	double bAlpha = b_a / 255.0;
	double tAlpha = t_a / 255.0;
	uint8_t topAlphaInv = 255 - t_a;
	return Color4(
		(uint8_t)(t_r * tAlpha + b_r * bAlpha * topAlphaInv),
		(uint8_t)(t_g * tAlpha + b_g * bAlpha * topAlphaInv),
		(uint8_t)(t_b * tAlpha + b_b * bAlpha * topAlphaInv),
		(uint8_t)(t_a * tAlpha + b_a * bAlpha * topAlphaInv)
	);
}
Color4 Color4::flattened(const Color4& bottom, const Color4& top) {
	return flattened(bottom.r, bottom.g, bottom.b, bottom.alpha, top.r, top.g, top.b, top.alpha);
}
Color4 Color4::flattened(const Color4& bottom, const void* top) {
	auto castedTop = (uint8_t*)top;
	return flattened(bottom.r, bottom.g, bottom.b, bottom.alpha, castedTop[0], castedTop[1], castedTop[2], castedTop[3]);
}
void Color4::flatten(const Color4& top) {
	flatten(r, g, b, alpha, top.r, top.g, top.b, top.alpha);
}
void Color4::flatten(const void* top) {
	auto castedTop = (uint8_t*)top;
	flatten(r, g, b, alpha, castedTop[0], castedTop[1], castedTop[2], castedTop[3]);
}
void Color4::flatten(void* bottom, const Color4& top) {
	auto castedBottom = (uint8_t*)bottom;
	flatten(castedBottom[0], castedBottom[1], castedBottom[2], castedBottom[3], top.r, top.g, top.b, top.alpha);
}
void Color4::flatten(void* bottom, const void* top) {
	auto castedBottom = (uint8_t*)bottom;
	auto castedTop = (uint8_t*)top;
	flatten(castedBottom[0], castedBottom[1], castedBottom[2], castedBottom[3], castedTop[0], castedTop[1], castedTop[2], castedTop[3]);
}

double Color4::luma() const {
	return Math::sqrt(Vector3::dot(Vector3(r / 255.0, g / 255.0, b / 255.0), Vector3(0.299, 0.587, 0.114)));
}
uint8_t Color4::value() const {
	return r / 3 + g / 3 + b / 3;
}
Color4 Color4::modified(std::function<Color4(const Color4&)> func) const {
	return func(*this);
}
Color4 Color4::modified(const Color4& rhs, std::function<Color4(const Color4&, const Color4&)> func) const {
	return func(*this, rhs);
}
Color4 Color4::withAlpha(char alpha) const {
	return Color4(r, g, b, (int)this->alpha * alpha / 255);
}
Color3 Color4::asColor3() const {
	return Color3((uint8_t)((int)r * alpha / 255), (uint8_t)((int)g * alpha / 255), (uint8_t)((int)b * alpha / 255));
}
Color4 Color4::grayscaled() const {
	int avg = this->value();
	return Color4(avg, avg, avg, alpha);
}
Color4 Color4::opaque() const {
	return Color4(r, g, b);
}
Color4 Color4::invisible() const {
	return Color4(r, g, b, 0);
}

void Color4::writeToPixel(void* pixel) const {
	auto castedPixel = (uint8_t*)pixel;
	castedPixel[0] = this->r;
	castedPixel[1] = this->g;
	castedPixel[2] = this->b;
	castedPixel[3] = this->alpha;
}