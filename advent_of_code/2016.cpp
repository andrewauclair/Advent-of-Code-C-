#include "2016.h"
#include "utils.h"

#include <iostream>
#include <map>

namespace
{
	enum class direction { left, right, up, down };

	struct instruction
	{
		direction direction = direction::left;
		int count = 0;
	};

	struct position
	{
		int x = 0;
		int y = 0;

		bool operator<(position b) const
		{
			return x < b.x || (x == b.x && y < b.y);
		}
	};
}

bool aoc_2016_1::part1()
{
	auto file = open_input_file(2016, 1);

	std::string input;
	std::getline(file, input);

	std::vector<instruction> instructions;

	std::vector<std::string> input_values = split_string(input, ',');

	for (auto&& str : input_values)
	{
		if (str.at(0) == ' ')
		{
			str = str.substr(1);
		}
		int count = std::stoi(str.substr(1));
		instructions.emplace_back(str.at(0) == 'L' ? direction::left : direction::right, count);
	}

	position current_position;
	direction current_direction = direction::up;

	for (instruction instruction : instructions)
	{
		if (instruction.direction == direction::left)
		{
			switch (current_direction)
			{
			case direction::left:
				current_direction = direction::down;
				break;
			case direction::right:
				current_direction = direction::up;
				break;
			case direction::up:
				current_direction = direction::left;
				break;
			case direction::down:
				current_direction = direction::right;
				break;
			}
		}
		else
		{
			switch (current_direction)
			{
			case direction::left:
				current_direction = direction::up;
				break;
			case direction::right:
				current_direction = direction::down;
				break;
			case direction::up:
				current_direction = direction::right;
				break;
			case direction::down:
				current_direction = direction::left;
				break;
			}
		}

		switch (current_direction)
		{
		case direction::left:
			current_position.x -= instruction.count;
			break;
		case direction::right:
			current_position.x += instruction.count;
			break;
		case direction::up:
			current_position.y -= instruction.count;
			break;
		case direction::down:
			current_position.y += instruction.count;
			break;
		}
	}

	const int answer = std::abs(current_position.x) + std::abs(current_position.y);

	return answer == 253;
}

bool aoc_2016_1::part2()
{
	auto file = open_input_file(2016, 1);

	std::string input;
	std::getline(file, input);

	std::vector<instruction> instructions;

	std::vector<std::string> input_values = split_string(input, ',');

	for (auto&& str : input_values)
	{
		if (str.at(0) == ' ')
		{
			str = str.substr(1);
		}
		int count = std::stoi(str.substr(1));
		instructions.emplace_back(str.at(0) == 'L' ? direction::left : direction::right, count);
	}

	position current_position;
	direction current_direction = direction::up;

	std::map<position, bool> visited_positions;
	visited_positions[current_position] = true;

	for (instruction instruction : instructions)
	{
		if (instruction.direction == direction::left)
		{
			switch (current_direction)
			{
			case direction::left:
				current_direction = direction::down;
				break;
			case direction::right:
				current_direction = direction::up;
				break;
			case direction::up:
				current_direction = direction::left;
				break;
			case direction::down:
				current_direction = direction::right;
				break;
			}
		}
		else
		{
			switch (current_direction)
			{
			case direction::left:
				current_direction = direction::up;
				break;
			case direction::right:
				current_direction = direction::down;
				break;
			case direction::up:
				current_direction = direction::right;
				break;
			case direction::down:
				current_direction = direction::left;
				break;
			}
		}

		bool done = false;

		for (int i = 0; i < instruction.count; i++)
		{
			switch (current_direction)
			{
			case direction::left:
				current_position.x -= 1;
				break;
			case direction::right:
				current_position.x += 1;
				break;
			case direction::up:
				current_position.y -= 1;
				break;
			case direction::down:
				current_position.y += 1;
				break;
			}

			if (visited_positions.find(current_position) != visited_positions.end())
			{
				done = true;
				break;
			}
			visited_positions[current_position] = true;
		}

		if (done)
		{
			break;
		}
	}

	const int answer = std::abs(current_position.x) + std::abs(current_position.y);

	return answer == 126;
}
