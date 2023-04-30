#include "2019.h"
#include "utils.h"

namespace
{
	int fuel_required(int mass)
	{
		int total_fuel = 0;

		while (mass > 0)
		{
			const int fuel = static_cast<int>(std::floor(mass / 3.0)) - 2;

			if (fuel < 0)
			{
				break;
			}

			total_fuel += fuel;
			mass = fuel;
		}
		
		return total_fuel;
	}
}

bool aoc_2019_1::part1()
{
	auto file = open_input_file(2019, 1);

	std::vector<int> module_masses;

	int mass;

	while (file >> mass)
	{
		module_masses.push_back(mass);
	}

	int total_fuel = 0;

	for (const int module_mass : module_masses)
	{
		total_fuel += static_cast<int>(std::floor(module_mass / 3.0)) - 2;
	}

	return total_fuel == 3268951;
}

bool aoc_2019_1::part2()
{
	auto file = open_input_file(2019, 1);

	std::vector<int> module_masses;

	int mass;

	while (file >> mass)
	{
		module_masses.push_back(mass);
	}

	int total_fuel = 0;

	for (const int module_mass : module_masses)
	{
		total_fuel += fuel_required(module_mass);
	}

	return total_fuel == 4900568;
}
