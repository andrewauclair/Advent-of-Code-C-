#include "2017.h"
#include "utils.h"

bool aoc_2017_1::part1()
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

bool aoc_2017_1::part2()
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

bool aoc_2017_2::part1()
{
	auto file = open_input_file(2017, 2);

	const std::vector<std::string> lines = read_lines(file);

	int checksum = 0;

	for (const std::string& line : lines)
	{
		const std::vector<int> values = read_as<int>(line);

		int lowest = std::numeric_limits<int>::max();
		int highest = std::numeric_limits<int>::min();

		for (int value : values)
		{
			lowest = std::min(lowest, value);
			highest = std::max(highest, value);
		}

		checksum += highest - lowest;
	}

	// 47623
	return checksum == 47623;
}

bool aoc_2017_2::part2()
{
	auto file = open_input_file(2017, 2);

	const std::vector<std::string> lines = read_lines(file);

	int total = 0;

	for (const std::string& line : lines)
	{
		const std::vector<int> values = read_as<int>(line);

		for (int i = 0; i < values.size(); i++)
		{
			for (int j = i + 1; j < values.size(); j++)
			{
				int min = std::min(values[i], values[j]);
				int max = std::max(values[i], values[j]);

				if (max % min == 0)
				{
					total += max / min;
				}
			}
		}
	}
	
	return total == 312;
}
