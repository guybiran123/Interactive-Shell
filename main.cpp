#include <iostream>
#include <string>
#include "cli_command.h"
#include "env_vars.h"

int main()
{
    EnvVars::initialize();
    CliCommand cli;
    std::string cli_string;
    while (true) {
        std::cout << "\033[32m" + EnvVars::getVar("PWD") + "$ \033[0m";
        std::getline(std::cin, cli_string);
        cli.execute(cli_string);
    }
    return 0;
}