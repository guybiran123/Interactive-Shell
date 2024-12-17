#pragma once

#include <filesystem>
#include <unordered_map>
#include <functional>
#include "command.h"
#include "env_vars.h"

class CdCommand : public Command {
public:
	CdCommand(const std::string& flags, const std::vector<std::string>& arguments);

	void execute() override;

	void handleArgument();

	void errorChecking() override;
};