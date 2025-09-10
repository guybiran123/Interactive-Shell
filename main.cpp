#include <iostream>
#include <string>
#include "cli_command.h"
#include "env_vars.h"

int main()
{
    EnvVars::initialize();
    CliCommand cli;
    std::string cliString;
    while (true) {
        std::cout << "\033[32m" + EnvVars::getVar("PWD") + "$ \033[0m";
        std::getline(std::cin, cliString);
        if (cliString == "exit") {
            break;
        }
        if (cliString == "") {
            continue;
        }
        cli.execute(cliString);
    }
    return 0;
}