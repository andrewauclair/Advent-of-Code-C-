#include "2023.h"

#include "utils.h"

#include <vector>
#include <numeric>
#include <algorithm>
#include <map>
#include <set>
#include <deque>
#include <array>

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

bool aoc_2023_4::part1()
{
	struct Card {
		int card_number;
		int score = 0;

		std::vector<int> held_numbers;
		std::vector<int> winning_numbers;
	};

	auto file = open_input_file(2023, 4);
	const auto values = read_lines(file);

	std::vector<Card> cards;

	for (auto&& card_input : values) {
		Card card;
		std::string held;
		std::string winning;

		std::istringstream iss(card_input);

		std::string cardNum;
		std::getline(iss, cardNum, ':');
		std::getline(iss, held, '|');
		std::getline(iss, winning, '|');

		trim(held);
		trim(winning);

		for (auto&& num : split_by_whitespace(held)) {
			card.held_numbers.push_back(std::stoi(num));
		}

		for (auto&& num : split_by_whitespace(winning)) {
			card.winning_numbers.push_back(std::stoi(num));
		}

		for (int num : card.held_numbers) {
			if (std::find(card.winning_numbers.begin(), card.winning_numbers.end(), num) != card.winning_numbers.end()) {
				if (card.score == 0) {
					card.score = 1;
				}
				else {
					card.score *= 2;
				}
			}
		}
		cards.push_back(card);
	}

	int sum = 0;

	for (auto&& card : cards) {
		sum += card.score;
	}

	return sum == 24160;
}

bool aoc_2023_4::part2()
{
	struct Card {
		int matches = 0;
		int copies = 0;

		std::vector<int> held_numbers;
		std::vector<int> winning_numbers;
	};

	auto file = open_input_file(2023, 4);
	const auto values = read_lines(file);

	std::map<int, Card> cards;

	for (auto&& card_input : values) {
		Card card;
		std::string held;
		std::string winning;

		std::istringstream iss(card_input);

		std::string cardNumPart;
		std::getline(iss, cardNumPart, ':');
		std::getline(iss, held, '|');
		std::getline(iss, winning, '|');


		trim(held);
		trim(winning);

		for (auto&& num : split_by_whitespace(held)) {
			card.held_numbers.push_back(std::stoi(num));
		}

		for (auto&& num : split_by_whitespace(winning)) {
			card.winning_numbers.push_back(std::stoi(num));
		}

		for (int num : card.held_numbers) {
			if (std::find(card.winning_numbers.begin(), card.winning_numbers.end(), num) != card.winning_numbers.end()) {
				card.matches++;
			}
		}
		cards[std::stoi(split_by_whitespace(cardNumPart)[1])] = card;
	}

	struct Process {
		int card_num;
		int copies = 1;
	};
	std::vector<Process> cards_to_process;
	for (int i = 1; i <= cards.size(); i++) {
		cards_to_process.emplace_back(i, 1);
	}

	for (auto&& process : cards_to_process) {
		Card& card = cards.at(process.card_num);

		card.copies += process.copies;

		for (int i = 0; i < card.matches; i++) {
			cards_to_process.at(process.card_num + i).copies += card.copies;
		}
	}

	int sum = 0;

	for (auto&& card : cards) {
		sum += card.second.copies;
	}

	return sum == 5659035;
}

