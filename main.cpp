#include <iostream>
#include <string>
#include "cli_command.h"

int main()
{
    CliCommand cli;
    std::string cli_string;
    while (true) {
        std::cout << ">> ";
        std::getline(std::cin, cli_string);
        cli.execute(cli_string);
    }
    return 0;
}