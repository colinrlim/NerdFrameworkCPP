#include "Format.h"

std::vector<std::string> Format::split(const std::string& input, const char delimitter) {
	std::vector<std::string> args;
	std::string lastString = "";
	for (size_t i = 0; i < input.length(); i++) {
		if (input.at(i) == delimitter) {
			args.push_back(lastString);
			lastString = "";
			continue;
		}
		lastString += input.at(i);
	}
	args.push_back(lastString);
	return args;
}