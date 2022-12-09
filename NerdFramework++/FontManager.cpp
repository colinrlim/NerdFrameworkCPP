#include <stdexcept>
#include "FontManager.h"

FontManager::FontManager() : _fonts() { }

FontManager::FontManager(const FontManager& rhs) : _fonts() { }
FontManager::~FontManager() { }
FontManager& FontManager::operator=(const FontManager& rhs) { return *this; }

Font* FontManager::createFont(const std::string& filepath) {
	Font* newFont = new Font(filepath);
	_fonts.insert({ filepath, newFont });
	return newFont;
}
Font* FontManager::getFont(const std::string& name) const {
	try {
		return _fonts.at(name);
	}
	catch (const std::out_of_range&) {
		return nullptr;
	}
}
void FontManager::destroyFont(const std::string& name) {
	delete getFont(name);
	_fonts.erase(name);
}
void FontManager::destroyFont(Font* font) {
	_fonts.erase(font->name);
	delete font;
}