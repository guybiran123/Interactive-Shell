#include "cd_command.h"

static void changeDirectory(const std::string& directory);

static void changeToHome();

static void changeToOld();

static void changeToParent();

static void changeToRoot();

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
	handleArgument();
	
}

void CdCommand::handleArgument() {
	static std::unordered_map<std::string, std::function<void()>> specialStringsToFunctions = {
		{"~", &changeToHome},
		{"-", &changeToOld},
		{"..", &changeToParent},
		{"/", &changeToRoot}
	};
	if (arguments.empty()){
		changeToHome();
	}
	else if (specialStringsToFunctions.find(arguments[FIRST_INDEX]) != specialStringsToFunctions.end()) {
		specialStringsToFunctions[arguments[FIRST_INDEX]]();
	}
	else {
		std::filesystem::path path = arguments[FIRST_INDEX];
		if (!std::filesystem::exists(path)) {
			std::filesystem::path pwd = EnvVars::getVar("PWD");
			if (std::filesystem::exists(pwd / path)) {
				path = pwd / path;
			}
			else {
				writeErrorMessage("cd: " + path.string() + ": No such file or directory");
				return;
			}
		}
		if (!std::filesystem::is_directory(path)) {
			writeErrorMessage("cd: " + path.string() + ": Not a directory");
			return;
		}
		changeDirectory(path.string());
	}
}

void CdCommand::errorChecking() {
	if (!areFlagsValid()) {
		throw std::runtime_error("cd: invalid option -- '" + flags + "'");
	}
	if (arguments.size() > 1) {
		throw std::runtime_error("cd: too many arguments");
	}
}

static void changeDirectory(const std::string& directory) {
	EnvVars::setVar("OLDPWD", EnvVars::getVar("PWD"));
	EnvVars::setVar("PWD", directory);
}

static void changeToHome() {
	changeDirectory(EnvVars::getVar("HOME"));
}

static void changeToOld() {
	changeDirectory(EnvVars::getVar("OLDPWD"));
}

static void changeToParent() {
	std::filesystem::path pwd = EnvVars::getVar("PWD");
	changeDirectory(pwd.parent_path().string());
}

static void changeToRoot() {
	std::filesystem::path pwd = EnvVars::getVar("PWD");
	changeDirectory(pwd.root_path().string());
}