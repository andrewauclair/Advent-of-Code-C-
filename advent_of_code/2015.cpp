#include "2015.h"
#include "utils.h"

#include <iostream>

bool aoc_2015_1::part1()
{
	auto file = open_input_file(2015, 1);

	std::string input;
	file >> input;

	int floor = 0;
	for (char c : input)
	{
		if (c == '(') floor++;
		if (c == ')') floor--;
	}

	return floor == 280;
}

bool aoc_2015_1::part2()
{
	auto file = open_input_file(2015, 1);

	std::string input;
	file >> input;

	int floor = 0;
	for (char c : input)
	{
		if (c == '(') floor++;
		if (c == ')') floor--;
	}

	int first_pos = -1;
	int pos = 0;
	floor = 0;
	for (char c : input)
	{
		if (c == '(') floor++;
		if (c == ')') floor--;

		if (floor < 0)
		{
			first_pos = pos + 1;
			break;
		}
		pos++;
	}

	return first_pos == 1797;
}

bool aoc_2015_2::part1()
{
	auto file = open_input_file(2015, 2);

	std::string line;
	
	int total_paper = 0;

	while (std::getline(file, line))
	{
		const std::vector<std::string> values = split_string(line, 'x');

		const int length = std::stoi(values[0]);
		const int width = std::stoi(values[1]);
		const int height = std::stoi(values[2]);

		const int side_a = length * width;
		const int side_b = width * height;
		const int side_c = height * length;

		total_paper += std::min({ side_a, side_b, side_c });

		total_paper += (2 * side_a) + (2 * side_b) + (2 * side_c);
	}
	
	return total_paper == 1606483;
}

bool aoc_2015_2::part2()
{
	auto file = open_input_file(2015, 2);

	std::string line;

	int total_ribbon = 0;

	while (std::getline(file, line))
	{
		const std::vector<std::string> values = split_string(line, 'x');

		const int length = std::stoi(values[0]);
		const int width = std::stoi(values[1]);
		const int height = std::stoi(values[2]);

		const int side_a = length * width;
		const int side_b = width * height;
		const int side_c = height * length;

		const int smallest_side = std::min({ side_a, side_b, side_c });

		if (smallest_side == side_a)
		{
			total_ribbon += (2 * length) + (2 * width);
		}
		else if (smallest_side == side_b)
		{
			total_ribbon += (2 * width) + (2 * height);
		}
		else if (smallest_side == side_c)
		{
			total_ribbon += (2 * height) + (2 * length);
		}

		total_ribbon += length * width * height;
	}

	return total_ribbon == 3842356;
}