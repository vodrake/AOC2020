// Day 8.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <sstream>

struct INSTRUCTION
{
	std::string m_instr_type;
	int16_t		m_instr_value = 0;
	bool		m_has_been_visited = false;
	bool		m_has_tried_swapping = false;
};



int main()
{
	std::string line;
	std::ifstream input_file( "input.txt" );

	std::vector<INSTRUCTION> instruction_list;

	//read in all of our bag types
	if ( input_file.is_open() )
	{
		while ( std::getline( input_file, line ) )
		{
			INSTRUCTION new_inst;

			std::istringstream  stStream( line );
			std::string line_instr_typee;
			std::string line_value;

			std::getline( stStream, line_instr_typee, ' ' );
			std::getline( stStream, line_value, ' ' );

			new_inst.m_instr_type = line_instr_typee;
			new_inst.m_instr_value = std::stoi( line_value );

			instruction_list.push_back( std::move( new_inst ) );
		}
	}


	auto run_instruction_set = [&instruction_list](  const bool can_flip_instruction ) -> int
	{
		do 
		{
			//reset each loop
			for ( auto& instr : instruction_list )
			{
				instr.m_has_been_visited = false;
			}

			int accumulator = 0;
			size_t cmd_pos = 0;
			bool has_flipped_in_iter = false;

			while ( true )
			{
				//for part 2 return once we've hit a loop that visits the last instruction and then carries on past the array
				if ( can_flip_instruction && has_flipped_in_iter && cmd_pos == instruction_list.size() )
				{
					return accumulator;
				}

				INSTRUCTION& inst = instruction_list[cmd_pos];
				// for part 1we keep looping until we hit a node for the second time
				//for part 2 if we reach a loop, then we move on to trying to flip another inst
				if ( inst.m_has_been_visited )
				{
					if ( can_flip_instruction )
					{
						break;
					}
					else
					{
						return accumulator;
					}
				}

				std::string instr_type = inst.m_instr_type;
				const int instr_value = inst.m_instr_value;
				//if we can, for part 2, try flipping one (and only one!) of our jmp or nop operations to see if we can hit the end instruction
				if ( can_flip_instruction && !has_flipped_in_iter && !inst.m_has_tried_swapping && (instr_type == "jmp" || instr_type == "nop" ) )
				{
					if ( instr_type == "jmp" )
						instr_type = "nop";
					else if ( instr_type == "nop" )
						instr_type = "jmp";

					has_flipped_in_iter = true;
					inst.m_has_tried_swapping = true;
				}

				inst.m_has_been_visited = true;
				if ( instr_type == "jmp" )
				{
					cmd_pos += instr_value;
					continue;
				}
				else if ( instr_type == "acc" )
				{
					accumulator += instr_value;
				}

				++cmd_pos;
			}
		}
		while ( can_flip_instruction );

		return 0;
	};
	
	int accumulator_part1 = run_instruction_set(  false );

	std::cout << "===================PART 1===============================" << std::endl;
	std::cout << "Accumulator before loop:" << accumulator_part1 << std::endl;

	int accumulator_part2 = run_instruction_set(  true );
	std::cout << "===================PART 2===============================" << std::endl;
	std::cout << "Accumulator when hitting last instruction:" << accumulator_part2 << std::endl;
}

