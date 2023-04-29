#pragma once

#include "base_day.h"
#include "register.h"

#include <iostream>

struct _2016_1 : base_day { void register_day() { REGISTER_DAY(_2016_1, 2016, 1) };  bool part1() override; bool part2() override; };
