#pragma once

#include <string>
#include <map>

class EnvVars {
private:
	static std::map<std::string, std::string> env;

public:
	static void initialize() {
		env["HOME"] = "";
		env["PATH"] = "";
		env["PWD"] = "";
		env["OLDPWD"] = "";
	}
	static void setVar(const std::string& key, const std::string& value) {
		env[key] = value;
	}
	static std::string getVar(const std::string& key) {
		return env.count(key) ? env[key] : "";
	}
};
