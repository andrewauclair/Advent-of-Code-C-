#include "2019.h"
#include "utils.h"

namespace
{
	int fuel_required(int mass)
	{
		int total_fuel = 0;

		while (mass > 0)
		{
			const int fuel = static_cast<int>(std::floor(mass / 3.0)) - 2;

			if (fuel < 0)
			{
				break;
			}

			total_fuel += fuel;
			mass = fuel;
		}
		
		return total_fuel;
	}

	struct IntcodeComputer
	{
		enum class parameter_mode
		{
			position = 0,
			immediate = 1
		};

		std::vector<int> instructions;

		explicit IntcodeComputer(std::vector<int> instructions)
			: instructions(std::move(instructions))
		{
		}

		explicit IntcodeComputer(std::istream& file)
			: instructions(load_instructions(file))
		{
		}

		static std::vector<int> load_instructions(std::istream& file)
		{
			std::vector<int> instructions;
			std::string value;

			while (std::getline(file, value, ','))
			{
				instructions.push_back(std::stoi(value));
			}
			return instructions;
		}

		int run(std::vector<int> inputs, bool diagnostics_on = false)
		{
			if (diagnostics_on)
			{
				std::cout << "\n\nrun computer\n\n";
			}
			bool is_halted = false;
			std::size_t instruction_pointer = 0;
			parameter_mode active_parameter_mode = parameter_mode::position;

			std::size_t next_input = 0;
			int last_output_value = 0;

			do {
				const int instruction = instructions.at(instruction_pointer);

				const int opcode = instruction % 100;
				const parameter_mode parameter_mode1 = static_cast<parameter_mode>((instruction / 100) % 10);
				const parameter_mode parameter_mode2 = static_cast<parameter_mode>((instruction / 1000) % 10);
				const parameter_mode parameter_mode3 = static_cast<parameter_mode>(instruction / 10000);

				switch (opcode)
				{
				case 1: // add
				{
					if (diagnostics_on)
					{
						std::cout << "add(1)\n";
					}
					const int a = instructions.at(instruction_pointer + 1);
					const int b = instructions.at(instruction_pointer + 2);

					const int location = instructions.at(instruction_pointer + 3);

					const int value_a = parameter_mode1 == parameter_mode::immediate ? a : instructions.at(a);
					const int value_b = parameter_mode2 == parameter_mode::immediate ? b : instructions.at(b);

					instructions.at(location) = value_a + value_b;

					instruction_pointer += 4;

					break;
				}
				case 2: // multiply
				{
					if (diagnostics_on)
					{
						std::cout << "multiply(2)\n";
					}
					const int a = instructions.at(instruction_pointer + 1);
					const int b = instructions.at(instruction_pointer + 2);

					const int location = instructions.at(instruction_pointer + 3);

					const int value_a = parameter_mode1 == parameter_mode::immediate ? a : instructions.at(a);
					const int value_b = parameter_mode2 == parameter_mode::immediate ? b : instructions.at(b);

					instructions.at(location) = value_a * value_b;

					instruction_pointer += 4;

					break;
				}
				case 3: // input
				{
					if (diagnostics_on)
					{
						std::cout << "input(3)\n";
					}
					const int input = inputs.at(next_input);
					++next_input;

					const int address = instructions.at(instruction_pointer + 1);

					instructions.at(address) = input;

					instruction_pointer += 2;

					break;
				}
				case 4: // output
				{
					if (diagnostics_on)
					{
						std::cout << "output(4)\n";
					}

					const int parameter1 = instructions.at(instruction_pointer + 1);

					const int value = parameter_mode1 == parameter_mode::immediate ? parameter1 : instructions.at(parameter1);

					last_output_value = value;

					if (diagnostics_on)
					{
						// actually print the value to the screen
						std::cout << value << ' ';
					}

					instruction_pointer += 2;

					break;
				}
				case 5: // jump-if-true
				{
					if (diagnostics_on)
					{
						std::cout << "jump-if-true(5)\n";
					}

					const int a = instructions.at(instruction_pointer + 1);
					const int b = instructions.at(instruction_pointer + 2);

					const int value_a = parameter_mode1 == parameter_mode::immediate ? a : instructions.at(a);
					const int value_b = parameter_mode2 == parameter_mode::immediate ? b : instructions.at(b);

					if (value_a != 0)
					{
						instruction_pointer = value_b;
					}
					else
					{
						instruction_pointer += 3;
					}

					break;
				}
				case 6: // jump-if-false
				{
					if (diagnostics_on)
					{
						std::cout << "jump-if-false(6)\n";
					}

					const int a = instructions.at(instruction_pointer + 1);
					const int b = instructions.at(instruction_pointer + 2);

					const int value_a = parameter_mode1 == parameter_mode::immediate ? a : instructions.at(a);
					const int value_b = parameter_mode2 == parameter_mode::immediate ? b : instructions.at(b);

					if (value_a == 0)
					{
						instruction_pointer = value_b;
					}
					else
					{
						instruction_pointer += 3;
					}


					break;
				}
				case 7: // less than
				{
					if (diagnostics_on)
					{
						std::cout << "less than(7)\n";
					}

					const int a = instructions.at(instruction_pointer + 1);
					const int b = instructions.at(instruction_pointer + 2);
					const int c = instructions.at(instruction_pointer + 3);

					const int value_a = parameter_mode1 == parameter_mode::immediate ? a : instructions.at(a);
					const int value_b = parameter_mode2 == parameter_mode::immediate ? b : instructions.at(b);
					const int value_c = parameter_mode3 == parameter_mode::immediate ? c : instructions.at(c);

					if (value_a < value_b)
					{
						instructions.at(c) = 1;
					}
					else
					{
						instructions.at(c) = 0;
					}

					instruction_pointer += 4;

					break;
				}
				case 8: // equals
				{
					if (diagnostics_on)
					{
						std::cout << "equals (8)\n";
					}

					const int a = instructions.at(instruction_pointer + 1);
					const int b = instructions.at(instruction_pointer + 2);
					const int c = instructions.at(instruction_pointer + 3);

					const int value_a = parameter_mode1 == parameter_mode::immediate ? a : instructions.at(a);
					const int value_b = parameter_mode2 == parameter_mode::immediate ? b : instructions.at(b);
					const int value_c = parameter_mode3 == parameter_mode::immediate ? c : instructions.at(c);

					if (value_a == value_b)
					{
						instructions.at(c) = 1;
					}
					else
					{
						instructions.at(c) = 0;
					}

					instruction_pointer += 4;

					break;
				}
				case 99:
					is_halted = true;
					break;
				}

				
			} while (!is_halted);

			return last_output_value;
		}
	};
}

