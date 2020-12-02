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
	//first take the number that we want to reach as input
	constexpr int input_number = 2020;

	//now read the input file and sort the values into buckets based upon the input number
	using VALUE_MAP = std::map<int, int>;
	using VALUE_VECTOR = std::vector<int>;

	
	//PART 1 variables
	VALUE_MAP lower_half;
	VALUE_MAP upper_half;

	//PART 2 variables
	VALUE_VECTOR values;

	//read the input
	int line;
	std::ifstream input_file( "input.txt" );
	if ( input_file.is_open() )
	{
		while ( input_file >> line )
		{
			//for part 1 we split into 2 maps, depending on whether the value is > or < half the input number, so we can limit the amount of iterations we need
			//if our first number is in one map, we know the other number must be in the other map in order to match our criteria
			if ( (float)line < (input_number / 2.f) )
			{
				lower_half.insert( std::pair<int, int>( line, 1 ) );
			}
			else
			{
				upper_half.insert( std::pair<int, int>( line, 1 ) );
			}

			//for part 2 just store in a vector
			values.push_back( line );
		}
		input_file.close();
	}

	auto find_matching_pair = []( const VALUE_MAP& map_a, const VALUE_MAP& map_b, const int input_number )
	{
		for ( const auto& it : map_a )
		{
			const int val1 = it.first;
			//val 2 is the difference between our first number and the input number we need to match
			const int val2 = input_number - val1;

			//check our map for the key of val2
			if ( map_b.find( val2 ) != map_b.end() )
			{
				std::cout << "Pair found!" << std::endl;
				std::cout << "Value 1: " << val1 << "    Value 2: " << val2 << std::endl;
				std::cout << "Multiplied Together: " << val1 * val2 << std::endl;
				return;
			}
		}
	};


	std::cout << "=======================PART 1=========================" << std::endl;
	//we take whichever map is smallest as our main input to limit iterations
	if ( lower_half.size() > upper_half.size() )
	{
		find_matching_pair( upper_half, lower_half, input_number );
	}
	else
	{
		find_matching_pair( lower_half, upper_half, input_number );
	}



	std::cout << "=======================PART 2=========================" << std::endl;

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
			//array is in ascending order, so can break out of this loop once we go over the target, as any subsequent value will also be over
			if ( value1 + value2 > input_number )
				break;

			for ( size_t k = j + 1; k < values.size(); ++k )
			{
				const int value3 = values[k];
				//array is in ascending order, so can break out of this loop once we go over the target, as any subsequent value will also be over
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
