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
