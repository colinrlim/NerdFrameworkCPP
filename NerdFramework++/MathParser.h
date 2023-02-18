#pragma once

#include <vector>
#include "MathNode.h"

class MathParser {
	struct Item {
		const char* ptr;
		char precedence;
		size_t size;
		char id;

		Item(const char* ptr, char precedence, size_t size, char id) :
			ptr(ptr),
			precedence(precedence),
			size(size),
			id(id)
		{ }
	};

	static Item getNextOperator(const char* string, size_t size);
public:
	static MathNode* toExpressionTree(const char* string, size_t size);
	static MathNode* toExpressionTree(const char* string);

	static std::vector<std::string> getUnknowns(MathNode* head);
	static double calculate(MathNode* head);
	static double solve(MathNode* head);
};