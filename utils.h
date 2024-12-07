#pragma once

#include <vector>
#include <string>
#include <sstream>

struct Message_s {
	bool doesExist{false};
	std::string message{};

	void initialize();
};

std::vector<std::string> split(const std::string& str, char delimiter);

