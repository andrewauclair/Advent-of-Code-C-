#include "2022.h"

#include "utils.h"

#include <vector>
#include <numeric>
#include <algorithm>
#include <map>

namespace
{
	struct elf
	{
		std::vector<int> calories;
	};

	std::vector<elf> parse_input()
	{
		auto file = open_input_file(2022, 1);

		std::vector<elf> elves;

		std::string line;
		elf current_elf;

		while (std::getline(file, line))
		{
			if (line.empty())
			{
				elves.emplace_back(current_elf);

				// new elf
				current_elf = {};
				continue;
			}
			current_elf.calories.push_back(std::stoi(line));
		}

		return elves;
	}
}

bool aoc_2022_1::part1()
{
	std::vector<elf> elves = parse_input();

	const auto calorie_total = [](const elf& elf) -> int {
		return std::reduce(elf.calories.begin(), elf.calories.end());
	};

	std::vector<int> calories;
	
	std::transform(elves.begin(), elves.end(), std::back_inserter(calories), calorie_total);

	const int max = *std::max_element(calories.begin(), calories.end());

	return max == 71124;
}

bool aoc_2022_1::part2()
{
	std::vector<elf> elves = parse_input();

	const auto calorie_total = [](const elf& elf) -> int {
		return std::reduce(elf.calories.begin(), elf.calories.end());
	};

	std::vector<int> calories;

	std::transform(elves.begin(), elves.end(), std::back_inserter(calories), calorie_total);

	std::sort(calories.rbegin(), calories.rend());

	const int total = calories[0] + calories[1] + calories[2];

	return total == 204639;
}

namespace
{
	enum class type : int
	{
		rock, paper, scissors
	};

	enum result : int
	{
		win, lose, draw
	};
}

bool aoc_2022_2::part1()
{
	const std::map<char, type> opponent_types = {
					{ 'A', type::rock },
					{ 'B', type::paper },
					{ 'C', type::scissors }
	};
	const std::map<char, type> my_types = {
		{ 'X', type::rock },
		{ 'Y', type::paper },
		{ 'Z', type::scissors }
	};

	auto file = open_input_file(2022, 2);

	int opponent_score = 0;
	int my_score = 0;

	char opponent_char;
	char my_char;

	while (file >> opponent_char >> my_char)
	{
		const type opponent = opponent_types.find(opponent_char)->second;
		const type mine = my_types.find(my_char)->second;

		opponent_score += static_cast<int>(opponent) + 1;
		my_score += static_cast<int>(mine) + 1;

		if ((opponent == type::rock && mine == type::scissors) ||
			(opponent == type::paper && mine == type::rock) ||
			(opponent == type::scissors && mine == type::paper))
		{
			opponent_score += 6;
		}
		else if (opponent == mine)
		{
			opponent_score += 3;
			my_score += 3;
		}
		else
		{
			my_score += 6;
		}
	}
	
	return my_score == 11150;
}

bool aoc_2022_2::part2() 
{
	std::string line;
	const std::map<char, type> opponent_types = {
		{ 'A', type::rock },
		{ 'B', type::paper },
		{ 'C', type::scissors }
	};
	const std::map<char, result> results = {
		{ 'X', result::lose },
		{ 'Y', result::draw },
		{ 'Z', result::win }
	};

	auto file = open_input_file(2022, 2);

	int opponent_score = 0;
	int my_score = 0;

	char opponent_char;
	char my_char;

	while (file >> opponent_char >> my_char)
	{
		const type opponent = opponent_types.find(opponent_char)->second;
		const result my_result = results.find(my_char)->second;

		type mine = type::rock;

		switch (opponent)
		{
		case type::rock:
			switch (my_result)
			{
			case result::lose: mine = type::scissors; break;
			case result::draw: mine = type::rock; break;
			case result::win: mine = type::paper; break;
			}
			break;
		case type::paper:
			switch (my_result)
			{
			case result::lose: mine = type::rock; break;
			case result::draw: mine = type::paper; break;
			case result::win: mine = type::scissors; break;
			}
			break;
		case type::scissors:
			switch (my_result)
			{
			case result::lose: mine = type::paper; break;
			case result::draw: mine = type::scissors; break;
			case result::win: mine = type::rock; break;
			}
			break;
		}

		opponent_score += static_cast<int>(opponent) + 1;
		my_score += static_cast<int>(mine) + 1;

		if ((opponent == type::rock && mine == type::scissors) ||
			(opponent == type::paper && mine == type::rock) ||
			(opponent == type::scissors && mine == type::paper))
		{
			opponent_score += 6;
		}
		else if (opponent == mine)
		{
			opponent_score += 3;
			my_score += 3;
		}
		else
		{
			my_score += 6;
		}
	}
	
	return my_score == 8295;
}
