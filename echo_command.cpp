#include "echo_command.h"

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