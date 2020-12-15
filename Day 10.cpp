// Day 10.cpp : This file contains the 'main' function. Program execution begins and ends there.
//


#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <algorithm>
#include <unordered_map>
#include <set>
#include <functional>


constexpr int MAX_VOLT_DIFF = 3;

int main()
{
	//read the input
	std::vector<int> input_list;
	int line;
	std::ifstream input_file( "input.txt" );
	if ( input_file.is_open() )
	{
		input_list.push_back( 0 );
		while ( input_file >> line )
		{
			input_list.push_back( line );
		}

		std::sort( input_list.begin(), input_list.end() );

		const int built_in_voltage = input_list[input_list.size() - 1] + MAX_VOLT_DIFF;
		input_list.push_back( built_in_voltage );

		//map for part 1
		std::unordered_map<int, int> volt_dif_totals;

		//vector of diffs for part 2
		int current_volt = 0;
		for ( const auto int_val : input_list )
		{
			if ( !int_val )
			{
				continue;
			}
			
			if ( int_val > current_volt && int_val <= current_volt + MAX_VOLT_DIFF )
			{
				volt_dif_totals[int_val - current_volt]++;
				current_volt = int_val;
			}
			else
			{
				std::cout << "ERROR! No valid voltage adapter to move to!" << std::endl;
				break;
			}
		}

		std::cout << "=======================PART 1===============================" << std::endl;
		std::cout << "output_value: " << volt_dif_totals[1] * volt_dif_totals[3] << std::endl;

		std::vector<size_t> possible_paths_reached( input_list.size() );

		//for each adapter we need a list of how many adaptors paths can reach that one
		//this is the sum of all the previous adaptor counts that can reach this one
		for ( int idx = 0; idx < input_list.size(); ++idx )
		{
			if ( idx == 0 )
			{
				possible_paths_reached[idx] = 1;
			}
			else
			{
				const int current_val = input_list[idx];
				size_t count = 0;
				for ( int jdx = idx - 1; jdx >= 0; --jdx )
				{
					if ( input_list[jdx] + MAX_VOLT_DIFF >= current_val )
					{
						count += possible_paths_reached[jdx];
					}
					else
					{
						break;
					}
				}
				possible_paths_reached[idx] = count;
			}
		}

		std::cout << "=======================PART 2===============================" << std::endl;
		std::cout << "unique vals: " << possible_paths_reached[possible_paths_reached.size() - 1] << std::endl;
	}
}


