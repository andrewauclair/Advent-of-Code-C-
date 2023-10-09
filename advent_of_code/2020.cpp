#include "2020.h"
#include "utils.h"
#include <istream>
#include <algorithm>

bool aoc_2020_1::part1()
{
	auto file = open_input_file(2020, 1);

	std::vector<int> expenses = read_as<int>(file);;
	
	std::sort(expenses.rbegin(), expenses.rend());

	for (int i = 0; i < expenses.size(); i++)
	{
		for (int j = i + 1; j < expenses.size(); j++)
		{
			const int sum = expenses[i] + expenses[j];

			if (sum == 2020)
			{
				return (expenses[i] * expenses[j]) == 197451;
			}
		}
	}
	return false;
}

bool aoc_2020_1::part2()
{
	auto file = open_input_file(2020, 1);

	std::vector<int> expenses = read_as<int>(file);
	
	std::sort(expenses.rbegin(), expenses.rend());

	for (int i = 0; i < expenses.size(); i++)
	{
		for (int j = i + 1; j < expenses.size(); j++)
		{
			for (int k = j + 1; k < expenses.size(); k++)
			{
				const int sum = expenses[i] + expenses[j] + expenses[k];

				if (sum == 2020)
				{
					return (expenses[i] * expenses[j] * expenses[k]) == 138233720;
				}
			}
		}
	}
	return false;
}

bool aoc_2020_2::part1()
{
	auto file = open_input_file(2020, 2);

	const std::vector<std::string> lines = read_lines(file);

	int valid_passwords = 0;

	for (const std::string& line : lines)
	{
		const std::string requirements = line.substr(0, line.find(':'));
		const std::string password = line.substr(line.find(':') + 1);

		int min;
		int max;
		char ch;

		std::sscanf(line.c_str(), "%d-%d %c", &min, &max, &ch);

		const auto count = std::count(password.begin(), password.end(), ch);

		if (count >= min && count <= max)
		{
			valid_passwords++;
		}
	}

	return valid_passwords == 620;
}

bool aoc_2020_2::part2()
{
	auto file = open_input_file(2020, 2);

	const std::vector<std::string> lines = read_lines(file);

	int valid_passwords = 0;

	for (const std::string& line : lines)
	{
		const std::string requirements = line.substr(0, line.find(':'));
		const std::string password = line.substr(line.find(':') + 2);

		int min;
		int max;
		char ch;

		std::sscanf(line.c_str(), "%d-%d %c", &min, &max, &ch);

		const bool first = password[min - 1] == ch;
		const bool second = password[max - 1] == ch;

		if ((first && !second) || (!first && second))
		{
			valid_passwords++;
		}
	}

	return valid_passwords == 727;
}
