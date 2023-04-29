#include "register.h"

#include <iostream>
#include <format>

int main()
{
	for (auto&& problem : days)
	{
		std::cout << std::format("{}/{}/1: {}", problem.year, problem.day, problem.obj->part1() ? "pass" : "fail") << '\n';
		std::cout << std::format("{}/{}/2: {}", problem.year, problem.day, problem.obj->part2() ? "pass" : "fail") << '\n';
	}
}
