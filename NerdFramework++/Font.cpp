#include "Font.h"

Font::Font(const std::string& name) : name(name) { }

Font::Font(const Font& rhs) { }
Font::~Font() { }
Font& Font::operator=(const Font& rhs) { return *this; }