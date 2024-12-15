#pragma once

#include <string>
#include <string_view>
#include <vector>
#include "utils.h"
#include "constants.h"

class Command {
protected:
	Message_s output;
	Message_s error;
	std::string flags;
	std::vector<std::string> arguments;
	std::string validFlags;

public:
	Command(const std::string& flags,
		const std::vector<std::string>& arguments,
		const std::string_view& validFlags);

	virtual void execute() = 0;

	//returns true if no errors were found
	virtual void errorChecking() = 0;

	bool areFlagsValid();

	Message_s getOutput() const;

	Message_s getError() const;
};