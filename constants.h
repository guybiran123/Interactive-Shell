#pragma once

#include <array>
#include <string_view>
#include <filesystem>

inline std::string HOME_DIRECTORY = std::filesystem::current_path().string();

inline constexpr std::array<std::string_view, 2> OUTPUT_REDIRECTION_SYMBOLS = { ">", "1>" };
inline constexpr std::string_view ERROR_REDIRECTION_SYMBOL = "2>";
inline constexpr char FLAGS_SYMBOL = '-';

inline constexpr int FIRST_INDEX = 0;
inline constexpr int SECOND_INDEX = 1;

inline constexpr std::string_view ECHO_VALID_FLAGS = "";
inline constexpr std::string_view CAT_VALID_FLAGS = "nEs";
inline constexpr std::string_view CD_VALID_FLAGS = "";
inline constexpr std::string_view LS_VALID_FLAGS = "lahRtr";
inline constexpr std::string_view HELP_VALID_FLAGS = "";
