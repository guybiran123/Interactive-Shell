#pragma once

#include <array>
#include <string_view>

//inline constexpr std::array<std::string_view, 2> SPECIAL_CHARACTERS = { ">", "`" };
inline constexpr std::array<std::string_view, 2> OUTPUT_REDIRECTION_SYMBOLS = { ">", "1>" };
inline constexpr std::string_view ERROR_REDIRECTION_SYMBOL = "2>";
inline constexpr char FLAGS_SYMBOL = '-';
inline constexpr int FIRST_INDEX = 0;
inline constexpr int SECOND_INDEX = 1;

