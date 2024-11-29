#include "out.h"

void Out::writeConsole(const std::string& message) {
	std::cout << message << '\n';
}

void Out::writeError(const std::string& error) {
	std::cerr << error << '\n';
}

void Out::writeToFile(const std::string& fileName, const std::string& message) {
	FileOutput fileOutput(fileName, false);
	fileOutput.write(message);
}

void Out::appendToFile(const std::string& fileName, const std::string& message) {
	FileOutput fileOutput(fileName, true);
	fileOutput.write(message);
}

void Out::setPersistentFile(const std::string& fileName, bool append) {
	if (persistentFileOutput) {
		persistentFileOutput.reset();
	}
	persistentFileOutput = std::make_unique<FileOutput>(fileName, append);
}

void Out::writeToPersistentFile(const std::string message) {
	if (!persistentFileOutput) {
		throw std::runtime_error("Persistent file not set. Call setPersistentFile first.");
	}
	persistentFileOutput->write(message);
}

void Out::closePersistentFile() {
	persistentFileOutput.reset();
}

Out::~Out() {
	persistentFileOutput.reset();
}