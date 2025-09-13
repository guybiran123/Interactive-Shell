#include "help_command.h"
#include "help_messages.h"

HelpCommand::HelpCommand(const std::string& flags, const std::vector<std::string>& arguments) :
	Command(flags, arguments, HELP_VALID_FLAGS) {}

void HelpCommand::execute() {
	try {
		errorChecking();
	}
	catch (const std::runtime_error& exception) {
		writeErrorMessage(exception.what());
		return;
	}
	writeHelpMessage();
}

void HelpCommand::errorChecking() {
	if (!areFlagsValid()) {
		throw std::runtime_error("help: invalid option -- '" + flags + "'");
	}
	if (arguments.size() > 1) {
		throw std::runtime_error("help: too many arguments");
	}
	if (!arguments.empty()) {
		if (!COMMAND_TO_HELP_MESSAGE.contains(arguments[FIRST_INDEX])) {
			throw std::runtime_error("help: no help topics match '" + arguments[FIRST_INDEX] + "'");
		}
	}	
}

void HelpCommand::writeHelpMessage() {
	
	if (arguments.empty()) {
		writeOutputMessage(std::string(DEFAULT_HELP_MESSAGE));
	}
	else {
		writeOutputMessage(std::string(COMMAND_TO_HELP_MESSAGE.at(arguments[FIRST_INDEX])));
	}
}

const std::unordered_map<std::string, std::string_view> HelpCommand::COMMAND_TO_HELP_MESSAGE = {
	{"echo", ECHO_HELP_MESSAGE},
	{"cat",  CAT_HELP_MESSAGE},
	{"cd",   CD_HELP_MESSAGE},
	{"ls",   LS_HELP_MESSAGE},
	{"help", HELP_HELP_MESSAGE}
};