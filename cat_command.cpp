#include "cat_command.h"

CatCommand::CatCommand(const std::string& flags, const std::vector<std::string>& arguments) :
	Command(flags, arguments, CAT_VALID_FLAGS) {}

void CatCommand::execute() {
	try {
		errorChecking();
	}
	catch (const std::runtime_error& exception) {
		writeErrorMessage(exception.what());
		return;
	}
	
	std::unique_ptr<FileReader> file_ptr;
	for (const std::string& arg : arguments) {
		try {
			file_ptr = std::make_unique<FileReader>(arg);
		}
		catch (const std::runtime_error& exception) {
			try {
				file_ptr = std::make_unique<FileReader>(EnvVars::getVar("PWD") + "\\" + arg);
			}
			catch(const std::runtime_error& exception2){
				writeErrorMessage(exception.what());
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
		throw std::runtime_error("cat: invalid option -- '" + flags + "'");
	}
	if (arguments.empty()) {
		throw std::runtime_error("cat: missing file operand");
	}
}

void CatCommand::makeFlagsChanges(std::string& fileContent) {
	if (inFlags('s')) {
		squeezeBlank(fileContent);
	}
	if (inFlags('n')) {
		numberLines(fileContent);
	}
	if (inFlags('E')) {
		showEnds(fileContent);
	}
}

void CatCommand::numberLines(std::string& fileContent) {
	std::istringstream stream(fileContent);
	std::string line;
	fileContent = "";
	int lineNumber = 1;
	bool firstLoop = true;
	while (std::getline(stream, line)) {
		if (!firstLoop) {
			fileContent += '\n';
		}
		fileContent += std::to_string(lineNumber) + "  " + line;
		++lineNumber;
		firstLoop = false;
	}	
}

void CatCommand::showEnds(std::string& fileContent) {
	std::istringstream stream(fileContent);
	std::string line;
	fileContent = "";;
	bool firstLoop = true;
	while (std::getline(stream, line)) {
		if (!firstLoop) {
			fileContent += '\n';
		}
		fileContent += line + '$';
		firstLoop = false;
	}
}

void CatCommand::squeezeBlank(std::string& fileContent) {
	std::istringstream stream(fileContent);
	std::string line;
	fileContent = "";;
	bool firstLoop = true;
	while (std::getline(stream, line)) {
		if (!firstLoop && line != "") {
			fileContent += '\n';
		}
		fileContent += line;
		firstLoop = false;
	}
}