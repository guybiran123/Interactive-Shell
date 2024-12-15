#pragma once

#include <memory>
#include "command.h"
#include "file_reader.h"
#include "env_vars.h"

class CatCommand : public Command {
public:
	CatCommand(const std::string& flags, const std::vector<std::string>& arguments);

	void execute() override;

	void errorChecking() override;

	void makeFlagsChanges(std::string& fileContent);
};