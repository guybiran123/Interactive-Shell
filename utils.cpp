#include "utils.h"

void Message_s::initialize() {
    doesExist = false;
    message = "";
}

std::vector<std::string> split(const std::string& str, char delimiter) {
    std::vector<std::string> tokens; // Stores the result (split substrings)
    std::stringstream ss(str);       // Wraps the input string into a stringstream object
    std::string token;               // Temporary storage for each substring

    while (std::getline(ss, token, delimiter)) {
		if (token != "") {
			tokens.push_back(token); // Add each substring to the vector
		}
    }

    return tokens;                   // Return the resulting substrings
}

std::string substrIndexToChar(std::string str, int startIndex, char character, bool includeChar) {
	str = str.substr(startIndex);
	int charIndex = str.find_first_of(character);
	if (charIndex == std::string::npos) {
		return str;
	}
	if (includeChar) {
		return str.substr(FIRST_INDEX, charIndex + 1);
	}
	return str.substr(FIRST_INDEX, charIndex);
}

std::string trimLeadinSpaces(std::string str) {
	int startIndex = str.find_first_not_of(' ');
	if (startIndex == std::string::npos) {
		return "";
	}
	return str.substr(startIndex);
}

std::string trimTrailingSpaces(std::string str) {
	std::reverse(str.begin(), str.end());
	str = trimLeadinSpaces(str);
	std::reverse(str.begin(), str.end());
	return str;
}