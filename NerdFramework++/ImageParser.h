#pragma once

#include <string>
#include "Image4.h"

class ImageParser
{
public:
	static Image4 fromFile(const char* filename);
	static void toFile(const Image4& image, const char* filename);
};

