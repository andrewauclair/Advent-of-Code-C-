#pragma once

#include <fstream>
#include <vector>
#include <string>

std::fstream open_input_file(int year, int day);

std::vector<std::string> split_string(const std::string& str, char delim);