bool aoc_2019_1::part1()
{
	auto file = open_input_file(2019, 1);

	std::vector<int> module_masses;

	int mass;

	while (file >> mass)
	{
		module_masses.push_back(mass);
	}

	int total_fuel = 0;

	for (const int module_mass : module_masses)
	{
		total_fuel += static_cast<int>(std::floor(module_mass / 3.0)) - 2;
	}

	return total_fuel == 3268951;
}

bool aoc_2019_1::part2()
{
	auto file = open_input_file(2019, 1);

	std::vector<int> module_masses;

	int mass;

	while (file >> mass)
	{
		module_masses.push_back(mass);
	}

	int total_fuel = 0;

	for (const int module_mass : module_masses)
	{
		total_fuel += fuel_required(module_mass);
	}

	return total_fuel == 4900568;
}

bool aoc_2019_2::part1()
{
	auto file = open_input_file(2019, 2);

	std::vector<int> instructions = IntcodeComputer::load_instructions(file);
	
	instructions.at(1) = 12;
	instructions.at(2) = 2;

	auto computer = IntcodeComputer{ instructions };

	computer.run({});

	return computer.instructions.at(0) == 3850704;
}

bool aoc_2019_2::part2()
{
	auto file = open_input_file(2019, 2);

	const auto initial_instructions = IntcodeComputer::load_instructions(file);

	for (int noun = 0; noun <= 99; noun++)
	{
		for (int verb = 0; verb <= 99; verb++)
		{
			std::vector<int> instructions = initial_instructions;
			instructions.at(1) = noun;
			instructions.at(2) = verb;

			auto computer = IntcodeComputer{ instructions };

			computer.run({});

			if (computer.instructions.at(0) == 19690720)
			{
				return (100 * noun + verb) == 6718;
			}
		}
	}

	return false;
}

bool aoc_2019_5::part1()
{
	auto file = open_input_file(2019, 5);

	auto computer = IntcodeComputer(file);
	
	return computer.run({ 1 }) == 12428642;
}

bool aoc_2019_5::part2()
{
	auto file = open_input_file(2019, 5);

	auto computer = IntcodeComputer(file);

	return computer.run({ 5 }) == 918655;
}
