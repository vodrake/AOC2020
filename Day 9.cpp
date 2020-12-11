// Day 9.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <algorithm>
#include <numeric>

constexpr size_t PREAMBLE_VALUE = 25;

int main()
{
	std::string line;
	std::ifstream input_file( "input.txt" );

	std::vector<int64_t> numbers_list;

	//read in all of our bag types
	if ( input_file.is_open() )
	{
		while ( std::getline( input_file, line ) )
		{
			numbers_list.push_back( std::stoll( line ) );
		}
	}


	auto can_find_sum_of_two_numbers = [&numbers_list]( const int64_t number_to_match, const size_t idx_range_end ) -> bool
	{
		for ( size_t top_idx = idx_range_end - PREAMBLE_VALUE; top_idx < idx_range_end; ++top_idx )
		{
			for ( size_t bottom_idx = top_idx + 1; bottom_idx < idx_range_end; ++bottom_idx )
			{
				if ( numbers_list[top_idx] + numbers_list[bottom_idx] == number_to_match )
				{
					return true;
				}

			}
		}
		return false;
	};

	auto find_contiguous_range_that_matches_input_no = [&numbers_list]( const int64_t number_to_match ) -> std::vector<int64_t>
	{
		if ( numbers_list.size() )
		{
			//we want to find a contiguous range from our array that sum up to match our output
			size_t first_index = 0;
			int64_t count = numbers_list[first_index];
			for ( size_t bottom_idx = first_index + 1; bottom_idx < numbers_list.size(); ++bottom_idx )
			{
				//loop through summing all the values from first to bottom up
				count += numbers_list[bottom_idx];

				//once we go over the number, we need to start moving the first index up and removing those values from the start to get back under
				if ( count > number_to_match )
				{
					//we move the first index forward until we're back under our limit again
					do
					{
						count -= numbers_list[first_index++];
					}
					while ( count > number_to_match && first_index < bottom_idx );
				}

				if ( count == number_to_match )
				{
					return std::vector <int64_t>{numbers_list.begin() + first_index, numbers_list.begin() + bottom_idx};
				}
			}
		}
		return  std::vector<int64_t>();
	};

	int64_t part1_value = 0;
	for ( size_t idx = PREAMBLE_VALUE; idx < numbers_list.size(); ++idx )
	{
		const int64_t number_to_match = numbers_list[idx];

		if ( !can_find_sum_of_two_numbers( number_to_match, idx) )
		{
			part1_value = number_to_match;
			break;
		}

	}

	std::cout << "===================PART 1===============================" << std::endl;
	std::cout << "Number which fails fist:" << part1_value << std::endl;

	//get our subvector range that sums up to our part 1 value
	auto sub_vector = find_contiguous_range_that_matches_input_no( part1_value );

	//sort the vector so we can get the highest and lowest value
	std::sort( sub_vector.begin(), sub_vector.end() );

	if ( sub_vector.size() > 1 )
	{
		std::cout << "===================PART 2===============================" << std::endl;
		std::cout << "Magic number:" << sub_vector[0] + sub_vector[sub_vector.size() - 1] << std::endl;
	}
	else
	{
		std::cout << "Oops we've had a Part 2 error!" << std::endl;
	}
}
