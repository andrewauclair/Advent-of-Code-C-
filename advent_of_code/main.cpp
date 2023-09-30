#include "register.h"

#include <iostream>
#include <format>

int main()
{
	int stars = 0;

	for (auto&& problem : days)
	{
		const bool passed_part1 = problem.processor->part1();
		const bool passed_part2 = problem.processor->part2();

		std::cout << std::format("{}/{}/1: {}", problem.year, problem.day, passed_part1 ? "pass" : "fail!!") << '\n';
		std::cout << std::format("{}/{}/2: {}", problem.year, problem.day, passed_part2 ? "pass" : "fail!!") << '\n';

		if (passed_part1)
		{
			++stars;
		}

		if (passed_part2)
		{
			++stars;
		}
	}
	std::cout << '\n' << "total stars: " << stars;
}
