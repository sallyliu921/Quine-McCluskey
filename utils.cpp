
#include "utils.h"

bool utils::check_characters_within_range(std::string Expression) 
{
	for (int i = 0; i < Expression.length(); i++)
	{
		//if expression char isnt: within uppercase ASCII Latin block A..Z, integers 0, 1 
		//and is not equal to ( ) ' + \n
		if ((Expression[i] < 65 || Expression[i] > 90)
			&& Expression[i] != '0' && Expression[i] != '1'
			&& Expression[i] != '(' && Expression[i] != ')'
			&& Expression[i] != '\'' && Expression[i] != ' ' 
			&& Expression[i] != '+' && Expression[i] != '\n')
		{
			std::cout << "invalid Syntax";
			return false;
		}
	}
}

bool utils::check_parentheses(std::string Expression)
{
	std::stack<char> ParenthesesStack;

	for (int i = 0; i < Expression.length(); i++)
	{
		//checks for empty parentheses ()
		if (i != Expression.length() && Expression[i] == '(' && Expression[i + 1] == ')')
		{
			return false;
		}

		//checkas for valid parentheses
		if (Expression[i] == '(')
		{
			ParenthesesStack.push('(');
		}
		else if (ParenthesesStack.empty() && Expression[i] == ')')
		{
			return false;
		}
		else if(Expression[i] == ')')
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

bool utils::check_terms(std::string Expression) 
{
	for (int i = 0; i < Expression[i]; i++)
	{
		
	}

	return true;
}

int utils::verify_expression_syntax(std::string Expression)
{
	return check_characters_within_range(Expression) && check_parentheses(Expression);
}

int utils::unique_literals(std::string Expression)
{
	std::set<char> UniqueLiterals;
	for(int i = 0; i < Expression[i]; i++)
	{
		if (Expression[i] >= 65 && Expression[i] <= 90)
		{
			UniqueLiterals.insert(Expression[i]);
		}
	}
	return UniqueLiterals.size();
}

Matrix_Int truth_table_generator(int literals)
{
	int ColSize = std::pow(literals, 2);

	
}