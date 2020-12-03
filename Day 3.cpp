// Day 3.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <sstream>

	//variables
struct POINT
{
	int x;
	int y;

	POINT& operator+= ( const POINT& rhs ) { x += rhs.x; y += rhs.y; return *this; }
};

constexpr int GROUND_TILE = 0;
constexpr int  TREE_TILE = 1;

using MAP_ROW = std::vector<int>;
using MAP = std::vector<MAP_ROW>;

//PART 1
const POINT PART_1_SLOPE_1{ 3, 1 };
//PART 2
const POINT PART_2_SLOPE_1{ 1, 1 };
const POINT PART_2_SLOPE_2{ 3, 1 };
const POINT PART_2_SLOPE_3{ 5, 1 };
const POINT PART_2_SLOPE_4{ 7, 1 };
const POINT PART_2_SLOPE_5{ 1, 2 };

//now move down until we reach the bottom of the map, incrementing every time we hit a tree tile
template<class T>
T trees_hit_on_slope( const MAP& map, const POINT& movement_vector )
{
	T total_trees = 0;
	POINT current_position{ 0, 0 };
	while ( current_position.y < (int)map.size() )
	{
		const MAP_ROW& current_row = map[current_position.y];
		//if we go off the x axis of the map, we wrap round to the start again
		const int wrapped_x = current_position.x % (current_row.size());

		if ( current_row[wrapped_x] == TREE_TILE )
			++total_trees;

		current_position += movement_vector;
	}
	return total_trees;
}

int main()
{
	std::string line;
	std::ifstream input_file( "input.txt" );
	if ( input_file.is_open() )
	{
		std::vector<MAP_ROW> map;
		while ( std::getline( input_file, line ) )
		{
			//build our map
			MAP_ROW map_row;
			for ( const auto& cell : line )
			{
				// for . on map add 0, for # add 1
				map_row.push_back( cell == '.' ? GROUND_TILE : TREE_TILE );
			}
			map.push_back( std::move( map_row ) );
		}

		//PART 1 
		std::cout << "=================PART 1=========================" << std::endl;
		std::cout << "Number of trees hit: " << trees_hit_on_slope<int>(map, PART_1_SLOPE_1)  << std::endl;

		//PART 2
		//need to make them all 64 bit ints so we don't get any overflow when multiplying together
		const uint64_t total1 = trees_hit_on_slope<uint64_t>( map, PART_2_SLOPE_1 );
		const uint64_t total2 = trees_hit_on_slope<uint64_t>( map, PART_2_SLOPE_2 );
		const uint64_t total3 = trees_hit_on_slope<uint64_t>( map, PART_2_SLOPE_3 );
		const uint64_t total4 = trees_hit_on_slope<uint64_t>( map, PART_2_SLOPE_4 );
		const uint64_t total5 = trees_hit_on_slope<uint64_t>( map, PART_2_SLOPE_5 );

		std::cout << "=================PART 2=========================" << std::endl;
		std::cout << "Number of trees hit multiplied: " << ((((total1 * total2) * total3) * total4) * total5) << std::endl;
	}
}


