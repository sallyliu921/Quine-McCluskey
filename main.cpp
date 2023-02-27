
#include "utils.h"

int main()
{
	bool x = true;
	std::string s;
	std::getline(std::cin, s);
	x = utils::check_parentheses(s);

	std::cout << x << "\n";
	std::cout <<  utils::unique_literals(s) << "\n";

	return 0;
}