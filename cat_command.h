#pragma once

#include "command.h"

class CatCommand : public Command {
public:
	CatCommand(const std::string& flags, const std::vector<std::string>& arguments);

	void execute() override;

	void errorChecking() override;
};