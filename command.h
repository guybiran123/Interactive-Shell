#pragma once

#include <string>
#include <vector>

class Command {
protected:
	std::string output;
	std::string error;
	std::string flags;
	std::vector<std::string> arguments;

public:
	Command(const std::string& flags, const std::vector<std::string>& arguments);

	virtual void execute() = 0;

	const std::string& getOutput() const;

	const std::string& getError() const;
};