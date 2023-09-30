#include "utils.h"
#include <format>
#include <iostream>
#include <sstream>

std::fstream open_input_file(int year, int day)
{
	const std::string file = std::format("../Input/{}/day_{}.txt", year, day);

	auto input = std::fstream(file, std::ios_base::in);

	if (!input.is_open())
	{
		std::cerr << "Could not open " << file << '\n';
		throw std::runtime_error("failed to read file: " + file);
	}

	return input;
}
