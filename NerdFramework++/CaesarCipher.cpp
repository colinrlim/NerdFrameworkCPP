#include "CaesarCipher.h"
#include <string>

std::string CaesarCipher::encrypt(const std::string& input, int key) {
	std::string newStr(input);
	for (size_t i = 0; i < input.length(); i++) {
		newStr[i] = CaesarCipher::encrypt(input[i], key);
	}
	return newStr;
}
std::string CaesarCipher::decrypt(const std::string& input, int key) {
	return CaesarCipher::encrypt(input, -key);
}

char CaesarCipher::encrypt(char input, int key) {
	if (input >= 'a' && input <= 'z')
		return 'a' + (input - 'a' + key % 26 + 26) % 26;
	else if (input >= 'A' && input <= 'Z')
		return 'A' + (input - 'A' + key % 26 + 26) % 26;
	return input;
}
char CaesarCipher::decrypt(char input, int key) {
	return CaesarCipher::encrypt(input, -key);
}