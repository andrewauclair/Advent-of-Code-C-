#pragma once

struct base_day
{
	virtual ~base_day() = default;

	virtual bool part1() = 0;
	virtual bool part2() = 0;
};
