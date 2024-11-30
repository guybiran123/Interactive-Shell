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

struct Redirection_s {
	bool toRedirect{ false };
	std::string fileName{ };
};

struct ParsedCommand_s {
	std::string commandName{ };
	std::string flags{ };
	std::vector<std::string> arguments{ };
};

class CliCommand {
private:
	std::string cliCommand;
	std::string output;
	std::string error;
	Redirection_s outRedirection;
	Redirection_s errRedirection;

public:
	CliCommand() = default;

	void execute(const std::string& cliCommand, bool userEntered = true);

	void initialize(const std::string& cliCommand);

	void searchRedirection();

	void createParsedCommand(ParsedCommand_s& parsedCommand);

	std::unique_ptr<Command> createCommand(const ParsedCommand_s& parsedCommand);
};