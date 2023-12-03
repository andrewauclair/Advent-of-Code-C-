#include "2023.h"

#include "utils.h"

#include <vector>
#include <numeric>
#include <algorithm>
#include <map>
#include <set>

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

bool aoc_2023_2::part1()
{
	enum class color {
		red, green, blue
	};
	struct set {
		int count;
		color set_color;
	};
	struct game {
		std::vector<set> sets;

		bool is_valid(int red, int green, int blue) {
			for (auto&& s : sets) {
				switch (s.set_color) {
				case color::red:
					if (s.count > red) return false;
					break;
				case color::green:
					if (s.count > green) return false; 
					break;
				case color::blue:
					if (s.count > blue) return false;
					break;
				}
			}
			return true;
		}
	};

	int sum = 0;

	auto file = open_input_file(2023, 2);
	const auto values = read_lines(file);

	std::vector<game> games;

	for (auto&& line : values) {
		std::istringstream iss(line);

		std::string game_id_str;
		std::string remaining;
		std::getline(iss, game_id_str, ':');
		std::getline(iss, remaining, ':');

		int id;
		std::sscanf(game_id_str.c_str(), "Game %d", &id);

		iss = std::istringstream(remaining);

		std::string set;

		game new_game;
		
		while (std::getline(iss, set, ';'))
		{
			std::istringstream set_iss(set);

			const auto set_values = read_as<std::string>(set_iss);


			for (int i = 0; i < set_values.size(); i += 2)
			{
				color set_color;
				std::string set_color_raw = set_values[i + 1];

				if (set_color_raw.starts_with("red"))
				{
					set_color = color::red;
				}
				else if (set_color_raw.starts_with("green"))
				{
					set_color = color::green;
				}
				else if (set_color_raw.starts_with("blue"))
				{
					set_color = color::blue;
				}
				new_game.sets.emplace_back(std::stoi(set_values[i]), set_color);
			}

			
		}
		if (new_game.is_valid(12, 13, 14))
		{
			sum += id;
		}
	}

	return sum == 2239;
}

bool aoc_2023_2::part2()
{
	enum class color {
		red, green, blue
	};
	struct set {
		int count;
		color set_color;
	};
	struct game {
		std::vector<set> sets;

		int power_of_min()
		{
			int max_red = 0;
			int max_green = 0;
			int max_blue = 0;

			for (auto&& s : sets)
			{
				switch (s.set_color)
				{
				case color::red:
					max_red = std::max(max_red, s.count);
					break;
				case color::green:
					max_green = std::max(max_green, s.count);
					break;
				case color::blue:
					max_blue = std::max(max_blue, s.count);
					break;
				}
			}

			return max_red * max_green * max_blue;
		}
	};

	int sum = 0;

	auto file = open_input_file(2023, 2);
	const auto values = read_lines(file);

	std::vector<game> games;

	for (auto&& line : values) {
		std::istringstream iss(line);

		std::string game_id_str;
		std::string remaining;
		std::getline(iss, game_id_str, ':');
		std::getline(iss, remaining, ':');

		int id;
		std::sscanf(game_id_str.c_str(), "Game %d", &id);

		iss = std::istringstream(remaining);

		std::string set;

		game new_game;

		while (std::getline(iss, set, ';'))
		{
			std::istringstream set_iss(set);

			const auto set_values = read_as<std::string>(set_iss);


			for (int i = 0; i < set_values.size(); i += 2)
			{
				color set_color;
				std::string set_color_raw = set_values[i + 1];

				if (set_color_raw.starts_with("red"))
				{
					set_color = color::red;
				}
				else if (set_color_raw.starts_with("green"))
				{
					set_color = color::green;
				}
				else if (set_color_raw.starts_with("blue"))
				{
					set_color = color::blue;
				}
				new_game.sets.emplace_back(std::stoi(set_values[i]), set_color);
			}


		}

		sum += new_game.power_of_min();
	}

	return sum == 83435;
}

bool aoc_2023_3::part1()
{
	const auto is_digit = [](char ch) {
		return ch >= '0' && ch <= '9';
	};

	const auto is_symbol = [&is_digit](char ch) {
		return !is_digit(ch) && ch != '.';
	};

	auto file = open_input_file(2023, 3);
	const auto values = read_lines(file);

	const auto grid_width = values[0].size();

	const auto grid_height = values.size();

	bool parsing_number = false;
	bool has_symbol = false;
	std::string number;

	int sum = 0;

	for (int i = 0; i < grid_height; i++) {
		for (int j = 0; j < grid_width; j++) {
			const char ch = values[i][j];

			if (parsing_number && is_digit(ch)) {
				number += ch;

				if (!has_symbol) {
					for (int x = -1; x < 2; x++) {
						for (int y = -1; y < 2; y++) {
							if (i + x < 0 || i + x > grid_width - 1 || j + y < 0 || j + y > grid_height - 1) {
								continue;
							}

							if (is_symbol(values[i + x][j + y])) {
								has_symbol = true;
							}
						}
					}
				}
			}
			else if (is_digit(ch)) {
				parsing_number = true;

				number += ch;

				if (!has_symbol) {
					for (int x = -1; x < 2; x++) {
						for (int y = -1; y < 2; y++) {
							if (i + x < 0 || i + x > grid_width - 1 || j + y < 0 || j + y > grid_height - 1) {
								continue;
							}

							if (is_symbol(values[i + x][j + y])) {
								has_symbol = true;
							}
						}
					}
				}
			}
			else if (!number.empty()){
				if (has_symbol) {
					sum += std::stoi(number);
				}
				parsing_number = false;
				has_symbol = false;
				number = "";
			}
		}
	}

	return sum == 533784;
}

bool aoc_2023_3::part2()
{
	const auto is_digit = [](char ch) {
		return ch >= '0' && ch <= '9';
	};

	auto file = open_input_file(2023, 3);
	const auto values = read_lines(file);

	const auto grid_width = values[0].size();

	const auto grid_height = values.size();

	int sum = 0;

	for (int i = 0; i < grid_height; i++) {
		for (int j = 0; j < grid_width; j++) {
			const char ch = values[i][j];

			if (ch == '*') {
				std::set<std::string> part_numbers;

				// check for numbers in surrounding characters
				for (int x = -1; x < 2; x++) {
					for (int y = -1; y < 2; y++) {
						if (i + x < 0 || i + x > grid_width - 1 || j + y < 0 || j + y > grid_height - 1) {
							continue;
						}

						if (is_digit(values[i + x][j + y])) {
							std::string number;

							int start = j + y;

							while (start > 0 && is_digit(values[i + x][start])) {
								start--;
							}
							if (!is_digit(values[i + x][start])) {
								start++;
							}
							int index = start;

							while (is_digit(values[i + x][index])) {
								number += values[i + x][index];
								index++;
							}

							part_numbers.insert(number);
						}
					}
				}

				if (part_numbers.size() == 2) {
					std::vector<std::string> v = std::vector<std::string>(part_numbers.begin(), part_numbers.end());
					sum += std::stoi(v[0]) * std::stoi(v[1]);
				}
			}
		}
	}

	return sum == 78826761;
}
