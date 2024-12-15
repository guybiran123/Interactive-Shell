#include "cat_command.h"

CatCommand::CatCommand(const std::string& flags, const std::vector<std::string>& arguments) :
	Command(flags, arguments, CAT_VALID_FLAGS) {}

void CatCommand::execute() {
	try {
		errorChecking();
	}
	catch (const std::runtime_error& exception) {
		error.doesExist = true;
		error.message = exception.what();
		return;
	}
	
	std::unique_ptr<FileReader> file_ptr;
	for (const std::string& arg : arguments) {
		try {
			file_ptr = std::make_unique<FileReader>(arg);
		}
		catch (const std::runtime_error& exception) {
			try {
				std::string j = EnvVars::getVar("PWD");
				file_ptr = std::make_unique<FileReader>(EnvVars::getVar("PWD") + "\\" + arg);
			}
			catch(const std::runtime_error& exception2){
				error.doesExist = true;
				error.message = exception.what();
				return;
			}
		}
		std::string fileContent = file_ptr->read();
		makeFlagsChanges(fileContent);
		output.doesExist = true;
		output.message += fileContent;
	}
}

void CatCommand::errorChecking() {
	if (!areFlagsValid()) {
		throw std::runtime_error("echo: invalid option -- '" + flags + "'");
	}
	if (arguments.empty()) {
		throw std::runtime_error("cat: missing file operand");
	}
}

void CatCommand::makeFlagsChanges(std::string& fileContent) {

}