bool aoc_2023_5::part1()
{
	struct Range {
		std::int64_t start;
		std::int64_t end;
	};
	struct Mapping {
		Range input;
		Range output;

		Mapping(std::int64_t input_start, std::int64_t output_start, std::int64_t count)
			: input{ input_start, input_start + count },
			output{ output_start, output_start + count } {
		}
	};
	struct Mappings {
		std::vector<Mapping> mappings;

		std::int64_t map(std::int64_t input) const noexcept {
			for (auto&& mapping : mappings) {
				if (input >= mapping.input.start && input < mapping.input.end) {
					return mapping.output.start + (input - mapping.input.start);
				}
			}
			return input;
		}
	};

	struct Data {
		Mappings seed_to_soil;
		Mappings soil_to_fertilizer;
		Mappings fertilizer_to_water;
		Mappings water_to_light;
		Mappings light_to_temperature;
		Mappings temperature_to_humidity;
		Mappings humidity_to_location;

		std::int64_t map(std::int64_t seed) {
			auto soil = seed_to_soil.map(seed);
			auto fertilizer = soil_to_fertilizer.map(soil);
			auto water = fertilizer_to_water.map(fertilizer);
			auto light = water_to_light.map(water);
			auto temperature = light_to_temperature.map(light);
			auto humidity = temperature_to_humidity.map(temperature);
			auto location = humidity_to_location.map(humidity);

			return location;
		}
	};

	auto file = open_input_file(2023, 5);

	std::string seeds;
	std::getline(file, seeds);

	seeds = seeds.substr(7);

	std::string skip;
	std::getline(file, skip);
	std::getline(file, skip); // seed-to-soil map

	const auto read_mapping = [&]() -> Mappings {
		std::string line;
		std::vector<Mapping> ranges;
		while (std::getline(file, line))
		{
			if (line.empty())
			{
				break;
			}
			std::int64_t in, out, count;
			std::sscanf(line.c_str(), "%lld %lld %lld", &out, &in, &count);

			ranges.emplace_back(in, out, count);
		}
		return { ranges };
	};

	Data data;
	data.seed_to_soil = read_mapping();
	data.soil_to_fertilizer = read_mapping();
	data.fertilizer_to_water = read_mapping();
	data.water_to_light = read_mapping();
	data.light_to_temperature = read_mapping();
	data.temperature_to_humidity = read_mapping();
	data.humidity_to_location = read_mapping();
	
	std::int64_t lowest_location = std::numeric_limits<std::int64_t>::max();
	std::string seed;
	std::istringstream iss(seeds);
	while (iss >> seed) {
		lowest_location = std::min(lowest_location, data.map(std::stoll(seed)));
	}
	return lowest_location == 240320250;
}

bool aoc_2023_5::part2()
{
	struct Range {
		std::int64_t start;
		std::int64_t end;
	};
	struct Mapping {
		Range input;
		Range output;

		Mapping(std::int64_t input_start, std::int64_t output_start, std::int64_t count)
			: input{ input_start, input_start + count },
			output{ output_start, output_start + count } {
		}
	};
	struct Mappings {
		std::vector<Mapping> mappings;

		std::int64_t map(std::int64_t input) const noexcept {
			for (auto&& mapping : mappings) {
				if (input >= mapping.input.start && input < mapping.input.end) {
					return mapping.output.start + (input - mapping.input.start);
				}
			}
			return input;
		}
	};

	struct Data {
		Mappings seed_to_soil;
		Mappings soil_to_fertilizer;
		Mappings fertilizer_to_water;
		Mappings water_to_light;
		Mappings light_to_temperature;
		Mappings temperature_to_humidity;
		Mappings humidity_to_location;

		std::int64_t map(std::int64_t seed) const noexcept {
			auto soil = seed_to_soil.map(seed);
			auto fertilizer = soil_to_fertilizer.map(soil);
			auto water = fertilizer_to_water.map(fertilizer);
			auto light = water_to_light.map(water);
			auto temperature = light_to_temperature.map(light);
			auto humidity = temperature_to_humidity.map(temperature);
			auto location = humidity_to_location.map(humidity);

			return location;
		}

		std::int64_t map_soil(std::int64_t soil) const noexcept {
			auto fertilizer = soil_to_fertilizer.map(soil);
			auto water = fertilizer_to_water.map(fertilizer);
			auto light = water_to_light.map(water);
			auto temperature = light_to_temperature.map(light);
			auto humidity = temperature_to_humidity.map(temperature);
			auto location = humidity_to_location.map(humidity);

			return location;
		}
	};

	auto file = open_input_file(2023, 5);

	std::string seeds;
	std::getline(file, seeds);

	seeds = seeds.substr(7);

	std::string skip;
	std::getline(file, skip);
	std::getline(file, skip); // seed-to-soil map

	const auto read_mapping = [&]() -> Mappings {
		std::string line;
		std::vector<Mapping> ranges;
		while (std::getline(file, line))
		{
			if (line.empty())
			{
				break;
			}
			std::int64_t in, out, count;
			std::sscanf(line.c_str(), "%lld %lld %lld", &out, &in, &count);

			ranges.emplace_back(in, out, count);
		}
		return { ranges };
		};

	Data data;
	data.seed_to_soil = read_mapping();
	data.soil_to_fertilizer = read_mapping();
	data.fertilizer_to_water = read_mapping();
	data.water_to_light = read_mapping();
	data.light_to_temperature = read_mapping();
	data.temperature_to_humidity = read_mapping();
	data.humidity_to_location = read_mapping();

	std::int64_t lowest_location = std::numeric_limits<std::int64_t>::max();
	std::int64_t seed;
	std::int64_t seed_count;
	std::istringstream iss(seeds);

	std::set<std::int64_t> soil_values;

	while (iss >> seed >> seed_count) {
		for (std::int64_t i = seed; i < seed + seed_count; i++)
		{
			soil_values.insert(data.seed_to_soil.map(i));
		}
	}

	for (std::int64_t soil : soil_values)
	{
		for (std::int64_t i = seed; i < seed + seed_count; i++) {
			std::int64_t soil = data.seed_to_soil.map(i);

			//if (soil != previous_soil) 
			{
				lowest_location = std::min(lowest_location, data.map(i));
			}
		}
	}
	return lowest_location == 28580589;
}

