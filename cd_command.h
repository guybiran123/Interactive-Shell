#pragma once

#include <filesystem>
#include "command.h"
#include "env_vars.h"

class CdCommand : public Command {
	CdCommand(const std::string& flags, const std::vector<std::string>& arguments);

	void execute() override;

	void errorChecking() override;

	void changeDirectory(const std::string& directory);
};