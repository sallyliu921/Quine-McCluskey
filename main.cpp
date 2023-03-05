
#include "utils.h"
#include "truthTable.h"

int main()
{
	//bool x = true;
	//std::string* s = new std::string;
	//std::getline(std::cin, *s);
	//x = utils::check_parentheses(s);

	//std::cout << x << "\n";
	//
	//std::set<char>* Ul = utils::unique_literals(s);
	//for (auto it = Ul->begin(); it != Ul->end(); it++)
	//{
	//	std::cout << *it;
	//}

	//normalizedString* ns = utils::parse_string(s);

	//for (auto it = ns->begin(); it != ns->end(); it++)
	//{
	//	std::cout << "\n" << *it;
	//}

	std::set<char>* Uls = new std::set<char>({'A', 'B'});
	normalizedString* f = new normalizedString({});

	truthTable T1(Uls, f);

	T1.build_char_table();
	T1.print_table();
	T1.qm();

	printf("minterm test:\n");

	std::string s;
	std::cin >> s;

	std::cout << *utils::decimal_to_binary(utils::minterm_to_binary(s), 4);


	return 0;
}