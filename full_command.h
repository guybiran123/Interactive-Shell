#pragma once

#include <string>

class FullCommand {
private:
	std::string fullCommand;
	std::string output;
	bool redirect;
	std::string fileName;

public:
	FullCommand() = default;

	void execute(const std::string& fullCommand, bool userEntered = true);

	void initialize(const std::string& fullCommand);

	void searchRedirection();

};