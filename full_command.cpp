#include "full_command.h"
#include "constants.h"

void CliCommand::execute(const std::string& cliCommand, bool userEntered = true) {
	initialize(cliCommand);
	searchRedirection();

}

void CliCommand::initialize(const std::string& cliCommand) {
	this->cliCommand = cliCommand;
	output = "";
	error = "";
	outRedirection.toRedirect = false;
	outRedirection.fileName = "";
	errRedirection.toRedirect = false;
	errRedirection.fileName = "";
}

//change it to work with both redirections in one command
void CliCommand::searchRedirection() { 
	int redirectionPos = cliCommand.find(OUTPUT_REDIRECTION_SYMBOL);
	if (redirectionPos != std::string::npos) {
		outRedirection.toRedirect = true;
		outRedirection.fileName = cliCommand.substr(redirectionPos + 1);
		cliCommand.erase(redirectionPos);
	}
	else {
		redirectionPos = cliCommand.find(ERROR_REDIRECTION_SYMBOL);
		if (redirectionPos != std::string::npos) {
			errRedirection.toRedirect = true;
			errRedirection.fileName = cliCommand.substr(redirectionPos + 1);
			cliCommand.erase(redirectionPos);
		}
	}
}
