#include "2017.h"
#include "utils.h"

bool _2017_1::part1()
{
	auto file = open_input_file(2017, 1);

	std::string line;

	int sum = 0;

	while (std::getline(file, line))
	{
		for (auto it = line.begin(); it != line.end(); ++it)
		{
			const bool at_end = std::next(it) == line.end();

			if (!at_end && *it == *std::next(it))
			{
				sum += *it - '0';
			}
			else if (at_end)
			{
				sum += *it - '0';
			}
		}
	}

	return sum == 1223;
}

bool _2017_1::part2()
{
	auto file = open_input_file(2017, 1);

	std::string line;

	int sum = 0;

	while (std::getline(file, line))
	{
		for (auto it = line.begin(); it != line.end(); ++it)
		{
			const auto next_pos = [&it, &line]() {
				const std::size_t steps = line.size() / 2;

				const auto current_pos = std::distance(line.begin(), it);
				const auto new_pos = (current_pos + steps) % line.size();
				
				return line.begin() + new_pos;
			};

			if (*it == *next_pos())
			{
				sum += *it - '0';
			}
		}
	}

	return sum == 1284;
}
