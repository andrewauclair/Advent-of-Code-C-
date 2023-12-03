#include "2023.h"

#include "utils.h"

#include <vector>
#include <numeric>
#include <algorithm>
#include <map>

namespace
{
}

bool aoc_2023_1::part1()
{
	auto file = open_input_file(2023, 1);
	auto values = read_as<std::string>(file);

	int sum = 0;

	for (auto v : values)
	{
		char first = ' ';
		char last = ' ';

		for (auto c : v) 
		{
			if (std::isdigit(c))
			{
				if (first == ' ') first = c;
				last = c;
			}
		}

		sum += ((first - 0x30) * 10) + (last - 0x30);
	}

	return sum == 52974;
}

bool aoc_2023_1::part2()
{
	auto file = open_input_file(2023, 1);
	auto values = read_as<std::string>(file);

	int sum = 0;

	std::map<std::string, int> mapping{
		{"one", 1},
		{"two", 2},
		{"three", 3},
		{"four", 4},
		{"five", 5},
		{"six", 6},
		{"seven", 7},
		{"eight", 8},
		{"nine", 9}
	};

	for (auto v : values)
	{
		int first = -1;
		int last = -1;

		for (int i = 0; i < v.size(); i++) {
			int current = -1;

			for (auto&& [str, num] : mapping)
			{
				if (v.substr(i).starts_with(str))
				{
					current = num;
					break;
				}
			}
			
			if (v[i] >= '0' && v[i] <= '9')
			{
				current = v[i] - 0x30;
			}

			if (current != -1)
			{
				if (first == -1)
				{
					first = current;
				}
				last = current;
			}
		}

		sum += (first * 10) + last;
	}

	return sum == 53340;
}
