// Day6.cpp : This file contains the 'main' function. Program execution begins and ends there.
//
#include <iostream>
#include <fstream>
#include <string>
#include <algorithm>
#include <map>

int main()
{
	std::string line;
	std::ifstream input_file( "input.txt" );
	if ( input_file.is_open() )
	{
		auto caclulate_unique_chars = []( std::string char_string ) -> int
		{
			//sort the chars for ease in removing duplicates
			std::sort( char_string.begin(), char_string.end() );

			//remove duplicates and get the count of unique chars
			return std::unique( char_string.begin(), char_string.end() ) - char_string.begin();
		};
		
		auto caclulate_chars_that_match_total = []( std::string char_string, const int total  ) -> int
		{
			std::map<char, int> set_of_chars;

			for ( const auto character : char_string )
			{
				set_of_chars[character]++;
			}

			int total_that_match = 0;

			for ( const auto char_total : set_of_chars )
			{
				if ( char_total.second == total )
					++total_that_match;
			}

			return total_that_match;
		};


		int count = 0;
		int count_part_2 = 0;
		std::string full_string;
		int people_in_set = 0;
		while ( std::getline( input_file, line ) )
		{
			if ( !line.empty() )
			{
				full_string += line;
				++people_in_set;
			}
			else
			{
				//calculate line
				count += caclulate_unique_chars( full_string );
				count_part_2 += caclulate_chars_that_match_total( full_string, people_in_set );

				//reset for next group
				full_string = "";
				people_in_set = 0;
			}
		}

		if ( !full_string.empty() )
		{
			//calculate line
			count += caclulate_unique_chars( full_string );
			count_part_2 += caclulate_chars_that_match_total( full_string, people_in_set );
		}


		std::cout << "===================PART 1===============================" << std::endl;
		std::cout << "Total count:" << count << std::endl;

		std::cout << "===================PART 2===============================" << std::endl;
		std::cout << "Total count:" << count_part_2 << std::endl;
	}

}
