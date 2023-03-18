

#define charKeyMatrix std::map<char, std::vector<int>*>
#define normalizedString std::vector<std::string>

#ifndef UTILS_H
#define UTILS_H

#include <iostream>
#include <sstream>
#include <iomanip>
#include <string>
#include <stack>
#include <set>
#include <map>
#include <vector>
#include <stdio.h>
#include <bitset>

#include "coveredBool.h"

/// <summary>
/// utilities class holding independent functions
/// </summary>
class utils
{
public:

	///checkers///

	/// <summary>
	/// contains all checkers for a boolean SoP expression
	/// </summary>
	/// <param name="Expression"></param>
	/// <returns></returns>
	static int verify_expression_syntax(std::string* Expression);

	/// <summary>
	/// checks if string characters are within correct ASCII codes
	/// </summary>
	/// <param name="Expression">Expression given from user</param>
	/// <returns>boolean</returns>
	static bool check_characters_within_range(std::string* Expression);

	/// <summary>
	/// checks open and empty parentheses 
	/// </summary>
	/// <param name="Expression">Expression given from user</param>
	/// <returns>boolean</returns>
	static bool check_parentheses(std::string* Expression);

	///misc utilities///


	/// <summary>
	/// converts from decimal to binary with zero padding for ease of printing
	/// </summary>
	/// <param name="Dec">decimal value</param>
	/// <param name="Bits">number of bits for padding</param>
	/// <returns>pointer to resulting string</returns>
	static std::string* decimal_to_binary(int Dec, int Bits);

	/// <summary>
	/// converts a minterm to its binary value (used to store expression as binary values for to operate upon)
	/// </summary>
	/// <param name="Minterm">the Minterm</param>
	/// <returns>binary value</returns>
	static int minterm_to_binary(std::string Minterm);

	/// <summary>
	/// counts number of set bits in a given value
	/// </summary>
	/// <param name="x">value</param>
	/// <returns>integer</returns>
	static int count_bits(int x);

	/// <summary>
	/// loops over given string to extract unique literals given
	/// </summary>
	/// <param name="Expression">string given by user</param>
	/// <returns>set of unique literals</returns>
	static std::set<char>* unique_literals(std::string* Expression);

	/// <summary>
	/// parses given string into a vector of strings that separates expression and operations
	/// </summary>
	/// <param name="Expression">string given by user</param>
	/// <returns>vector of string (normalized string)</returns>
	static normalizedString* parse_string(std::string* Expression);

};


#endif