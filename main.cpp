
#include "utils.h"

int main()
{
	bool x = true;
	std::string* s = new std::string;
	std::getline(std::cin, *s);
	x = utils::check_parentheses(s);

	std::cout << x << "\n";
	
	std::set<char>* Ul = utils::unique_literals(s);
	for (auto it = Ul->begin(); it != Ul->end(); it++)
	{
		std::cout << *it;
	}

	normalizedString* ns = utils::parse_string(s);

	for (auto it = ns->begin(); it != ns->end(); it++)
	{
		std::cout << "\n" << *it;
	}



	return 0;
}