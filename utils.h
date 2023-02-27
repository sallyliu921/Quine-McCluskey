


#ifndef UTILS_H
#define UTILS_H

#include <iostream>
#include <iomanip>
#include <string>
#include <stack>
#include <set>
#include <vector>
#include <cmath>

//definitions

#define Matrix_Int std::vector<int, int>

/// <summary>
/// utilities class holding independent functions
/// </summary>
class utils
{
public:
	static int verify_expression_syntax(std::string Expression);

	/// <summary>
	/// checks if string characters are within correct ASCII codes
	/// </summary>
	/// <param name="Expression">Expression given from user</param>
	/// <returns>boolean</returns>
	static bool check_characters_within_range(std::string Expression);

	/// <summary>
	/// checks open and empty parentheses 
	/// </summary>
	/// <param name="Expression">Expression given from user</param>
	/// <returns>boolean</returns>
	static bool check_parentheses(std::string Expression);

	/// <summary>
	/// iterates through expressions and checks for invalid terms such as (''') ()' ('
	/// checks if beginning of expression is valid eg; doesn't begin with '
	/// </summary>
	/// <param name="Expression"></param>
	/// <returns></returns>
	static bool check_terms(std::string Expression);

	static int unique_literals(std::string Expression);

	static Matrix_Int truth_table_generator(int literals);
};


#endif