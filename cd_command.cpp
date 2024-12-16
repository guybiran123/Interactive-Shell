#include "cd_command.h"

CdCommand::CdCommand(const std::string& flags, const std::vector<std::string>& arguments) :
	Command(flags, arguments, CD_VALID_FLAGS) {}

void CdCommand::execute() {
	try {
		errorChecking();
	}
	catch (const std::runtime_error& exception) {
		error.doesExist = true;
		error.message = exception.what();
		return;
	}
	if (arguments.empty() || arguments.at(FIRST_INDEX) == "~") {
		changeDirectory(EnvVars::getVar("HOME"));
	}
	else if (arguments.at(FIRST_INDEX) == "-") {
		changeDirectory(EnvVars::getVar("OLDPWD"));
	}
	/*
	V cd – Goes to your home directory. 
	cd /path/to/directory – Goes to an absolute path.
	cd relative/directory – Goes to a directory relative to the current one.
	cd .. – Goes to the parent directory.
	V cd - – Goes to the previous directory.
	V cd ~ – Goes to your home directory (equivalent to cd with no arguments).
	cd / – Goes to the root directory.
	*/
	
}

void CdCommand::errorChecking() {
	if (!areFlagsValid()) {
		throw std::runtime_error("cd: invalid option -- '" + flags + "'");
	}
	if (arguments.size() > 1) {
		throw std::runtime_error("cd: too many arguments");
	}
}

void CdCommand::changeDirectory(const std::string& directory) {
	EnvVars::setVar("OLDPWD", EnvVars::getVar("PWD"));
	EnvVars::setVar("PWD", directory);
}