bool aoc_2023_6::part1()
{
	auto file = open_input_file(2023, 6);

	std::string times;
	std::string distances;

	std::getline(file, times);
	std::getline(file, distances);

	times = times.substr(5);
	distances = distances.substr(9);

	std::istringstream iss_times(times);
	std::istringstream iss_distances(distances);

	struct Race {
		int time;
		int distance;
	};

	int time;
	int record_distance;

	int mult = 1;

	while (iss_times >> time && iss_distances >> record_distance)
	{
		int winners = 0;

		for (int i = 1; i < time; i++)
		{
			int distance = i * (time - i);

			if (distance > record_distance)
			{
				winners++;
			}
		}

		mult *= winners;
	}

	return mult == 503424;
}

bool aoc_2023_6::part2()
{
	auto file = open_input_file(2023, 6);

	std::string times;
	std::string distances;

	std::getline(file, times);
	std::getline(file, distances);

	times = times.substr(5);
	distances = distances.substr(9);

	times.erase(std::remove_if(times.begin(), times.end(), isspace), times.end());
	distances.erase(std::remove_if(distances.begin(), distances.end(), isspace), distances.end());

	std::int64_t time = std::stoll(times);
	std::int64_t record_distance = std::stoll(distances);

	std::int64_t winners = 0;

	for (std::int64_t i = 1; i < time; i++)
	{
		std::int64_t distance = i * (time - i);

		if (distance > record_distance)
		{
			winners++;
		}
	}

	return winners == 32607562;
}

