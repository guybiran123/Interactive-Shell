#pragma once
#include <fstream>

class FileOutput {
private:
	std::ofstream file;

public:
	FileOutput(const std::string& fileName, bool append);

	~FileOutput();

	void write(const std::string& message);
};