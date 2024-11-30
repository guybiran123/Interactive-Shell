#include "command.h"

Command::Command(const std::string& flags, const std::vector<std::string>& arguments) :
	output{ },
	error{ },
	flags{ flags },
	arguments{ arguments }
{}

const std::string& Command::getOutput() const {
	return output;
}

const std::string& Command::getError() const {
	return error;
}