// Day 5.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <limits>
#include <algorithm>


int main()
{
	std::vector<std::string> seat_list;
	std::string line;
	std::ifstream input_file( "input.txt" );
	if ( input_file.is_open() )
	{
		std::string full_passport_string;

		while ( std::getline( input_file, line ) )
		{
			seat_list.push_back( line );
		}


		auto parse_string_to_get_position_in_range = []( const std::string& str, int min, int max, const char min_token, const char max_token ) -> int
		{
			int pos = -1;

			//break out if our min is greater than equal to our max 
			if ( min >= max )
				return pos;

			//loop through all chars to narrow down our range
			for ( const auto& str_char : str )
			{
				if ( str_char == min_token )
				{
					max -= ( (max - min) + 1 )/ 2;
				}
				else if ( str_char == max_token )
				{
					min += ((max - min) + 1) / 2;
				}
			}
			return min;
		};


		//now loop through our seat list and find the highest ID
		std::vector<int> id_list;
		int max_id = std::numeric_limits<int>::min();
		for ( const auto& seat : seat_list )
		{

			if ( seat.size() == 10 )
			{
				const std::string row_string = seat.substr( 0, 7 );
				const std::string col_string = seat.substr( 7, 3 );

				const int row_pos = parse_string_to_get_position_in_range( row_string, 0, 127, 'F', 'B' );
				const int col_pos = parse_string_to_get_position_in_range( col_string, 0, 7, 'L', 'R' );

				if ( row_pos == -1 || col_pos == -1 )
					continue;

				const int ID = (row_pos * 8) + col_pos;
				max_id = std::max( max_id, ID );

				//for part 2
				id_list.push_back( ID );
			}
		}

		std::cout << "===================PART 1===============================" << std::endl;
		std::cout << "Maximum ID:" << max_id << std::endl;


		//sort our id's to make looping through easier
		std::sort ( id_list.begin(), id_list.end());


		//PART 2
		//these 2 mark the search bounds for our seat
		constexpr int first_row_max_id = 7 + 1;
		constexpr int last_row_min_id =  127 * 8 + 1;

		int missing_id = 0;
		for ( size_t idx = 2; idx < id_list.size()- 3; ++idx )
		{
			const int id = id_list[idx];
			const int previous_id = id_list[idx - 1];
			const int nexts_id = id_list[idx + 1];

			if ( id > first_row_max_id && id < last_row_min_id )
			{
				//check if we've skipped an ID
				if ( id != previous_id + 1 )
				{
					missing_id = id - 1;
				}
				else if ( id != nexts_id - 1 )
				{
					missing_id = id + 1;
				}
			}
		}


		std::cout << "===================PART 2===============================" << std::endl;
		std::cout << "Missing ID:" << missing_id << std::endl;
	}
}
