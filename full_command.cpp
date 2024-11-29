#include "full_command.h"
#include "constants.h"

void FullCommand::execute(const std::string& fullCommand, bool userEntered = true) {
	initialize(fullCommand);
	searchRedirection();

}

void FullCommand::initialize(const std::string& fullCommand) {
	this->fullCommand = fullCommand;
	output = "";
	redirect = false;
	fileName = "";
}

void FullCommand::searchRedirection() {
	int redirectionPos = fullCommand.find(OUTPUT_REDIRECTION_CHARACTER);
	if (redirectionPos != std::string::npos) {
		redirect = true;
		fileName = fullCommand.substr(redirectionPos + 1);
		fullCommand.erase(redirectionPos);
	}
}
