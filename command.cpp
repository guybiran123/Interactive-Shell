#include "command.h"

Command::Command(const std::string& flags,
	const std::vector<std::string>& arguments,
	const std::string_view& validFlags) :
	flags{ flags },
	arguments{ arguments },
	validFlags{ validFlags }
{
	output.initialize();
	error.initialize();
}

bool Command::areFlagsValid() {
	for (char f : flags) {
		if (std::find(validFlags.begin(), validFlags.end(), f) == validFlags.end()) {
			return false;
		}
	}
	return true;
}

bool Command::inFlags(char flag) {
	return std::find(flags.begin(), flags.end(), flag) != flags.end();
}

Message_s Command::getOutput() const {
	return output;
}

Message_s Command::getError() const {
	return error;
}