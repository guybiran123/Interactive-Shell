#pragma once
#include <fstream>
#include <filesystem>
#include "utils.h"

class FileOutput {
private:
	std::ofstream file;

public:
	FileOutput(const std::string& fileName, bool append);

	~FileOutput();

	void write(const std::string& message);
};