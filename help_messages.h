#pragma once
#include <string_view>

// General help
inline constexpr std::string_view DEFAULT_HELP_MESSAGE = R"(
help: available commands:
  echo    - write arguments to standard output
  cat     - concatenate files and print on the standard output
  cd      - change the shell working directory
  ls      - list directory contents
  help    - display information about builtin commands

Use 'help <command>' to get more info about a specific command.

Output redirection:
  > file      Redirect standard output (stdout) to a file
  1> file     Same as > file (explicitly redirects stdout)
  2> file     Redirect standard error (stderr) to a file

General usage:
  <command> [flags] [arguments] [redirection] [file]

Where:
  <command>     The builtin command to run (echo, cat, cd, ls, help)
  [flags]       Optional flags that modify the command’s behavior (e.g., -la, -E, -n)
  [arguments]   Optional arguments passed to the command
  [redirection] Optional output or error redirection operator (> 1> 2>)
  [file]        Optional file name used with redirection

)";


// Per-command help
inline constexpr std::string_view ECHO_HELP_MESSAGE = R"(
echo: echo [arguments...]
  Prints arguments to standard output separated by spaces.
)";

inline constexpr std::string_view CAT_HELP_MESSAGE = R"(
cat: cat [FLAGS]... [FILE]...
  Concatenate FILE(s) to standard output.

FLAGS:
  -n    number all output lines
  -E    display $ at end of each line
  -s    suppress repeated empty output lines

Examples:
  cat file.txt         Print contents of file.txt
  cat -n file.txt      Print contents with line numbers
  cat -E file.txt      Show end-of-line markers
  cat -s file.txt      Collapse multiple blank lines into one
)";


inline constexpr std::string_view CD_HELP_MESSAGE = R"(
cd: cd [directory]
  Change the current working directory.

Arguments:
  directory    The target directory to switch to. You can use:
                 ~   Home directory
                 -   Previous directory
                 ..  Parent directory
                 /   Root directory
               Or any valid path relative or absolute.

Examples:
  cd /home/user       Change to /home/user
  cd ..               Go up one directory
  cd ~                Go to your home directory
  cd -                Go to the previous directory
)";


inline constexpr std::string_view LS_HELP_MESSAGE = R"(
ls: ls [flags] [directory...]
  List information about files and directories.

Flags:
  -l    Use a long listing format
  -a    Include hidden files (those starting with .)
  -h    Human-readable sizes (e.g., 1K, 234M)
  -R    Recursively list subdirectories
  -t    Sort by modification time, newest first
  -r    Reverse the order while sorting

Arguments:
  directory...  Optional directories to list; if none are provided, lists the current directory.

Examples:
  ls               List files in the current directory
  ls -l            Long format listing
  ls -a            Include hidden files
  ls -lhR          Long format, human-readable sizes, recursively
  ls -ltr          List sorted by modification time in reverse
)";


inline constexpr std::string_view HELP_HELP_MESSAGE = R"(
help: help [command]
  Display information about builtin commands.

Arguments:
  command    Optional. The name of the command you want help for.
             If omitted, displays general help information.

Examples:
  help           Show general help with all commands
  help echo      Show detailed help for the 'echo' command
  help ls        Show detailed help for the 'ls' command
)";

