#pragma once

#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <functional>

#include "constants.h"
#include "utils.h"
#include "command.h"
#include "echo_command.h"
#include "cat_command.h"
#include "cd_command.h"
#include "ls_command.h"
#include "out.h"

struct Redirection_s {
	bool toRedirect{ false };
	std::string fileName{ };

	void initialize();
};

struct ParsedCommand_s {
	std::string commandName{ };
	std::string flags{ };
	std::vector<std::string> arguments{ };
};

class CliCommand {
private:
	Out out;
	std::string cliCommand;
	Message_s output;
	Message_s error;
	Redirection_s outRedirection;
	Redirection_s errRedirection;

	static const std::vector<std::string> VALID_COMMANDS;

public:
	CliCommand() = default;

	void execute(const std::string& cliCommand, bool userEntered = true);

	void initialize(const std::string& cliCommand);

	void searchRedirection();

	void removeLeadingAndTrailingSpaces();

	void createRedirectionFileNameString(std::string& redirectionFileName, int redirectionPos, int redirectionSymbolLength);

	void createParsedCommand(ParsedCommand_s& parsedCommand);

	std::unique_ptr<Command> createCommand(const ParsedCommand_s& parsedCommand);

	static bool isValidCommand(const std::string& commandName);

	void writeErrorMessage(const std::string& message);

	void getMessagesFromCommand(const std::unique_ptr<Command>& commandPtr);

	void printMessages();
};