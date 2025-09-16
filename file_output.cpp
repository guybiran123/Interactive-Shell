#include "file_output.h"

FileOutput::FileOutput(const std::string& fileName, bool append) {
	std::filesystem::path p = resolvePath(fileName);
	file.open(p, (append ? std::ios::app : std::ios::out));
	if (!file.is_open()) {
		throw std::runtime_error("Failed to open file: " + p.string());
	}
}

FileOutput::~FileOutput() {
	if (file.is_open()) {
		file.close();
	}
}

void FileOutput::write(const std::string& message) {
	file << message;
}