bool aoc_2023_7::part1()
{
	enum class Card
	{
		_2 = 2,_3,_4,_5,_6,_7,_8,_9,
		T,J,Q,K,A
	};
	enum class Hand_Kind
	{
		high_card,
		one_pair,
		two_pair,
		three_of_a_kind,
		full_house,
		four_of_a_kind,
		five_of_a_kind,
	};
	struct Hand
	{
	private:
		std::array<Card, 5> cards;
		int m_bid = 0;
		Hand_Kind kind;

		bool is_five_of_a_kind() const
		{
			std::set<Card> set_of_cards{ cards.begin(), cards.end() };

			return set_of_cards.size() == 1;
		}

		bool is_four_of_a_kind() const
		{
			std::map<Card, int> counts;

			for (Card card : cards)
			{
				counts[card]++;
			}

			for (auto&& [card, count] : counts)
			{
				if (count == 4)
				{
					return true;
				}
			}
			return false;
		}

		bool is_full_house() const
		{
			std::map<Card, int> counts;

			for (Card card : cards)
			{
				counts[card]++;
			}

			int two_count = 0;
			int three_count = 0;
			for (auto&& [card, count] : counts)
			{
				if (count == 2) two_count++;
				if (count == 3) three_count++;
			}
			return two_count == 1 && three_count == 1;
		}

		bool is_three_of_a_kind() const
		{
			std::map<Card, int> counts;

			for (Card card : cards)
			{
				counts[card]++;
			}

			for (auto&& [card, count] : counts)
			{
				if (count == 3)
				{
					return true;
				}
			}
			return false;
		}

		bool is_two_pair() const
		{
			std::map<Card, int> counts;

			for (Card card : cards)
			{
				counts[card]++;
			}

			int two_count = 0;
			for (auto&& [card, count] : counts)
			{
				if (count == 2) two_count++;
			}
			return two_count == 2;
		}

		bool is_one_pair() const
		{
			std::map<Card, int> counts;

			for (Card card : cards)
			{
				counts[card]++;
			}

			int two_count = 0;
			for (auto&& [card, count] : counts)
			{
				if (count == 2) two_count++;
			}
			return two_count == 1;
		}

	public:
		Hand(std::array<Card, 5> cards, int bid) : cards(std::move(cards)), m_bid(bid)
		{
			//std::sort(this->cards.begin(), this->cards.end());

			if (is_five_of_a_kind())
			{
				kind = Hand_Kind::five_of_a_kind;
			}
			else if (is_four_of_a_kind())
			{
				kind = Hand_Kind::four_of_a_kind;
			}
			else if (is_full_house())
			{
				kind = Hand_Kind::full_house;
			}
			else if (is_three_of_a_kind())
			{
				kind = Hand_Kind::three_of_a_kind;
			}
			else if (is_two_pair())
			{
				kind = Hand_Kind::two_pair;
			}
			else if (is_one_pair())
			{
				kind = Hand_Kind::one_pair;
			}
			else
			{
				kind = Hand_Kind::high_card;
			}
		}

		int bid() const { return m_bid; }

		bool operator<(const Hand& other) const 
		{
			if (kind < other.kind) return true;
			else if (kind != other.kind) return false;

			for (int i = 0; i < 5; i++)
			{
				if (cards[i] < other.cards[i]) return true;
				else if (cards[i] != other.cards[i]) return false;
			}
			return true;
		}
	};

	auto file = open_input_file(2023, 7);
	std::string hand_str;
	int bid;

	std::vector<Hand> hands;

	while (file >> hand_str >> bid)
	{
		const auto char_to_card = [&](char ch) {
			switch (ch)
			{
			default:
			case '2': return Card::_2;
			case'3': return Card::_3;
			case '4': return Card::_4;
			case'5': return Card::_5;
			case '6':return Card::_6;
			case '7':return Card::_7;
			case '8':return Card::_8;
			case '9':return Card::_9;
			case 'T':return Card::T;
			case 'J':return Card::J;
			case 'Q':return Card::Q;
			case 'K':return Card::K;
			case 'A':return Card::A;
			}
			
			};
		std::array<Card, 5> cards{ 
			char_to_card(hand_str[0]),
			char_to_card(hand_str[1]),
			char_to_card(hand_str[2]),
			char_to_card(hand_str[3]),
			char_to_card(hand_str[4]),
			};
		Hand hand{ cards, bid };

		hands.push_back(hand);
	}

	std::sort(hands.begin(), hands.end());

	int total = 0;

	for (int i = 1; i <= hands.size(); i++)
	{
		total += i * hands[i - 1].bid();
	}

	return total == 248113761;
}

