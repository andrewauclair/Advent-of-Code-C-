#include "register.h"

#include <iostream>
#include <format>

int main()
{
	for (auto&& problem : days)
	{
		std::cout << std::format("{}/{}/1: {}", problem.year, problem.day, problem.processor->part1() ? "pass" : "fail") << '\n';
		std::cout << std::format("{}/{}/2: {}", problem.year, problem.day, problem.processor->part2() ? "pass" : "fail") << '\n';
	}
}
