// Day 12.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <fstream>
#include <string>
#include <vector>


constexpr int WAYPOINT_START_X = 10;
constexpr int WAYPOINT_START_Y = 1;

enum class DIRECTION : int
{
	EAST,
	SOUTH,
	WEST,
	NORTH
};

void move_in_direction( const DIRECTION direction, const int val_to_move, int& x_pos, int& y_pos )
{
	switch ( direction )
	{
	case DIRECTION::EAST:
		x_pos += val_to_move;
		break;
	case DIRECTION::WEST:
		x_pos -= val_to_move;
		break;
	case DIRECTION::NORTH:
		y_pos += val_to_move;
		break;
	case DIRECTION::SOUTH:
		y_pos -= val_to_move;
		break;
	}
}
int mod( int x, int m ) 
{
	return (x % m + m) % m;
}


int part_1( const std::vector<std::string>& data_list)
{	
	int x_pos = 0;
	int y_pos = 0;
	DIRECTION curr_dir = DIRECTION::EAST;
	for ( const auto& line : data_list )
	{

		const char instr_id = line[0];
		const int val = std::stoi( line.substr( 1 ) );

		switch ( instr_id )
		{
		case 'R':
			{
				//rotate
				const int no_dir_changes = val / 90;
				curr_dir = static_cast<DIRECTION>(mod( static_cast<int>(curr_dir) + no_dir_changes, 4 ));
				break;
			}
		case 'L':
			{
				//rotate
				const int no_dir_changes = val / 90;
				curr_dir = static_cast<DIRECTION>(mod( static_cast<int>(curr_dir) - no_dir_changes, 4 ));
				break;
			}
		case 'F':
			{
				//move in the direction faced
				move_in_direction( curr_dir, val, x_pos, y_pos );
				break;
			}
		case 'N':
			{
				y_pos += val;
				break;
			}
		case 'S':
			{
				y_pos -= val;
				break;
			}
		case 'E':
			{
				x_pos += val;
				break;
			}
		case 'W':
			{
				x_pos -= val;
				break;
			}
		}
	}
	 return std::abs( x_pos ) + std::abs( y_pos );
}

int part_2( const std::vector<std::string>& data_list, const int waypoint_start_x, const int waypoint_start_y )
{	
	int ship_x_pos = 0;
	int ship_y_pos = 0;	
	
	int waypoint_x_pos = waypoint_start_x;
	int waypoint_y_pos = waypoint_start_y;

	for ( const auto& line : data_list )
	{

		const char instr_id = line[0];
		const int val = std::stoi( line.substr( 1 ) );

		switch ( instr_id )
		{
		case 'R':
		case 'L':
			{
				//rotate
				int no_dir_changes = val / 90;
				//flip this around if we're going left to cause the opposite reaction for 1 and 3
				no_dir_changes = instr_id == 'L' ? 4 - no_dir_changes : no_dir_changes;
				switch ( no_dir_changes )
				{
				case 1:
					{
						const int temp_x = waypoint_x_pos;
						waypoint_x_pos = waypoint_y_pos;
						//with the direction set up, with 1 rotation the y pos will always be the opposite sign
						waypoint_y_pos = temp_x * -1;

						break;
					}
				case 2:
					{
						//flip the signs on both
						waypoint_x_pos = waypoint_x_pos * -1;
						waypoint_y_pos = waypoint_y_pos * -1;
						break;
					}
				case 3:
					{
						const int temp_x = waypoint_x_pos;
						//with the direction set up, with 1 rotation the x pos will always be the opposite sign
						waypoint_x_pos = waypoint_y_pos * -1;
						waypoint_y_pos = temp_x;
						break;
					}
				default:
					break;
				}
				break;
			}
		case 'F':
			{
				//move in the direction faced
				ship_x_pos += (val * waypoint_x_pos);
				ship_y_pos += (val * waypoint_y_pos);
				break;
			}
		case 'N':
			{
				waypoint_y_pos += val;
				break;
			}
		case 'S':
			{
				waypoint_y_pos -= val;
				break;
			}
		case 'E':
			{
				waypoint_x_pos += val;
				break;
			}
		case 'W':
			{
				waypoint_x_pos -= val;
				break;
			}
		}
	}
	 return std::abs( ship_x_pos ) + std::abs( ship_y_pos );
}


int main()
{
	//read the input
	std::string line;
	std::ifstream input_file( "input.txt" );
	if ( input_file.is_open() )
	{
		std::vector<std::string> our_data;
		//build our map
		while ( input_file >> line )
		{
			our_data.push_back( line );
		}

		std::cout << "=======================PART 1===============================" << std::endl;
		std::cout << "manhattan distance: " << part_1( our_data ) << std::endl;


		std::cout << "=======================PART 2===============================" << std::endl;
		std::cout << "manhattan distance: " << part_2( our_data, WAYPOINT_START_X, WAYPOINT_START_Y ) << std::endl;
	}
}
