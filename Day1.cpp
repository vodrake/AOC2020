// Day1.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <fstream>
#include <string>
#include <map>
#include <vector>
#include <algorithm>

int main()
{
	constexpr int input_number = 2020;
	//first take the number that we want to reach as input
	std::cout << "Please insert the number you are looking for: " << std::endl;
	std::cin >> input_number;

	//now read the input file and sort the values into buckets based upon the input number
	using VALUE_MAP = std::map<int, int>;
	using VALUE_VECTOR = std::vector<int>;

/*	
	//PART 1 
	VALUE_MAP lower_half;
	VALUE_MAP upper_half;

	int line;
	std::ifstream input_file( "input.txt" );
	int total_fuel = 0;
	if ( input_file.is_open() )
	{
		while ( input_file >> line )
		{
			if ( (float)line < (input_number / 2.f) )
			{
				lower_half.insert( std::pair<int,int>( line, 1 ) );
			}
			else
			{
				upper_half.insert( std::pair<int, int>( line, 1 ) );
			}
		}
		input_file.close();


		auto find_matching_pair = []( const VALUE_MAP& map_a, const VALUE_MAP& map_b, const int input_number )
		{
			for ( const auto& it : map_a )
			{
				const int val1 = it.first;
				const int val2 = input_number - val1;
				if ( map_b.find( val2 ) != map_b.end() )
				{
					std::cout << "Pair found!" << std::endl;
					std::cout << "Value 1: " << val1 << "    Value 2: " << val2 << std::endl;
					std::cout << "Multiplied Together: " << val1 * val2 << std::endl;
					return;
				}
			}

		};

		if ( lower_half.size() > upper_half.size() )
		{
			find_matching_pair( upper_half, lower_half, input_number );
		}
		else
		{
			find_matching_pair( lower_half, upper_half, input_number );
		}
	} */

	//PART 2 
	VALUE_VECTOR values;

	int line;
	std::ifstream input_file( "input.txt" );
	int total_fuel = 0;
	if ( input_file.is_open() )
	{
		while ( input_file >> line )
		{
			values.push_back( line );
		}

		input_file.close();

		//sort the vector, makes it easier later to determine when we can stop iterating through the array (as the numbers become too large)
		std::sort( values.begin(), values.end(), []( int a, int b ) { return a < b; } );

		for (  size_t i = 0; i < values.size(); ++i )
		{
			const int value1 = values[i];
			if ( value1 > input_number )
			{
				std::cout << "We found no solution for this input number!" << std::endl;
				break;
			}

			for ( size_t j = i + 1; j < values.size(); ++j )
			{
				const int value2 = values[j];
				if ( value1 + value2 > input_number )
					break;

				for ( size_t k = j + 1; k < values.size(); ++k )
				{
					const int value3 = values[k];
					if ( value1 + value2 + value3 > input_number )
						break;

					if ( value1 + value2 + value3 == input_number )
					{
						std::cout << "Trips found!" << std::endl;
						std::cout << "Value 1: " << value1 << "    Value 2: " << value2 << "    Value 3: " << value3 << std::endl;
						std::cout << "Multiplied Together: " << value1 * value2 * value3 << std::endl;
						return 0;
					}
				}

			}
		}
	} 
}
