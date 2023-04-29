#pragma once

#include "base_day.h"
#include "register.h"

#include <iostream>

struct _2020_1 : base_day { void register_day() { REGISTER_DAY(_2020_1, 2020, 1) };  bool part1() override; bool part2() override; };
