#pragma once

#include <fstream>
#include <vector>
#include <string>
#include <sstream>

std::fstream open_input_file(int year, int day);

inline std::vector<std::string> read_lines(std::fstream& in)
{
	std::vector<std::string> lines;
	std::string line;

	while (std::getline(in, line))
	{
		lines.push_back(line);
	}
	return lines;
}

template<typename T>
std::vector<T> read_as(std::fstream& in)
{
	std::vector<T> values;
	std::copy(std::istream_iterator<int>(in), std::istream_iterator<int>(), std::back_inserter(values));

	return values;
}

template<typename T = std::string>
std::vector<T> split_string(const std::string& str, char delim)
{
	std::vector<T> strs;

	std::stringstream ss(str);

	std::string item;

	while (std::getline(ss, item, delim))
	{
		strs.push_back(item);
	}

	return strs;
}
