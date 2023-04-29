#pragma once

#include "base_day.h"
#include "register.h"

#include <iostream>

struct _2022_1 : base_day { void register_day() { REGISTER_DAY(_2022_1, 2022, 1) };  bool part1() override; bool part2() override; };
