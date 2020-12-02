// Day 2.cpp : This file contains the 'main' function. Program execution begins and ends there.
//
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <sstream>

constexpr int MIN_CHAR_COUNT_ID = 0;
constexpr int MAX_CHAR_COUNT_ID = 1;
constexpr int CHAR_TO_CHECK_ID = 2;
constexpr int PASSWORD_ID = 3;


int main()
{
	std::string line;
	std::ifstream input_file( "input.txt" );
	const std::string DELIMITERS = "-:";

	auto parse_string_into_words = [DELIMITERS]( std::string& string ) -> std::vector<std::string>
	{
		std::string word;
		std::vector<std::string> words;
		//replace our delimeters with spaces, this makes it easier to parse the string into words
		for ( auto& it : string )
		{
			if ( DELIMITERS.find( it ) != std::string::npos )
			{
				it = ' ';
			}
		}

		std::stringstream stStream( string );
		while ( stStream >> word )
		{
			words.push_back( word );
		}
		return words;
	};

	if ( input_file.is_open() )
	{
		int total_valid_passwords = 0;
		int valid_password_positions = 0;
		while ( std::getline( input_file, line ) )
		{
			std::vector<std::string> tokens = parse_string_into_words( line );

			if ( tokens.size() < PASSWORD_ID )
				continue;

			const int  min_value = std::stoi( tokens[MIN_CHAR_COUNT_ID] );
			const int  max_value = std::stoi( tokens[MAX_CHAR_COUNT_ID] );
			const char pass_char_to_find = tokens[CHAR_TO_CHECK_ID][0];
			const std::string password = tokens[PASSWORD_ID];

			int occurences = std::count( password.begin(), password.end(), pass_char_to_find );

			//check the occurences of the given character are within the bounds for part 1
			if ( occurences >= min_value && occurences <= max_value )
				total_valid_passwords++;

			//for part 2, check if the character that appears in the password at either the min or max position is the given character
			const int  first_pos = min_value - 1;
			const int  second_pos = max_value - 1;

			const bool char_at_pos1 = (int)password.size() > first_pos && password[first_pos] == pass_char_to_find;
			const bool char_at_pos2 = (int)password.size() > second_pos && password[second_pos] == pass_char_to_find;

			//exclusive or to ensure only 1 can be valid
			if ( char_at_pos1 ^ char_at_pos2 )
			{
				valid_password_positions++;
			}
		}

		std::cout << "=======================PART 1===============================" << std::endl;
		std::cout << "Total valid password occurences: " << total_valid_passwords << std::endl;

		std::cout << "=======================PART 2===============================" << std::endl;
		std::cout << "Total valid position passwords: " << valid_password_positions << std::endl;
	}

}

// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file
