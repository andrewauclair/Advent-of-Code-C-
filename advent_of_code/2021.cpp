#include "2021.h"
#include "utils.h"
#include <array>

bool _2021_1::part1()
{
	auto file = open_input_file(2021, 1);

	std::vector<int> depths;

	std::copy(std::istream_iterator<int>(file), std::istream_iterator<int>(), std::back_inserter(depths));

	int depth_increases = 0;

	int last_depth = depths.at(0);

	for (size_t i = 1; i < depths.size(); i++)
	{
		const int depth = depths.at(i);

		if (depth > last_depth)
		{
			depth_increases++;
		}
		last_depth = depth;
	}

	return depth_increases == 1195;
}

bool _2021_1::part2()
{
	auto file = open_input_file(2021, 1);

	std::vector<int> depths;

	std::copy(std::istream_iterator<int>(file), std::istream_iterator<int>(), std::back_inserter(depths));

	std::array<int, 3> window { depths.at(0), depths.at(1), depths.at(2) };

	int sum{ window.at(0) + window.at(1) + window.at(2) };

	int depth_increases{};

	for (size_t i = 3; i < depths.size(); i++)
	{
		const int previous_sum{ sum };

		window = { window.at(1), window.at(2), depths.at(i) };

		sum = window.at(0) + window.at(1) + window.at(2);

		if (sum > previous_sum)
		{
			depth_increases++;
		}
	}

	return depth_increases == 1235;
}
