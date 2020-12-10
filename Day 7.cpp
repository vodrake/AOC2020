// Day 7.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <limits>
#include <algorithm>
#include <map>
#include <set>
#include <sstream>


using ID_HASH = size_t;
ID_HASH SHINY_GOLD_ID = std::hash<std::string>{} ("shiny gold");

struct COLOURED_BAG
{
	COLOURED_BAG( ID_HASH _hash ) : m_id( _hash ) {}
	std::vector<std::pair<ID_HASH, int>> m_contained_bags;
	ID_HASH m_id{ 0 };
	int  m_total_contained = 0;
	bool m_can_contain_gold_bag = false;
};

std::map<ID_HASH, COLOURED_BAG> m_bags;


ID_HASH create_hash_of_bag_colour( const std::string bag_colour ) {	return  std::hash<std::string>{} (bag_colour); }

void add_bag( const COLOURED_BAG&& bag ) 
{ 
	m_bags.emplace( bag.m_id, bag ); 
}

bool can_bag_contain_gold_bag( const ID_HASH bag_id, int& total_bags_containe )
{	
	const auto& it = m_bags.find( bag_id );
	if ( it != m_bags.end() )
	{
		auto& bag = it->second;

		//then check if we've already flagged this bag at some other point in our iteration
		if ( bag.m_total_contained )
		{
			total_bags_containe += bag.m_total_contained;
			return bag.m_can_contain_gold_bag;
		}

		//else iterate through the bag contained in this bag, set our flag if it returns true so we dont need to iterate again
		bool can_contain = false;
		for ( const auto& bag_item : bag.m_contained_bags )
		{
			//if this bag is the shiny gold bag, then we can contain
			if ( bag_item.first == SHINY_GOLD_ID )
				can_contain = true;

			int temp_bags_contained = 0;
			can_contain |= can_bag_contain_gold_bag( bag_item.first, temp_bags_contained );

			//set the number of  bags contained so we dont need to calculate again
			total_bags_containe += bag_item.second + (bag_item.second * temp_bags_contained);
		}

		bag.m_total_contained = total_bags_containe;
		bag.m_can_contain_gold_bag = can_contain;
		return can_contain;
		
	}
	return false;
}

int main()
{
	std::string line;
	std::ifstream input_file( "input.txt" );

	//read in all of our bag types
	if ( input_file.is_open() )
	{
		while ( std::getline( input_file, line ) )
		{
			const auto bags_pos = line.find( " bags" );
			const auto colour = line.substr( 0, bags_pos );

			//after the first bags we always have "bags  contain ", so can remove that
			line.erase( 0, bags_pos + std::string( "bags contain " ).size() );

			auto bag = COLOURED_BAG{ create_hash_of_bag_colour( colour ) };

			//check for special case where it contains no other bags, else ignore
			if (line.find("no other") == std::string::npos )
			{
				//replace , with a character we can easily split on
				const std::string DELIMITERS = ",";
				for ( auto& it : line )
				{
					if ( DELIMITERS.find( it ) != std::string::npos )
					{
						it = '.';
					}
				}

				std::istringstream  stStream( line );
				std::string next_bag_string;
				while ( std::getline( stStream, next_bag_string, '.' ) )
				{
					if ( next_bag_string[0] == ' ' )
						next_bag_string.erase( 0,  1 );

					//first is our number
					const auto num_pos = next_bag_string.find( " " );
					const int number = std::stoi( next_bag_string.substr( 0, num_pos ) );
					next_bag_string.erase( 0, num_pos + 1 );

					//then the next words after are the colour
					const auto sub_bags_pos = next_bag_string.find( " bag" );
					const auto sub_colour = next_bag_string.substr( 0, sub_bags_pos );

					bag.m_contained_bags.push_back( { create_hash_of_bag_colour( sub_colour ), number } );
				}
			}

			add_bag( std::move( bag ) );
		}
	}

	int shiny_count = 0;

	for ( const auto& bag : m_bags )
	{
		int total_bags_containe = 0;
		if ( can_bag_contain_gold_bag( bag.first, total_bags_containe ) )
			++shiny_count;
	}

	std::cout << "===================PART 1===============================" << std::endl;
	std::cout << "Bags which can contain Shiny Gold:" << shiny_count << std::endl;

	//part 2 just check shiny gold, we've already done the calculations so we just need to fetch the right bag
	const auto& it = m_bags.find( SHINY_GOLD_ID );
	if ( it != m_bags.end() )
	{
		std::cout << "===================PART 2===============================" << std::endl;
		std::cout << "Shiny Gold contains:" << it->second.m_total_contained << " bags" << std::endl;
	}
}


