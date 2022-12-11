#pragma once

#include <vector>
#include <string>
#include "List.h"

class String {
private:
	List<char> _data;
public:
	String(char character);
	String(const char* string);
	String(const std::string& string);
	String(char*&& string);
	String(std::string&& string);
	String& operator=(char character);
	String& operator=(const char* string);
	String& operator=(const std::string& string);
	String& operator=(char*&& string);
	String& operator=(std::string&& string);

	bool startsWith(char character);
	bool startsWith(const char* string);
	bool startsWith(const std::string& string);
	bool startsWith(const String& string);

	bool endsWith(char character);
	bool endsWith(const char* string);
	bool endsWith(const std::string& string);
	bool endsWith(const String& string);

	std::vector<String&> split(char character);
	std::vector<String&> split(const char* string);
	std::vector<String&> split(const std::string& string);
	std::vector<String&> split(const String& string);

	char* data();
	const char* data() const;
	size_t length() const;

	char operator[](size_t index) const;
	char& operator[](size_t index);

	void operator+(char character);
	void operator+(const char* string);
	void operator+(const std::string& string);
	void operator+(const String& string);

	bool operator==(char character);
	bool operator==(const char* string);
	bool operator==(const std::string& string);
	bool operator==(const String& string);
	bool operator!=(char character);
	bool operator!=(const char* string);
	bool operator!=(const std::string& string);
	bool operator!=(const String& string);
};

std::ostream& operator<<(std::ostream& stream, const String& rhs);

