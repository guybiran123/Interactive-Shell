#include "command.h"

Command::Command(const std::string& flags, const std::vector<std::string>& arguments) :
	flags{ flags },
	arguments{ arguments }
{
	output.initialize();
	error.initialize();
}

Message_s Command::getOutput() const {
	return output;
}

Message_s Command::getError() const {
	return error;
}