#pragma once

#include <vector>
#include <string>

class Format
{
private:
	Format();
public:
	static std::vector<std::string> split(const std::string& input, const char delimitter);
};

