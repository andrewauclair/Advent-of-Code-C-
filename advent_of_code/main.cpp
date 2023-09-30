#include "register.h"

#include <iostream>
#include <format>

int main()
{
	int stars = 0;

	std::cout << static_cast<char>(213);
	std::cout << static_cast<char>(205);
	std::cout << static_cast<char>(205);
	std::cout << static_cast<char>(205);
	std::cout << static_cast<char>(205);
	std::cout << static_cast<char>(205);
	std::cout << static_cast<char>(205);

	for (int i = 0; i < 25; i++) {
		std::cout << static_cast<char>(209);
		std::cout << static_cast<char>(205);
		std::cout << static_cast<char>(205);
	}
	std::cout << static_cast<char>(184);

	std::cout << '\n';
	std::cout << static_cast<char>(179);
	std::cout << " Year ";
	std::cout << static_cast<char>(179);
	std::cout << " 1";
	std::cout << static_cast<char>(179);
	std::cout << " 2";
	std::cout << static_cast<char>(179);
	std::cout << " 3";
	std::cout << static_cast<char>(179);
	std::cout << " 4";
	std::cout << static_cast<char>(179);
	std::cout << " 5";
	std::cout << static_cast<char>(179);
	std::cout << " 6";
	std::cout << static_cast<char>(179);
	std::cout << " 7";
	std::cout << static_cast<char>(179);
	std::cout << " 8";
	std::cout << static_cast<char>(179);
	std::cout << " 9";
	std::cout << static_cast<char>(179);
	std::cout << "10";
	std::cout << static_cast<char>(179);
	std::cout << "11";
	std::cout << static_cast<char>(179);
	std::cout << "12";
	std::cout << static_cast<char>(179);
	std::cout << "13";
	std::cout << static_cast<char>(179);
	std::cout << "14";
	std::cout << static_cast<char>(179);
	std::cout << "15";
	std::cout << static_cast<char>(179);
	std::cout << "16";
	std::cout << static_cast<char>(179);
	std::cout << "17";
	std::cout << static_cast<char>(179);
	std::cout << "18";
	std::cout << static_cast<char>(179);
	std::cout << "19";
	std::cout << static_cast<char>(179);
	std::cout << "20";
	std::cout << static_cast<char>(179);
	std::cout << "21";
	std::cout << static_cast<char>(179);
	std::cout << "22";
	std::cout << static_cast<char>(179);
	std::cout << "23";
	std::cout << static_cast<char>(179);
	std::cout << "24";
	std::cout << static_cast<char>(179);
	std::cout << "25";
	std::cout << static_cast<char>(179);
	
	std::cout << '\n';

	std::cout << static_cast<char>(195);
	std::cout << static_cast<char>(196);
	std::cout << static_cast<char>(196);
	std::cout << static_cast<char>(196);
	std::cout << static_cast<char>(196);
	std::cout << static_cast<char>(196);
	std::cout << static_cast<char>(196);
	
	for (int i = 0; i < 25; i++) {
		std::cout << static_cast<char>(197);
		std::cout << static_cast<char>(196);
		std::cout << static_cast<char>(196);
	}
	std::cout << static_cast<char>(180);
	

	int year = 0;
	int days_output = 25;

	for (auto&& problem : days)
	{
		if (problem.year != year) {
			for (int i = days_output; i < 25; i++) {
				std::cout << "  " << static_cast<char>(179);
			}
			days_output = 0;

			year = problem.year;
			std::cout << '\n';

			std::cout << static_cast<char>(179) << ' ';
			std::cout << year; 
			
			std::cout << ' ' << static_cast<char>(179);
		}
		days_output++;

		const bool passed_part1 = problem.processor->part1();
		const bool passed_part2 = problem.processor->part2();

		//std::cout << std::format("{}/{}/1: {}", problem.year, problem.day, passed_part1 ? "pass" : "fail!!") << '\n';
		//std::cout << std::format("{}/{}/2: {}", problem.year, problem.day, passed_part2 ? "pass" : "fail!!") << '\n';

		if (passed_part1)
		{
			std::cout << static_cast<char>(251);
			++stars;
		}
		else {
			std::cout << static_cast<char>(219);
		}

		if (passed_part2)
		{
			std::cout << static_cast<char>(251);
			++stars;
		}
		else {
			std::cout << static_cast<char>(219);
		}
		std::cout << static_cast<char>(179);
	}
	for (int i = days_output; i < 25; i++) {
		std::cout << "  " << static_cast<char>(179);
	}
	std::cout << '\n';
	std::cout << static_cast<char>(192);
	for (int i = 0; i < 6; i++) {
		std::cout << static_cast<char>(196);
	}
	for (int i = 0; i < 25; i++) {
		std::cout << static_cast<char>(193);
		std::cout << static_cast<char>(196);
		std::cout << static_cast<char>(196);
	}
	std::cout << static_cast<char>(217);

	std::cout << "\n\n" << "total stars: " << stars;
}
