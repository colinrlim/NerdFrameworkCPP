#include <fstream>
#include <array>
#include "ImageParser.h"
#include "String.h"

Image4 ImageParser::fromFile(const char* filename) {
	std::ifstream file(filename, std::ios::binary);
	if (!file)
		throw "File could not be found!";

	file.seekg(0, std::ios::end);
	std::streamsize size = file.tellg();
	file.seekg(0, std::ios::beg);

	String string(filename);
	Image4 image;
	
	if (string.endsWith(".png")) {
		uint8_t signature[8];
		static constexpr uint8_t TARGET_SIGNATURE[8]{ 0x89, 0x50, 0x4e, 0x47, 0x0d, 0x0a, 0x1a, 0x0a };
		static constexpr std::array<uint8_t, 4> IHDR_TYPE{ 'I', 'H', 'D', 'R' };
		static constexpr std::array<uint8_t, 4> IDAT_TYPE{ 'I', 'D', 'A', 'T' };
		static constexpr std::array<uint8_t, 4> PLTE_TYPE{ 'P', 'L', 'T', 'E' };
		static constexpr std::array<uint8_t, 4> tRNS_TYPE{ 't', 'R', 'N', 'S' };
		static constexpr std::array<uint8_t, 4> IEND_TYPE{ 'I', 'E', 'N', 'D' };

		file.read(reinterpret_cast<char*>(&signature), sizeof(uint8_t) * 8);
		for (size_t i = 0; i < 8; i++)
			if (signature[i] != TARGET_SIGNATURE[i])
				throw "Error: File is not a valid png.";

		int sizeLeft = (int)size - sizeof(uint8_t) * 8;

		uint8_t bitDepth;
		uint8_t colorType;
		uint8_t compressionMethod;
		uint8_t filterMethod;
		uint8_t interlaceMethod;

		while (sizeLeft > 0) {
			uint32_t length;
			file.read(reinterpret_cast<char*>(&length), sizeof(uint8_t) * 4);
			std::array<uint8_t, 4> type;
			file.read(reinterpret_cast<char*>(type.data()), sizeof(uint8_t) * 4);
			if (type == IHDR_TYPE) {
				uint32_t width;
				uint32_t height;
				file.read(reinterpret_cast<char*>(&width), sizeof(uint8_t) * 4);
				file.read(reinterpret_cast<char*>(&height), sizeof(uint8_t) * 4);
				image = std::move(Image4(width, height));

				file.read(reinterpret_cast<char*>(&bitDepth), sizeof(uint8_t));
				file.read(reinterpret_cast<char*>(&colorType), sizeof(uint8_t));
				file.read(reinterpret_cast<char*>(&compressionMethod), sizeof(uint8_t));
				file.read(reinterpret_cast<char*>(&filterMethod), sizeof(uint8_t));
				file.read(reinterpret_cast<char*>(&interlaceMethod), sizeof(uint8_t));
			} else if (type == IDAT_TYPE) {

			} else if (type == PLTE_TYPE) {

			} else if (type == tRNS_TYPE) {

			} else if (type == IEND_TYPE) {
				break;
			} else
				throw "Error: SUS chunk! Type unknown!";
			uint32_t crc;
			file.read(reinterpret_cast<char*>(&crc), sizeof(uint8_t) * 4);
			sizeLeft -= sizeof(uint8_t) * 12 + length;
		}
	}

	return image;
}
void ImageParser::toFile(const Image4& image, const char* filename) {

}