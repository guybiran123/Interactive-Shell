#include "env_vars.h"

std::map<std::string, std::string> EnvVars::env;

void EnvVars::initialize() {
	env["HOME"] = "";
	env["PATH"] = "";
	env["PWD"] = "";
	env["OLDPWD"] = "";
}

void EnvVars::setVar(const std::string& key, const std::string& value) {
	env[key] = value;
}

std::string EnvVars::getVar(const std::string& key) {
	return env.count(key) ? env[key] : "";
}