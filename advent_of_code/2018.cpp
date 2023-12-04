#include "2018.h"
#include "utils.h"
#include <numeric>
#include <unordered_set>

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

	std::unordered_set<int> reached;

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

bool aoc_2018_2::part1()
{
	auto file = open_input_file(2018, 2);

	const std::vector<std::string> lines = read_lines(file);

	int lines_with_2_chars = 0;
	int lines_with_3_chars = 0;

	for (const std::string& line : lines)
	{
		bool counted_2 = false;
		bool counted_3 = false;

		for (char ch : line)
		{
			auto count = std::count(line.begin(), line.end(), ch);

			if (!counted_2 && count == 2)
			{
				lines_with_2_chars++;
				counted_2 = true;
			}
			if (!counted_3 && count == 3)
			{
				lines_with_3_chars++;
				counted_3 = true;
			}
		}
	}

	return (lines_with_2_chars * lines_with_3_chars) == 8118;
}

bool aoc_2018_2::part2()
{
	auto file = open_input_file(2018, 2);

	const std::vector<std::string> lines = read_lines(file);

	std::string answer;

	for (int i = 0; i < lines.size(); i++)
	{
		for (int j = i + 1; j < lines.size(); j++)
		{
			int diffs = 0;

			for (int k = 0; k < std::min(lines[i].length(), lines[j].length()); k++)
			{
				if (lines[i][k] != lines[j][k])
				{
					diffs++;
				}
				if (diffs > 1)
				{
					break;
				}
			}
			if (diffs == 1)
			{
				for (int k = 0; k < std::min(lines[i].length(), lines[j].length()); k++)
				{
					if (lines[i][k] == lines[j][k])
					{
						answer += lines[i][k];
					}
				}
				break;
			}
		}
		if (!answer.empty())
		{
			break;
		}
	}
	
	return answer == "jbbenqtlaxhivmwyscjukztdp";
}

bool aoc_2018_3::part1()
{
	auto file = open_input_file(2018, 3);

	struct claim {
		int claim_number;
		int left_edge;
		int right_edge;
		int width;
		int height;
	};

	const auto claims = [&file]() -> std::vector<claim> {
		const std::vector<std::string> lines = read_lines(file);

		int claim_number;
		int left_edge;
		int right_edge;
		int width;
		int height;

		std::vector<claim> claims;

		for (auto&& line : lines)
		{
			std::sscanf(line.c_str(), "#%d @ %d,%d: %dx%d", &claim_number, &left_edge, &right_edge, &width, &height);

			claims.emplace_back(claim_number, left_edge, right_edge, width, height);
		}

		return claims;
	}();

	std::vector<short> counts;
	counts.resize(1000 * 1000);

	for (auto&& claim : claims)
	{

	}

	return false;
}

bool aoc_2018_3::part2()
{
	auto file = open_input_file(2018, 3);

	return false;
}
