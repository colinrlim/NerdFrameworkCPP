#pragma once

#include <string>

class VigenereCipher
{
public:
	static std::string encrypt(const std::string& input, const std::string& key);
	static std::string decrypt(const std::string& input, const std::string& key);
};

