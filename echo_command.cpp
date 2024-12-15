#include "echo_command.h"

EchoCommand::EchoCommand(const std::string& flags, const std::vector<std::string>& arguments) :
	Command(flags, arguments, ECHO_VALID_FLAGS){}

void EchoCommand::execute() {
	try {
		errorChecking();
	}
	catch (const std::runtime_error& exception) {
		error.doesExist = true;
		error.message = exception.what();
		return;
	}
	output.doesExist = true;
	output.message = "";
	bool firstLoop = true;
	for (const std::string& str : arguments) {
		if (!firstLoop) {
			output.message += " ";
		}
		output.message += str;
		firstLoop = false;
	}
}

void EchoCommand::errorChecking() {
	if (!areFlagsValid()) {
		throw std::runtime_error("echo: invalid option -- '" + flags + "'");
	}
}