#pragma once

#include <string>

struct Redirection_s {
	bool toRedirect{ false };
	std::string fileName{ };
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

};