// Day 4.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <sstream>

constexpr int8_t NULL_VALUE = 0;

struct PASSPORT_DATA
{
	std::string		passport_id;
	std::string		country_id ;
	std::string		height;
	std::string		hair_colour;
	std::string		eye_colour;
	std::string		birth_year;
	std::string		issue_year;
	std::string		expiration_year;

	//nine digit number
	bool	is_passport_id_valid() const { return  passport_id.size() == 9 && passport_id.find_first_not_of( "0123456789" ) == std::string::npos;	}

	//must be # followed by exactly 6 chars or number 0 - 9 a-f
	bool	is_hair_colour_valid() const
	{
		if ( hair_colour.size() == 7 && hair_colour[0] == '#')
		{
			//ensure rest of string is only digits or a - f
			std::string splt_str = hair_colour.substr( 1, hair_colour.size() );
			return splt_str.find_first_not_of( "0123456789abcdef" ) == std::string::npos;
		}
		return false;
	}

	//must be one of amb blu brn gry grn hzl oth
	bool is_eye_colour_valid() const {	return eye_colour == "amb" || eye_colour == "blu" || eye_colour == "brn" || eye_colour == "gry"
										|| eye_colour == "grn" || eye_colour == "hzl" || eye_colour == "oth";	}
	
		
	//birth year must be in range  1920 - 2002
	bool is_birth_year_valid() const {	return !birth_year.empty() && std::stoi( birth_year ) >= 1920 && std::stoi( birth_year ) <= 2002;	};
	//issue year must be in range  2010 - 2020
	bool is_issue_year_valid() const {	return  !issue_year.empty() && std::stoi( issue_year ) >= 2010 && std::stoi( issue_year ) <= 2020;	};
	//expiration year must be in range  2020 - 2030
	bool is_expiry_year_valid() const {	return !expiration_year.empty() && std::stoi( expiration_year ) >= 2020 && std::stoi( expiration_year ) <= 2030;	};

	//number followed by cm or in
	// cm must be in range 150 - 193
	// in myst be in range 59 - 76
	bool is_height_valid() const 	{	return  (height.find( "cm" ) != std::string::npos && std::stoi( height ) >= 150 && std::stoi( height ) <= 193) ||
													(height.find( "in" ) != std::string::npos && std::stoi( height ) >= 59 && std::stoi( height ) <= 76);	}


	// For part 1, just check we have any data for each of the categories (other than country id )
	bool is_valid_passport_part1() const {	return !passport_id.empty() && !issue_year.empty() && !birth_year.empty() &&
											!expiration_year.empty() && !eye_colour.empty() && !height.empty() && !hair_colour.empty();	};

	//for part 2, check we have only  valid data for our categories, matching the given criteria
	bool is_valid_passport_part2() const {	return is_passport_id_valid() && is_hair_colour_valid() && is_eye_colour_valid() &&
											is_birth_year_valid() && is_height_valid() && is_issue_year_valid() && is_expiry_year_valid();	};
};


int main()
{
	//read in our passports
	std::vector<PASSPORT_DATA> all_passports;

	auto parse_passport_string = [&]( std::string& passport_data ) -> PASSPORT_DATA
	{
		PASSPORT_DATA new_passport;
		std::string word;
		std::stringstream stStream( passport_data );
		//parse each item in the passport data
		while ( stStream >> word )
		{
			std::stringstream word_str( word );
			std::string prop_id;
			std::string prop_value;

			//split our item into the id and the value
			std::getline( word_str, prop_id, ':');
			std::getline( word_str, prop_value, ':' );

			if ( prop_id == "byr" )
			{
				new_passport.birth_year =  prop_value;
			}
			else if ( prop_id == "iyr" )
			{
				new_passport.issue_year = prop_value;
			}
			else if ( prop_id == "eyr" )
			{
				new_passport.expiration_year =  prop_value;
			}
			else if ( prop_id == "hgt" )
			{
				new_passport.height = prop_value;
			}
			else if ( prop_id == "hcl" )
			{
				new_passport.hair_colour = prop_value;
			}
			else if ( prop_id == "ecl" )
			{
				new_passport.eye_colour = prop_value;
			}
			else if ( prop_id == "pid" )
			{
				new_passport.passport_id = prop_value;
			}
			else if ( prop_id == "cid" )
			{
				new_passport.country_id = prop_value;
			}
		}
		//clear our data
		passport_data.clear();
		return new_passport;
	};

	std::string line;
	std::ifstream input_file( "input.txt" );
	if ( input_file.is_open() )
	{
		std::string full_passport_string;

		while ( std::getline( input_file, line ) )
		{
			if ( !line.empty() )
			{
				//we have more data to add to our full passport string
				full_passport_string = full_passport_string + line + " ";
			}
			else
			{
				//we've reached the end of one passport. Send the data string off for parsing and move onto the next one
				all_passports.push_back( parse_passport_string( full_passport_string ) );
			}
		}

		//clear out any remaining data at the end
		if ( !full_passport_string.empty() )
		{
			all_passports.push_back( parse_passport_string( full_passport_string ) );
		}
	}

	int valid_passport_count_part_1 = 0;
	int valid_passport_count_with_criteria = 0;

	for ( const auto& passport : all_passports )
	{
		if ( passport.is_valid_passport_part1() )
		{
			++valid_passport_count_part_1;
		}
		
		if ( passport.is_valid_passport_part2() )
		{
			++valid_passport_count_with_criteria;
		}
	}

	std::cout << "=======================PART 1=========================== "  << std::endl;
	std::cout << "Total valid Passports: " << valid_passport_count_part_1 << std::endl;
	std::cout << "=======================PART 2=========================== " << std::endl;
	std::cout << "Total valid Passports: " << valid_passport_count_with_criteria << std::endl;
}
