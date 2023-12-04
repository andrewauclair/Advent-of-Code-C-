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
std::vector<T> read_as(std::istream& in)
{
	std::vector<T> values;
	std::copy(std::istream_iterator<T>(in), std::istream_iterator<T>(), std::back_inserter(values));

	return values;
}

template<typename T>
std::vector<T> read_as(std::string in)
{
	auto input = std::istringstream(in);

	std::vector<T> values;

	T value;

	while (input >> value)
	{
		values.push_back(value);
	}
	
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

inline std::vector<std::string> split_by_whitespace(const std::string& str)
{
	std::vector<std::string> strs;

	std::stringstream ss(str);

	std::string item;

	while (ss >> item)
	{
		strs.push_back(item);
	}

	return strs;
}
#include <algorithm> 
#include <cctype>
#include <locale>

// trim from start (in place)
static inline void ltrim(std::string& s) {
	s.erase(s.begin(), std::find_if(s.begin(), s.end(), [](unsigned char ch) {
		return !std::isspace(ch);
		}));
}

// trim from end (in place)
static inline void rtrim(std::string& s) {
	s.erase(std::find_if(s.rbegin(), s.rend(), [](unsigned char ch) {
		return !std::isspace(ch);
		}).base(), s.end());
}

// trim from both ends (in place)
static inline void trim(std::string& s) {
	rtrim(s);
	ltrim(s);
}