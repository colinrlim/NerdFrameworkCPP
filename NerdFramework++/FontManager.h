#pragma once

#include <map>
#include <string>
#include "Font.h"

class FontManager
{
private:
	std::map<std::string, Font*> _fonts;

	FontManager();

	FontManager(const FontManager& rhs);
	~FontManager();
	FontManager& operator=(const FontManager& rhs);
public:
	static FontManager& getInstance() {
		static FontManager mine;
		return mine;
	}

	Font* createFont(const std::string& filepath);
	Font* getFont(const std::string& name) const;
	void destroyFont(const std::string& name);
	void destroyFont(Font* font);
};

