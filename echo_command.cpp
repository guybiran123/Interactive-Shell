#include "echo_command.h"

EchoCommand::EchoCommand(const std::string& flags, const std::vector<std::string>& arguments) :
	Command(flags, arguments){}

void EchoCommand::execute() {
	if (errorChecking()) {
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
}

bool EchoCommand::errorChecking() {
	return true;
}