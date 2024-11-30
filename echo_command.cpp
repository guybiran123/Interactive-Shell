#include "echo_command.h"

void EchoCommand::execute() {
	for (const std::string& str : arguments) {
		output += str + " ";
	}
}