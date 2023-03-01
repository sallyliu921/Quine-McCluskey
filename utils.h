
#define normalizedString std::vector<std::string>
#define charKeyMatrix std::map<char, std::vector<int>*>

#ifndef UTILS_H
#define UTILS_H

#include <iostream>
#include <iomanip>
#include <string>
#include <stack>
#include <set>
#include <map>
#include <vector>
#include <cmath>

/// <summary>
/// utilities class holding independent functions
/// </summary>
class utils
{
public:
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



	static std::set<char>* unique_literals(std::string* Expression);

	static std::string simplify_expression(std::string* Expression);

	static normalizedString* normalize_string(std::string* Expression);
};


#endif