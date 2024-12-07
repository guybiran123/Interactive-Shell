#pragma once

#include "command.h"

class EchoCommand : public Command {
public:
	EchoCommand(const std::string& flags, const std::vector<std::string>& arguments);

	void execute() override;

	bool errorChecking() override;
};