#pragma once

#include <string>

class CaesarCipher
{
public:
	static std::string encrypt(const std::string& input, int key);
	static std::string decrypt(const std::string& input, int key);

	static char encrypt(char input, int key);
	static char decrypt(char input, int key);
};

