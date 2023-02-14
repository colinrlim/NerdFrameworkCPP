#pragma once

#include <vector>
#include "MathNode.h"

class MathParser {
public:
	static MathNode* fromString(char* string, size_t size);
	static std::vector<std::string> getUnknowns(MathNode* head);
	static double calculate(MathNode* head);
	static double solve(MathNode* head);
};