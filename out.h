#pragma once
#include <string>
#include <iostream>
#include <memory>
#include "file_output.h"

class Out {
private:
	std::unique_ptr<FileOutput> persistentFileOutput = nullptr;
public:
	void writeConsole(const std::string& message);

	void writeError(const std::string& error);

	void writeToFile(const std::string& fileName, const std::string& message);

	void appendToFile(const std::string& fileName, const std::string& message);

	void setPersistentFile(const std::string& fileName, bool append);

	void writeToPersistentFile(const std::string message);

	void closePersistentFile();

	~Out();
};