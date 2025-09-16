#pragma once

#include <fstream>
#include <string>
#include "utils.h"

class FileReader {
private:
	std::ifstream file;

public:
	FileReader(const std::string& fileName);

	~FileReader();

	std::string read();
};