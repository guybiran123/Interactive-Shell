#pragma once

#include <unordered_map>
#include <string>
#include <string_view>

#include "command.h"

class HelpCommand : public Command {
private:
	static const std::unordered_map<std::string, std::string_view> COMMAND_TO_HELP_MESSAGE;

public:
	HelpCommand(const std::string& flags, const std::vector<std::string>& arguments);

	void execute() override;

	void errorChecking() override;

	void writeHelpMessage();
};