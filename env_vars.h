#pragma once

#include <string>
#include <map>

class EnvVars {
private:
	static std::map<std::string, std::string> env;

	EnvVars() = delete;

public:
	static void initialize();

	static void setVar(const std::string& key, const std::string& value);

	static std::string getVar(const std::string& key);
};
