#include "String.h"

String::String(char character) :
	_data(1)
{
	_data.push_back(character);
}
String::String(const char* string) {
	size_t size = 0;
	while (string[size] != '\0')
		size++;
	_data.reserve(size);
	for (size_t i = 0; i < size; i++)
		_data.push_back(*(string + i));
}
String::String(const std::string& string) :
	_data(string.length())
{
	const char* data = string.data();
	for (size_t i = 0; i < string.length(); i++)
		_data.push_back(*(data + i));
}
String::String(const String& string) :
	_data(string._data.size())
{
	const char* data = string._data.data();
	for (size_t i = 0; i < string._data.size(); i++)
		_data.push_back(*(data + i));
}
String& String::operator=(char character) {
	_data.clear();
	_data.push_back(character);
	return *this;
}
String& String::operator=(const char* string) {
	_data.clear();
	size_t size = 0;
	while (string[size] != '\0')
		size++;
	_data.reserve(size);
	for (size_t i = 0; i < size; i++)
		_data.push_back(*(string + i));
	return *this;
}
String& String::operator=(const std::string& string) {
	_data.clear();
	size_t size = string.length();
	_data.reserve(size);
	const char* data = string.data();
	for (size_t i = 0; i < size; i++)
		_data.push_back(*(data + i));
	return *this;
}
String& String::operator=(const String& string) {
	_data.clear();
	size_t size = string._data.size();
	_data.reserve(size);
	const char* data = string._data.data();
	for (size_t i = 0; i < size; i++)
		_data.push_back(*(data + i));
	return *this;
}

bool String::startsWith(char character) {
	if (_data.size() < 1) return false;
	return _data[0] == character;
}
bool String::startsWith(const char* string) {
	size_t size = 0;
	while (string[size] != '\0')
		size++;
	if (_data.size() < size) return false;
	const char* data = _data.data();
	for (size_t i = 0; i < size; i++)
		if (*(data + i) != *(string + i))
			return false;
	return true;
}
bool String::startsWith(const std::string& string) {
	if (_data.size() < string.length()) return false;
	const char* data = _data.data();
	const char* s_data = string.data();
	for (size_t i = 0; i < string.length(); i++)
		if (*(data + i) != *(s_data + i))
			return false;
	return true;
}
bool String::startsWith(const String& string) {
	if (_data.size() < string._data.size()) return false;
	const char* data = _data.data();
	const char* s_data = string._data.data();
	for (size_t i = 0; i < string._data.size(); i++)
		if (*(data + i) != *(s_data + i))
			return false;
	return true;
}

bool String::endsWith(char character) {
	size_t size = _data.size();
	if (size < 1) return false;
	return *(_data.data() + size - 1) == character;
}
bool String::endsWith(const char* string) {
	size_t size = 0;
	while (string[size] != '\0')
		size++;
	size_t diff = _data.size() - size;
	if (diff < 0) return false;
	const char* data = _data.data();
	for (size_t i = diff, x = 0; i < _data.size(); i++, x++)
		if (*(data + i) != *(string + x))
			return false;
	return true;
}
bool String::endsWith(const std::string& string) {
	size_t diff = _data.size() - string.length();
	if (diff < 0) return false;
	const char* data = _data.data();
	const char* s_data = string.data();
	for (size_t i = diff, x = 0; i < _data.size(); i++, x++)
		if (*(data + i) != *(s_data + x))
			return false;
	return true;
}
bool String::endsWith(const String& string) {
	size_t diff = _data.size() - string._data.size();
	if (diff < 0) return false;
	const char* data = _data.data();
	const char* s_data = string._data.data();
	for (size_t i = diff, x = 0; i < _data.size(); i++, x++)
		if (*(data + i) != *(s_data + x))
			return false;
	return true;
}

char* String::data() {
	return _data.data();
}
const char* String::data() const {
	return _data.data();
}
size_t String::length() const {
	return _data.size();
}

char String::operator[](size_t index) const {
	return _data[index];
}
char& String::operator[](size_t index) {
	return _data[index];
}

void String::operator+(char character) {
	_data.push_back(character);
}
void String::operator+(const char* string) {
	size_t size = 0;
	while (string[size] != '\0')
		size++;
	_data.reserve(_data.capacity() + size);
	for (size_t i = 0; string[i] != '\0'; i++)
		_data.push_back(string[i]);
}
void String::operator+(const std::string& string) {
	_data.reserve(_data.capacity() + string.length());
	for (size_t i = 0; i < string.length(); i++)
		_data.push_back(string[i]);
}
void String::operator+(const String& string) {
	_data.reserve(_data.capacity() + string._data.size());
	for (size_t i = 0; i < string._data.size(); i++)
		_data.push_back(string[i]);
}

bool String::operator==(char character) {
	if (_data.size() != 1) return false;
	return *_data.data() == character;
}
bool String::operator==(const char* string) {
	size_t size = _data.size();
	size_t i = 0;
	const char* data = _data.data();
	while (string[i] != '\0') {
		if (i == size) return false;
		if (*(data + i) != *(string + i)) return false;
		i++;
	}
	return i == --size;
}
bool String::operator==(const std::string& string) {
	if (_data.size() != string.length()) return false;
	const char* data = _data.data();
	const char* s_data = string.data();
	for (size_t i = 0; i < _data.size(); i++)
		if (*(data + i) != *(s_data + i)) return false;
	return true;
}
bool String::operator==(const String& string) {
	if (_data.size() != string._data.size()) return false;
	const char* data = _data.data();
	const char* s_data = string._data.data();
	for (size_t i = 0; i < _data.size(); i++)
		if (*(data + i) != *(s_data + i)) return false;
	return true;
}
bool String::operator!=(char character) {
	return !(*this == character);
}
bool String::operator!=(const char* string) {
	return !(*this == string);
}
bool String::operator!=(const std::string& string) {
	return !(*this == string);
}
bool String::operator!=(const String& string) {
	return !(*this == string);
}

std::ostream& operator<<(std::ostream& stream, const String& rhs) {
	const char* data = rhs.data();
	size_t length = rhs.length();
	for (size_t i = 0; i < length; i++)
		stream << *(data + i);
	return stream;
}