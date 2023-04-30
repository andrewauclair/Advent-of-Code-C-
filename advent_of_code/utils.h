#pragma once

#include <fstream>
#include <vector>
#include <string>

std::fstream open_input_file(int year, int day);

std::vector<std::string> split_string(const std::string& str, char delimiter);

template<typename T>
std::vector<T> read_as(std::fstream& in)
{
	std::vector<T> values;
	std::copy(std::istream_iterator<int>(in), std::istream_iterator<int>(), std::back_inserter(values));

	return values;
}
