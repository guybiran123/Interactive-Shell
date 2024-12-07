#pragma once

#include <string>
#include <vector>
#include "utils.h"

class Command {
protected:
	Message_s output;
	Message_s error;
	std::string flags;
	std::vector<std::string> arguments;

public:
	Command(const std::string& flags, const std::vector<std::string>& arguments);

	virtual void execute() = 0;

	//returns true if no errors were found
	virtual bool errorChecking() = 0;

	Message_s getOutput() const;

	Message_s getError() const;
};