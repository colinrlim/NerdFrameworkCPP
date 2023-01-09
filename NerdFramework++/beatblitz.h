#pragma once

#include <string>
#include <vector>
#include "Vector2.h"

struct Object {
	int classID;
	double scale;
	bool dangerous;
	std::vector<Vector2> points;
};

struct BeatMap {
	std::string soundFile;
	std::vector<std::vector<Vector2>> templates;
	std::vector<Object> objects;
};