#include "VigenereCipher.h"
#include "CaesarCipher.h"

std::string VigenereCipher::encrypt(const std::string& input, const std::string& key) {
	std::string newStr(input);
	size_t keylen = key.length();
	for (size_t i = 0, v = 0; i < input.length(); i++) {
		if (input[i] >= 'a' && input[i] <= 'z') {
			newStr[i] = CaesarCipher::encrypt(input[i], key[v % keylen] - 'a');
			v++;
		} else if (input[i] >= 'A' && input[i] <= 'Z') {
			newStr[i] = CaesarCipher::encrypt(input[i], key[v % keylen] - 'a');
			v++;
		}
	}
	return newStr;
}
std::string VigenereCipher::decrypt(const std::string& input, const std::string& key) {
	std::string newStr(input);
	size_t keylen = key.length();
	for (size_t i = 0, v = 0; i < input.length(); i++) {
		if (input[i] >= 'a' && input[i] <= 'z') {
			newStr[i] = CaesarCipher::decrypt(input[i], key[v % keylen] - 'a');
			v++;
		}
		else if (input[i] >= 'A' && input[i] <= 'Z') {
			newStr[i] = CaesarCipher::decrypt(input[i], key[v % keylen] - 'a');
			v++;
		}
	}
	return newStr;
}