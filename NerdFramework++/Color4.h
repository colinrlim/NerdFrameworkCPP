#pragma once

#include <functional>
#include <vector>
#include "Color3.h"
struct Color3;

struct Color4
{
private:
	static void flatten(uint8_t& b_r, uint8_t& b_g, uint8_t& b_b, uint8_t& b_a,
						uint8_t  t_r, uint8_t  t_g, uint8_t  t_b, uint8_t  t_a);
	static Color4 flattened(uint8_t b_r, uint8_t b_g, uint8_t b_b, uint8_t b_a,
						  uint8_t t_r, uint8_t t_g, uint8_t t_b, uint8_t t_a);
	static uint8_t lerpValue(uint8_t x0, uint8_t x1, double alpha);
public:
	uint8_t r;
	uint8_t g;
	uint8_t b;
	uint8_t alpha;

	Color4(uint8_t r, uint8_t g, uint8_t b, uint8_t alpha = 255);
	Color4(void* pixel);

	static const Color4 none;
	static const Color4 white;
	static const Color4 black;

	static const Color4 red;
	static const Color4 green;
	static const Color4 blue;

	static const Color4 lightRed;
	static const Color4 lightGreen;
	static const Color4 lightBlue;

	static Color4 fromVector3(const Vector3& v);
	static Color4 lerp(const Color4& a, const Color4& b, double alpha);
	static Color4 average(const Color4& color1, const Color4& color2);
	static Color4 average(const std::vector<Color4>& colors);
	static Color4 fromParameterization(double t, double s, const Color4& a, const Color4& b, const Color4& c);
	static uint8_t valueFromParameterization(double t, double s, const Color4& a, const Color4& b, const Color4& c);

	static Color4 flattened(const Color4& bottom, const Color4& top);
	static Color4 flattened(const Color4& bottom, const void* top);
	void flatten(const Color4& top);
	void flatten(const void* top);
	static void flatten(void* bottom, const Color4& top);
	static void flatten(void* bottom, const void* top);

	double luma() const;
	uint8_t value() const;
	Color4 modified(std::function<Color4(const Color4&)> func) const;
	Color4 modified(const Color4& rhs, std::function<Color4(const Color4&, const Color4&)> func) const;
	Color4 withAlpha(char alpha) const;
	Color3 asColor3() const;
	Color4 grayscaled() const;
	Color4 opaque() const;
	Color4 invisible() const;

	void writeToPixel(void* pixel) const;
};

