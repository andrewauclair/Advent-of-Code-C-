#include "utils.h"
#include <iostream>
#include <vector>
#include <map>
#include <format>

#include "2015.h"

void run_2016_1()
{
	auto file = open_input_file(2016, 1);

	std::string input;
	std::getline(file, input);

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

	std::vector<instruction> instructions;

	std::vector<std::string> input_values = split_string(input, ',');

	for (auto&& str : input_values)
	{
		int count = str.at(0) == ' ' ? std::stoi(str.substr(2)) : std::stoi(str.substr(1));
		instructions.emplace_back((str.at(0) == ' ' ? str.at(1) == 'L' : str.at(0) == 'L') ? direction::left : direction::right, count);
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

	std::cout << "2016/1/1: " << (std::abs(current_position.y) + std::abs(current_position.x)) << '\n';
}

void run_2016_2()
{
	auto file = open_input_file(2016, 1);

	std::string input;
	std::getline(file, input);

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

	std::vector<instruction> instructions;

	std::vector<std::string> input_values = split_string(input, ',');

	for (auto&& str : input_values)
	{
		int count = str.at(0) == ' ' ? std::stoi(str.substr(2)) : std::stoi(str.substr(1));
		instructions.emplace_back((str.at(0) == ' ' ? str.at(1) == 'L' : str.at(0) == 'L') ? direction::left : direction::right, count);
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
				current_position.x -= 1;// instruction.count;
				break;
			case direction::right:
				current_position.x += 1;//instruction.count;
				break;
			case direction::up:
				current_position.y -= 1;//instruction.count;
				break;
			case direction::down:
				current_position.y += 1;//instruction.count;
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

	std::cout << "2016/1/2: " << (std::abs(current_position.y) + std::abs(current_position.x)) << '\n';
}





int main()
{
	for (auto&& problem : days)
	{
		std::cout << std::format("{}/{}/1: {}", problem.year, problem.day, problem.obj->part1() ? "pass" : "fail") << '\n';
		std::cout << std::format("{}/{}/2: {}", problem.year, problem.day, problem.obj->part2() ? "pass" : "fail") << '\n';
	}
}
