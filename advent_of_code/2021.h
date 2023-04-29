#pragma once

#include "base_day.h"
#include "register.h"

#include <iostream>

struct _2021_1 : base_day { void register_day() { REGISTER_DAY(_2021_1, 2021, 1) };  bool part1() override; bool part2() override; };
