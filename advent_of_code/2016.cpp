#include "2016.h"
#include "utils.h"

#include <iostream>
#include <map>
#include <array>

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

bool aoc_2016_2::part1()
{
	auto file = open_input_file(2016, 2);

	const std::vector<std::string> lines = read_lines(file);

	const std::array<std::array<int, 3>, 3> buttons{ { 
		{1, 2, 3}, 
		{4, 5, 6}, 
		{7, 8, 9} 
	} };

	int x = 1;
	int y = 1;

	std::vector<int> button_presses;

	for (std::string_view instruction : lines)
	{
		for (char ch : instruction)
		{
			switch (ch)
			{
			case 'U': // up
				if (y > 0) --y;
				break;
			case 'D': // down
				if (y < 2) ++y;
				break;
			case 'L': // left
				if (x > 0) --x;
				break;
			case 'R': // right
				if (x < 2) ++x;
				break;
			}
		}
		button_presses.push_back(buttons.at(y).at(x));
	}

	// 61529
	return button_presses == std::vector<int>{6, 1, 5, 2, 9};
}

bool aoc_2016_2::part2()
{
	auto file = open_input_file(2016, 2);

	const std::vector<std::string> lines = read_lines(file);

	const std::array<std::array<char, 5>, 5> buttons{ {
		{ ' ', ' ', '1', ' ', ' ' },
		{ ' ', '2', '3', '4', ' ' },
		{ '5', '6', '7', '8', '9' },
		{ ' ', 'A', 'B', 'C', ' ' },
		{ ' ', ' ', 'D', ' ', ' ' }
	} };

	int x = 0;
	int y = 2;

	std::string buttons_pressed;

	for (std::string_view instruction : lines)
	{
		for (char ch : instruction)
		{
			switch (ch)
			{
			case 'U': // up
				if (y > 0 && buttons.at(y - 1).at(x) != ' ') --y;
				break;
			case 'D': // down
				if (y < 4 && buttons.at(y + 1).at(x) != ' ') ++y;
				break;
			case 'L': // left
				if (x > 0 && buttons.at(y).at(x - 1) != ' ') --x;
				break;
			case 'R': // right
				if (x < 4 && buttons.at(y).at(x + 1) != ' ') ++x;
				break;
			}
		}

		buttons_pressed += buttons.at(y).at(x);
	}
	
	return buttons_pressed == "C2C28";
}

bool aoc_2016_3::part1()
{
	auto file = open_input_file(2016, 3);

	const std::vector<int> triangles = read_as<int>(file);

	int valid_triangles = 0;

	for (int i = 0; i < triangles.size(); i += 3)
	{
		const int a = triangles[i];
		const int b = triangles[i + 1];
		const int c = triangles[i + 2];

		if ((a + b > c) && (b + c > a) && (c + a > b))
		{
			++valid_triangles;
		}
	}

	return valid_triangles == 917;
}

bool aoc_2016_3::part2()
{
	auto file = open_input_file(2016, 3);

	const std::vector<int> triangles = read_as<int>(file);

	auto it = triangles.begin();

	int valid_triangles = 0;

	for (int i = 0; i < triangles.size(); i += 9)
	{
		const auto count = [&](int a, int b, int c) {
			if ((a + b > c) && (b + c > a) && (c + a > b))
			{
				++valid_triangles;
			}
		};

		count(triangles[i], triangles[i + 3], triangles[i + 6]);
		count(triangles[i + 1], triangles[i + 4], triangles[i + 7]);
		count(triangles[i + 2], triangles[i + 5], triangles[i + 8]);
	}

	return valid_triangles == 1649;
}
