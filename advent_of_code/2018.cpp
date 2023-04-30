#include "2018.h"
#include "utils.h"
#include <numeric>
#include <set>

bool aoc_2018_1::part1()
{
	auto file = open_input_file(2018, 1);

	std::vector<int> frequencies;

	int freq;

	while (file >> freq)
	{
		frequencies.push_back(freq);
	}

	int total = std::accumulate(frequencies.begin(), frequencies.end(), 0);

	return total == 518;
}

bool aoc_2018_1::part2()
{
	auto file = open_input_file(2018, 1);

	std::vector<int> frequencies;

	int freq;

	while (file >> freq)
	{
		frequencies.push_back(freq);
	}

	std::set<int> reached;

	int total = 0;
	bool found = false;

	while (!found)
	{
		for (int i : frequencies)
		{
			const std::size_t start_size = reached.size();

			total += i;
			reached.insert(total);

			if (reached.size() == start_size)
			{
				found = true;
				break;
			}
		}
	}

	return total == 72889;
}
