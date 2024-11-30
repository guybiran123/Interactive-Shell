#include "cli_command.h"

void CliCommand::execute(const std::string& cliCommand, bool userEntered = true) {
	initialize(cliCommand);
	searchRedirection();
	ParsedCommand_s parsedCommand;
	createParsedCommand(parsedCommand);
	std::unique_ptr<Command> command = createCommand(parsedCommand);
	command->execute();
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

void CliCommand::createParsedCommand(ParsedCommand_s& parsedCommand) {
	std::vector<std::string> splittedCommand = split(cliCommand, ' ');
	parsedCommand.commandName = splittedCommand.at(FIRST_INDEX);
	splittedCommand.erase(splittedCommand.begin());
	parsedCommand.flags = "";
	if (splittedCommand.at(FIRST_INDEX).at(FIRST_INDEX) == FLAGS_SYMBOL) {
		parsedCommand.flags = splittedCommand.at(FIRST_INDEX);
		splittedCommand.erase(splittedCommand.begin());
	}
	parsedCommand.arguments = splittedCommand;
}

std::unique_ptr<Command> CliCommand::createCommand(const ParsedCommand_s& parsedCommand) {
	using commandCreator = std::function<std::unique_ptr<Command>(const ParsedCommand_s&)>;

	static std::unordered_map<std::string, commandCreator> commandTable = {
		{"echo", [](const ParsedCommand_s& parsedCommand) { return std::make_unique<EchoCommand>(parsedCommand.flags, parsedCommand.arguments); }}
	};

	auto iterator = commandTable.find(parsedCommand.commandName);
	if (iterator != commandTable.end()) {
		return iterator->second(parsedCommand);
	}
	else {
		return nullptr;
	}
}



