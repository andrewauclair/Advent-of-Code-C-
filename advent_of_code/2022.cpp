#include "2022.h"

#include "utils.h"

#include <vector>
#include <numeric>
#include <algorithm>

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

bool _2022_1::part1()
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

bool _2022_1::part2()
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