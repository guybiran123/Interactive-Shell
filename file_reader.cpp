#include "file_reader.h"

FileReader::FileReader(const std::string& fileName) {
	file.open(fileName);
	if (!file.is_open()) {
		throw std::runtime_error("Failed to open file: " + fileName);
	}
}

FileReader::~FileReader() {
	if (file.is_open()) {
		file.close();
	}
}

std::string FileReader::read() {
	std::string fileContent;
	std::string line;
	bool firstLoop = true;

	while (std::getline(file, line)) {
		if (!firstLoop) {
			fileContent += '\n';
		}
		fileContent += line;
		firstLoop = false;
	}

	return fileContent;
}