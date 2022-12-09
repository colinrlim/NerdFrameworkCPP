#pragma once

#include <string>

class Font
{
private:
	std::string name;

	Font(const std::string& name);
	
	Font(const Font& rhs);
	~Font();
	Font& operator=(const Font& rhs);

	friend class FontManager;
};

