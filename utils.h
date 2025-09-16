#pragma once

#include <vector>
#include <filesystem>
#include <string>
#include <sstream>
#include <algorithm>
#include "constants.h"
#include "env_vars.h"

struct Message_s {
	bool doesExist{false};
	std::string message{};

	void initialize();
};

std::vector<std::string> split(const std::string& str, char delimiter);

std::string substrIndexToChar(std::string str, int startIndex, char character, bool includeChar);

std::string trimLeadinSpaces(std::string str);

std::string trimTrailingSpaces(std::string str);

std::filesystem::path resolvePath(const std::string& userInput);
