#include "2015.h"
#include "utils.h"

#include <iostream>

bool _2015_1::part1()
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

bool _2015_1::part2()
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
