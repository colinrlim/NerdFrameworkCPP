#pragma once

#include <functional>
#include <vector>
#include "Vector3.h"
#include "Color4.h"
struct Color4;

struct Color3
{
private:
	static uint8_t lerpValue(uint8_t x0, uint8_t x1, double alpha);
public:
	uint8_t r;
	uint8_t g;
	uint8_t b;

	Color3(uint8_t r, uint8_t g, uint8_t b);
	Color3(void* pixel);

	static const Color3 none;
	static const Color3 white;
	static const Color3 black;

	static const Color3 red;
	static const Color3 green;
	static const Color3 blue;

	static const Color3 lightRed;
	static const Color3 lightGreen;
	static const Color3 lightBlue;

	static Color3 fromVector3(const Vector3& v);
	static Color3 lerp(const Color3& a, const Color3& b, double alpha);
	static Color3 average(const Color3& color1, const Color3& color2);
	static Color3 average(const std::vector<Color3>& colors);
	static Color3 fromParameterization(double t, double s, const Color3& a, const Color3& b, const Color3& c);
	static uint8_t valueFromParameterization(double t, double s, const Color3& a, const Color3& b, const Color3& c);
	
	double luma() const;
	uint8_t value() const;
	Color3 modified(std::function<Color3(const Color3&)> func) const;
	Color3 modified(const Color3& rhs, std::function<Color3(const Color3&, const Color3&)> func) const;
	Color3 grayscaled() const;
	Color4 asColor4(uint8_t alpha) const;

	void writeToPixel(void* pixel) const;
};

