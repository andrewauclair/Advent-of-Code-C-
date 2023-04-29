#pragma once

#include <vector>
#include <memory>

#include "base_day.h"

struct day_object
{
	std::unique_ptr<base_day> obj;
	int year;
	int day;
};

inline std::vector<day_object> days;

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


#define REGISTER_DAY(DayType, year, day) \
	constexpr auto fn = []() { days.push_back({ std::make_unique< DayType >(), year, day }); }; \
	(void)&Init<decltype(fn)>::inst;
