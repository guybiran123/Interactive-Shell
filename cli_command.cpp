#include "cli_command.h"

void Redirection_s::initialize() {
	toRedirect = false;
	fileName = "";
}

const std::vector<std::string> CliCommand::VALID_COMMANDS = { "echo" };

void CliCommand::execute(const std::string& cliCommand, bool userEntered) {
	//executes the full CLI command
	initialize(cliCommand);
	searchRedirection();
	ParsedCommand_s parsedCommand;
	createParsedCommand(parsedCommand);
	if (isValidCommand(parsedCommand.commandName)) {
		std::unique_ptr<Command> command = createCommand(parsedCommand);
		command->execute();
		getMessagesFromCommand(command);
	}
	else {
		writeErrorMessage(parsedCommand.commandName + ": command not found");
	}
	printMessages();
}

void CliCommand::initialize(const std::string& cliCommand) {
	//initializes the CliCommand object
	this->cliCommand = cliCommand;
	output.initialize();
	error.initialize();
	outRedirection.initialize();
	errRedirection.initialize();
}

// TODO: change it to work with both redirections in one command
void CliCommand::searchRedirection() { 
	// Searches for redirection in cli command
	int redirectionPos = cliCommand.find(ERROR_REDIRECTION_SYMBOL);
	if (redirectionPos != std::string::npos) {
		errRedirection.toRedirect = true;
		error.doesExist = true;
		errRedirection.fileName = cliCommand.substr(redirectionPos + 2);
		cliCommand.erase(redirectionPos);
	}
	else {
		redirectionPos = cliCommand.find(OUTPUT_REDIRECTION_SYMBOL);
		if (redirectionPos != std::string::npos) {
			outRedirection.toRedirect = true;
			output.doesExist = true;
			outRedirection.fileName = cliCommand.substr(redirectionPos + 1);
			cliCommand.erase(redirectionPos);
		}
	}

	
}

void CliCommand::createParsedCommand(ParsedCommand_s& parsedCommand) {
	//creates a parsed command 
	std::vector<std::string> splittedCommand = split(cliCommand, ' ');
	parsedCommand.commandName = splittedCommand.at(FIRST_INDEX);
	splittedCommand.erase(splittedCommand.begin());
	parsedCommand.flags = "";
	if (!splittedCommand.empty()) {
		if (splittedCommand.at(FIRST_INDEX).at(FIRST_INDEX) == FLAGS_SYMBOL) {
			parsedCommand.flags = splittedCommand.at(FIRST_INDEX).substr(1);
			splittedCommand.erase(splittedCommand.begin());
		}
	}
	parsedCommand.arguments = splittedCommand;
}

std::unique_ptr<Command> CliCommand::createCommand(const ParsedCommand_s& parsedCommand) {
	//creates a Command object out of a parsed command
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

bool CliCommand::isValidCommand(std::string commandName) {
	//returns true of the given command is valid
	return std::find(VALID_COMMANDS.begin(), VALID_COMMANDS.end(), commandName) != VALID_COMMANDS.end();
}

void CliCommand::writeErrorMessage(std::string message) {
	error.doesExist = true;
	error.message = message;
}

void CliCommand::getMessagesFromCommand(const std::unique_ptr<Command>& commandPtr) {
	output = commandPtr->getOutput();
	Message_s commandErr = commandPtr->getError();
	if (!(error.doesExist && !commandErr.doesExist)) {
		error = commandPtr->getError();
	}
}

void CliCommand::printMessages() {
	if (output.doesExist) {
		if (outRedirection.toRedirect) {
			try {
				out.writeToFile(outRedirection.fileName, output.message);
			}
			catch (const std::runtime_error& exception) {
				writeErrorMessage(exception.what());
			}
		}
		else {
			out.writeConsole(output.message);
		}
	}
	if (error.doesExist) {
		if (errRedirection.toRedirect) {
			try {
				out.writeToFile(errRedirection.fileName, error.message);
			}
			catch (const std::runtime_error& exception) {
				out.writeError(error.message + '\n' + exception.what());
			}
		}
		else {
			out.writeError(error.message);
		}
	}
}