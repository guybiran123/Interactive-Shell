#pragma once

#include "command.h"

class EchoCommand : public Command {
public:
	void execute() override {
		for (const std::string& str : arguments) {
			output += str + " ";
		}
	}
};