#pragma once
#include <string>
#include <iostream>
#include "file_output.h"


/*
std::vector<std::string> a = {"hello", "world"};
std::vector<int> b = {1, 2, 3};
auto c = zip(a, b) //{{"hello", 1}, {"world", 2}}
auto d = zip(a, b, c) //{{"hello", 1, {"hello", 1}}, {"world", 2, {"world", 2}}};
*/


class Out {
private:
	std::unique_ptr<FileOutput> persistentFileOutput = nullptr;
public:
	void writeConsole(const std::string& message) {
		std::cout << message << '\n';
	}

	void writeError(const std::string& error) {
		std::cerr << error << '\n';
	}

	void writeToFile(const std::string& fileName, const std::string& message) {
		FileOutput fileOutput(fileName, false);
		fileOutput.write(message);
	}

	void appendToFile(const std::string& fileName, const std::string& message) {
		FileOutput fileOutput(fileName, true);
		fileOutput.write(message);
	}

	void setPersistentFile(const std::string& fileName, bool append) {
		if (persistentFileOutput) {
			persistentFileOutput.reset();
		}
		persistentFileOutput = std::make_unique<FileOutput>(fileName, append);
	}

	void writeToPersistentFile(const std::string message) {
		if (!persistentFileOutput) {
			throw std::runtime_error("Persistent file not set. Call setPersistentFile first.");
		}
		persistentFileOutput->write(message);
	}

	void closePersistentFile() {
		persistentFileOutput.reset();
	}

	~Output() {
		persistentFileOutput.reset();
	}
};