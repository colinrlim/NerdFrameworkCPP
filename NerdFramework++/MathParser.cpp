#include "MathParser.h"

MathParser::MathNode::MathNode(MathParser::NodeType type, char* value, size_t size) :
	type(type),
	value(value),
	size(size)
{ }

MathParser::MathNode MathParser::fromString(char* string, size_t size) {
	MathNode head(MathParser::NodeType::UNPARSED, string, size);
	std::vector<char> frequencies;
	frequencies.reserve('^' - '%' + 1);
	
}