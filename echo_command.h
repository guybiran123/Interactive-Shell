#pragma once

#include "command.h"

class EchoCommand : public Command {
public:
	void execute() override;

	bool errorChecking() override;
};