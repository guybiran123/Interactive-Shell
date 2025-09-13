#include "env_vars.h"

std::map<std::string, std::string> EnvVars::env;

void EnvVars::initialize() {
	env["HOME"] = HOME_DIRECTORY;
	env["PATH"] = "";
	env["PWD"] = env["HOME"];
	env["OLDPWD"] = env["HOME"];
}

void EnvVars::setVar(const std::string& key, const std::string& value) {
	env[key] = value;
}

std::string EnvVars::getVar(const std::string& key) {
	if (env.count(key)) {
		return env[key];
	}
	return "";
}