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
        tokens.push_back(token);     // Add each substring to the vector
    }

    return tokens;                   // Return the resulting substrings
}