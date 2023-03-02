
#include "utils.h"

bool utils::check_characters_within_range(std::string* Expression) 
{
	for (int i = 0; i < Expression->length(); i++)
	{
		//if expression char isnt: within uppercase ASCII Latin block A..Z, integers 0, 1 
		//and is not equal to ( ) ' + \n
		if (((*Expression)[i] < 65 || (*Expression)[i] > 90)
			&& (*Expression)[i] != '0' && (*Expression)[i] != '1'
			&& (*Expression)[i] != '(' && (*Expression)[i] != ')'
			&& (*Expression)[i] != '\'' && (*Expression)[i] != ' ' 
			&& (*Expression)[i] != '+' && (*Expression)[i] != '\n')
		{
			std::cout << "invalid Syntax";
			return false;
		}
	}
}

bool utils::check_parentheses(std::string* Expression)
{
	std::stack<char> ParenthesesStack;

	for (int i = 0; i < Expression->length(); i++)
	{
		//checks for empty parentheses () or open parenthesis followed by ' +
		if (i != Expression->length() && (*Expression)[i] == '(' && ((*Expression)[i + 1] == ')' || (*Expression)[i + 1] == '\''|| (*Expression)[i + 1] == '+'))
		{
			return false;
		}

		//checks for valid parentheses
		if ((*Expression)[i] == '(')
		{
			ParenthesesStack.push('(');
		}
		else if (ParenthesesStack.empty() && (*Expression)[i] == ')')
		{
			return false;
		}
		else if((*Expression)[i] == ')')
		{
			ParenthesesStack.pop();
		}
	} 

	if (!ParenthesesStack.empty())
	{
		return false;
	}

	return true;
}

int utils::verify_expression_syntax(std::string* Expression)
{
	return check_characters_within_range(Expression) && check_parentheses(Expression);
}

std::string* utils::decimal_to_bin(int dec)
{
	std::string* bin = new std::string;
	
	for (int i = 0; dec > 0; i++)
	{
		*bin += std::to_string(dec % 2);
		dec /= 2;
	}

	return bin;
}

std::set<char>* utils::unique_literals(std::string* Expression)
{
	std::set<char> *UniqueLiterals = new std::set<char>;
	for(int i = 0; i < Expression->length(); i++)
	{
		if ((*Expression)[i] >= 65 && (*Expression)[i] <= 90)
		{
			UniqueLiterals->insert((*Expression)[i]);
		}
	}
	return UniqueLiterals;
}

normalizedString* utils::parse_string(std::string* Expression) //simple parser for minterms (for now), for any Boolean expression we'd need a infix to RND parser
{
	normalizedString* RetStr = new normalizedString();
	std::string temp;

	for (int i = 0; i < Expression->length(); i++)	//iterates on string and removes spaces
	{
		if ((*Expression)[i] != ' ')
			temp += (*Expression)[i];
		
	}

	*Expression = temp;
	std::istringstream Stream(*Expression);
	std::string s;

	while (std::getline(Stream, s, '+')) //normalizes string using delimiter +
	{
		RetStr->push_back(s);
	}

	return RetStr;
}