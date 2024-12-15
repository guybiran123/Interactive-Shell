#pragma once

#include <fstream>
#include <string>

class FileReader {
private:
	std::ifstream file;

public:
	FileReader(const std::string& fileName);

	~FileReader();

	std::string read();
};