#pragma once

// Based off of Crazyman32's script

#include <vector>
#include "Vector2.h"

struct BezierCurve2 {
	std::vector<Vector2> points;
	
	BezierCurve2(std::vector<Vector2> points) : points(points) { }

	Vector2 getPoint(double interpolant) const;
	std::vector<Vector2> getPoints(double interpolantStep) const;
	std::vector<Vector2> getPointsBySegmentLength(double segmentLength) const;
	std::vector<Vector2> getPointsByNumberSegments(int numSegments) const;
	double getLength(double interpolantStep = 0.1) const;
};