bool aoc_2023_7::part2()
{
	enum class Card
	{
		J, _2, _3, _4, _5, _6, _7, _8, _9,
		T, Q, K, A
	};
	enum class Hand_Kind
	{
		high_card,
		one_pair,
		two_pair,
		three_of_a_kind,
		full_house,
		four_of_a_kind,
		five_of_a_kind,
	};
	struct Hand
	{
	private:
		std::array<Card, 5> cards;
		int m_bid = 0;
		Hand_Kind kind;

		bool is_five_of_a_kind() const
		{
			std::map<Card, int> counts;

			for (Card card : cards)
			{
				counts[card]++;
			}

			for (auto&& [card, count] : counts)
			{
				if (count == 5)
				{
					return true;
				}
				else if (card != Card::J && count + counts[Card::J] >= 5)
				{
					return true;
				}
			}
			return false;
		}

		bool is_four_of_a_kind() const
		{
			std::map<Card, int> counts;

			for (Card card : cards)
			{
				counts[card]++;
			}

			for (auto&& [card, count] : counts)
			{
				if (count == 4)
				{
					return true;
				}
				else if (card != Card::J && count + counts[Card::J] >= 4)
				{
					return true;
				}
			}
			return false;
		}

		bool is_full_house() const
		{
			std::map<Card, int> counts;

			for (Card card : cards)
			{
				counts[card]++;
			}

			bool has_two = false;
			bool has_three = false;
			int two_count = 0;
			int three_count = 0;
			for (auto&& [card, count] : counts)
			{
				if (card == Card::J) continue;

				if (count == 2) {
					has_two = true;
					two_count++;
				}
				if (count == 3) {
					has_three = true;
					three_count++;
				}
			}
			if (has_two && has_three)
			{
				return true;
			}
			else
			{
				// try to create a full house with Jokers
				if (counts[Card::J] == 0) return false;

				if (counts.size() < 3) return false;

				int breakpoint = 0;

				if (has_two && !has_three && two_count >= 2)
				{
					return true;
				}
				else if (!has_two && has_three)
				{
					for (auto&& [card, count] : counts)
					{
						if (card == Card::J) continue;

						if (count == 1) return true;
					}
				}
			}
			return false;
		}

		bool is_three_of_a_kind() const
		{
			std::map<Card, int> counts;

			for (Card card : cards)
			{
				counts[card]++;
			}

			for (auto&& [card, count] : counts)
			{
				if (count == 3)
				{
					return true;
				}
				else if (card != Card::J && count + counts[Card::J] >= 3)
				{
					return true;
				}
			}
			return false;
		}

		bool is_two_pair() const
		{
			std::map<Card, int> counts;

			for (Card card : cards)
			{
				counts[card]++;
			}

			int two_count = 0;
			for (auto&& [card, count] : counts)
			{
				if (count == 2) two_count++;
			}
			if (two_count == 2)
			{
				return true;
			}
			else if (two_count == 1)
			{
				for (auto&& [card, count] : counts)
				{
					if (count == 1 && card != Card::J && counts[Card::J] >= 1)
					{
						return true;
					}
				}
			}
			return false;
		}

		bool is_one_pair() const
		{
			std::map<Card, int> counts;

			for (Card card : cards)
			{
				counts[card]++;
			}

			int two_count = 0;
			for (auto&& [card, count] : counts)
			{
				if (count == 2) two_count++;
			}
			if (two_count == 1)
			{
				return true;
			}
			else
			{
				Card high_card = Card::J;

				for (auto&& [card, count] : counts)
				{
					if (count == 1 && card != Card::J && card > high_card)
					{
						high_card = card;
					}
				}

				if (high_card != Card::J && counts[Card::J] >= 1)
				{
					return true;
				}
			}
			return false;
		}

	public:
		Hand(std::array<Card, 5> cards, int bid) : cards(std::move(cards)), m_bid(bid)
		{
			if (is_five_of_a_kind())
			{
				kind = Hand_Kind::five_of_a_kind;
			}
			else if (is_four_of_a_kind())
			{
				kind = Hand_Kind::four_of_a_kind;
			}
			else if (is_full_house())
			{
				kind = Hand_Kind::full_house;
			}
			else if (is_three_of_a_kind())
			{
				kind = Hand_Kind::three_of_a_kind;
			}
			else if (is_two_pair())
			{
				kind = Hand_Kind::two_pair;
			}
			else if (is_one_pair())
			{
				kind = Hand_Kind::one_pair;
			}
			else
			{
				kind = Hand_Kind::high_card;
			}
		}

		int bid() const { return m_bid; }

		bool operator<(const Hand& other) const
		{
			if (kind < other.kind) return true;
			else if (kind != other.kind) return false;

			for (int i = 0; i < 5; i++)
			{
				if (cards[i] < other.cards[i]) return true;
				else if (cards[i] != other.cards[i]) return false;
			}
			return true;
		}
	};

	auto file = open_input_file(2023, 7);
	std::string hand_str;
	int bid;

	std::vector<Hand> hands;

	while (file >> hand_str >> bid)
	{
		const auto char_to_card = [&](char ch) {
			switch (ch)
			{
			default:
			case '2': return Card::_2;
			case'3': return Card::_3;
			case '4': return Card::_4;
			case'5': return Card::_5;
			case '6':return Card::_6;
			case '7':return Card::_7;
			case '8':return Card::_8;
			case '9':return Card::_9;
			case 'T':return Card::T;
			case 'J':return Card::J;
			case 'Q':return Card::Q;
			case 'K':return Card::K;
			case 'A':return Card::A;
			}

			};
		std::array<Card, 5> cards{
			char_to_card(hand_str[0]),
			char_to_card(hand_str[1]),
			char_to_card(hand_str[2]),
			char_to_card(hand_str[3]),
			char_to_card(hand_str[4]),
		};
		Hand hand{ cards, bid };

		hands.push_back(hand);
	}

	std::sort(hands.begin(), hands.end());

	int total = 0;

	for (int i = 1; i <= hands.size(); i++)
	{
		total += i * hands[i - 1].bid();
	}

	return total == 246285222;
}