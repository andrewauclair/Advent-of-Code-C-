#pragma once

#include <vector>
#include <memory>

#include "base_day.h"

struct aoc_day
{
	std::unique_ptr<base_day> processor;
	int year;
	int day;
};

inline std::vector<aoc_day> days;

// https://youtu.be/0a3wjaeP6eQ
template<typename T>
struct Init
{
	struct Inst
	{
		Inst()
		{
			(*(T*)(1))();
		}
	};
	static inline Inst inst;
};


#define REGISTER_DAY(year, day) \
	void register_day() const \
	{ \
		constexpr auto fn = []() { days.push_back({ std::make_unique<aoc_##year##_##day>(), year, day }); }; \
		(void)&Init<decltype(fn)>::inst; \
	}
