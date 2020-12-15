// Day 11.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <functional>

using SEAT_ROW = std::vector<char>;
using SEAT_MAP = std::vector<SEAT_ROW>;

constexpr char UNOCUPIED_CHAR = 'L';
constexpr char OCUPIED_CHAR = '#';
constexpr char EMPTY_CHAR = '.';

int main()
{
	//read the input
	SEAT_MAP map_of_seats;
	std::string line;
	std::ifstream input_file( "input.txt" );
	if ( input_file.is_open() )
	{
		//build our map
		while ( input_file >> line )
		{
			SEAT_ROW row;
			for ( const auto seat : line )
			{
				row.push_back( seat );
			}
			map_of_seats.push_back( row );
		}


		//for part 1, just check the 8 seats surrounding the given seat
		auto count_number_of_adjacent_seats_occupied_part1 = []( const SEAT_MAP& map_to_read,  const int x_indx, const int y_indx ) -> int
		{
			int count = 0;
			for ( int y = y_indx - 1; y <= y_indx + 1; ++y )
			{
				for ( int x = x_indx - 1; x <= x_indx + 1; ++x )
				{
					if ( ( x != x_indx || y != y_indx ) && ( y >= 0 && y < map_to_read.size()) &&
						 (x >= 0 && x < map_to_read[y].size()) )
					{
						count += map_to_read[y][x] == OCUPIED_CHAR ? 1 : 0;
					}
				}
			}
			return count;
		};

		//for part 2 we keep moving in one of our given directions until we kit a seat, or reach the end of the map
		//we start at our given point and move out from there
		auto count_number_of_adjacent_seats_occupied_part2 = []( const SEAT_MAP& map_to_read, const int x_indx, const int y_indx ) -> int
		{
			auto hits_occupied_seat_in_given_vector = [&map_to_read]( int x_indx, int y_indx, const int x_dir, const int y_dir ) -> int
			{
				x_indx += x_dir;
				y_indx += y_dir;

				//keep moving in the given direction until we hit a seat or the edge of the map
				while ( x_indx >= 0 && x_indx < (int)map_to_read[0].size() &&
						y_indx >= 0 && y_indx < (int)map_to_read.size() )
				{
					if ( map_to_read[y_indx][x_indx] == OCUPIED_CHAR )
					{
						return 1;
					}
					else if ( map_to_read[y_indx][x_indx] == UNOCUPIED_CHAR )
					{
						return 0;
					}

					x_indx += x_dir;
					y_indx += y_dir; 
				}
				return 0;
			};

			int count = 0;

			count += hits_occupied_seat_in_given_vector( x_indx, y_indx, 0, 1 );
			count += hits_occupied_seat_in_given_vector( x_indx, y_indx, 1, 0 ); 
			count += hits_occupied_seat_in_given_vector( x_indx, y_indx, 0, -1 );
			count += hits_occupied_seat_in_given_vector( x_indx, y_indx, -1, 0 );
			count += hits_occupied_seat_in_given_vector( x_indx, y_indx, -1, -1 );
			count += hits_occupied_seat_in_given_vector( x_indx, y_indx, 1, 1 );
			count += hits_occupied_seat_in_given_vector( x_indx, y_indx, -1, 1 );
			count += hits_occupied_seat_in_given_vector( x_indx, y_indx, 1, -1 );
			return count;
		};

		auto run_seat_swapper = [&map_of_seats]( std::function<int( const SEAT_MAP&,int,int)> count_function, const int MIN_SEATS_UNOCCUPIED ) -> int
		{
			auto lambda_set_map = map_of_seats;
			bool has_changed = false;
			do
			{
				has_changed = false;
				//create our temp new seat of seating
				SEAT_MAP temp_seats_map = lambda_set_map;

				//iterate over every seat in our map
				for ( int y_idx = 0; y_idx < temp_seats_map.size(); ++y_idx )
				{
					SEAT_ROW& curr_row = temp_seats_map[y_idx];
					for ( int x_idx = 0; x_idx < curr_row.size(); ++x_idx )
					{
						//count the number of adjacent occupied seats using our provided function
						const int adj_count = count_function( lambda_set_map, x_idx, y_idx );
						char& curr_char = curr_row[x_idx];

						//flip occupied or unoccupied seats if they match our criteria
						if ( curr_char == UNOCUPIED_CHAR && adj_count == 0 )
						{
							curr_char = OCUPIED_CHAR;
							has_changed = true;
						}
						else if ( curr_char == OCUPIED_CHAR && adj_count >= MIN_SEATS_UNOCCUPIED )
						{
							curr_char = UNOCUPIED_CHAR;
							has_changed = true;
						}
					}
				}

				//set our changed set of seats onto our main one now
				lambda_set_map = temp_seats_map;
			}
			while ( has_changed );

			//count map of seats occupied count
			int count = 0;
			for ( size_t y_idx = 0; y_idx < lambda_set_map.size(); ++y_idx )
			{
				SEAT_ROW& curr_row = lambda_set_map[y_idx];
				for ( size_t x_idx = 0; x_idx < curr_row.size(); ++x_idx )
				{
					count += curr_row[x_idx] == OCUPIED_CHAR ? 1 : 0;
				}
			}
			return count;
		};

		std::cout << "=======================PART 1===============================" << std::endl;
		std::cout << "output_value: " << run_seat_swapper( count_number_of_adjacent_seats_occupied_part1, 4 ) << std::endl;

		std::cout << "=======================PART 2===============================" << std::endl;
		std::cout << "output_value: " << run_seat_swapper( count_number_of_adjacent_seats_occupied_part2, 5 ) << std::endl;
	}
}
