#pragma once

#include <memory>
#include <sstream>
#include "command.h"
#include "file_reader.h"
#include "env_vars.h"

class CatCommand : public Command {
public:
	CatCommand(const std::string& flags, const std::vector<std::string>& arguments);

	void execute() override;

	void errorChecking() override;

	void makeFlagsChanges(std::string& fileContent);

	void numberLines(std::string& fileContent);

	void showEnds(std::string& fileContent);

	void squeezeBlank(std::string& fileContent);
};