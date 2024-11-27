#pragma once
#include <fstream>

class FileOutput {
private:
	std::ofstream file;
public:
	FileOutput(const std::string& fileName, bool append) {
		file.open(fileName, (append ? std::ios::app : std::ios::out));
		if (!file.is_open()) {
			throw std::runtime_error("Failed to open file: " + fileName);
		}
	}

	~FileOutput() {
		if (file.is_open()) {
			file.close();
		}
	}

	void write(const std::string& message) {
		file << message;
	}
};