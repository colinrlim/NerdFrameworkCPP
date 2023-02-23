#pragma once

#include <vector>
#include "MathNode.h"

class MathParser {
	struct Item {
		const char* ptr;
		const char precedence;
		const size_t size;
		const char id;

		Item(const char* ptr, const char precedence, const size_t size, const char id) :
			ptr(ptr),
			precedence(precedence),
			size(size),
			id(id)
		{ }
	};

	static Item getNextOperator(const char* string, size_t size);

	inline static bool substreq(const char* lhs, const char* rhs, size_t length) {
		for (size_t i = 0; i < length; i++)
			if (lhs[i] != rhs[i])
				return false;
		return true;
	}
public:
	static MathNode* toExpressionTree(const char* string, size_t size);
	inline static MathNode* toExpressionTree(const char* string) {
		return MathParser::toExpressionTree(string, std::strlen(string));
	}

	static std::vector<std::string> getUnknowns(MathNode* head);
	static double calculate(MathNode* head);
	static double solve(MathNode* head);
};