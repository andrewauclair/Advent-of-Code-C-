#pragma once

#include <fstream>
#include <vector>
#include <string>

std::fstream open_input_file(int year, int day);

std::vector<std::string> split_string(const std::string& str, char delim);

inline constexpr int a = 0;
inline const int b = 0;

constexpr int c = 0;
const int d = 0;

