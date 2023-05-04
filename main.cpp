
#include "utils.h"
#include "quineMcCluskey.h"

int main()
{

start:
	
	std::cout << "Enter '1' to use a test case or '2' to input your own function: ";
	int option;
	std::cin >> option;

	if (option == 1) {
		std::vector<std::string> testFunctions = {
			"A'B'C'+A'BC'+A'B'C+AB'C",
			"A'B'C'+A'B'C+A'BC'+A'BC+AB'C'+ABC+ABC'",
			"A'B'C'D'+A'BC'D'+A'BCD'+A'BC'D+A'BCD+ABC'D+ABCD",
			"A'B'C'D'E'+A'B'C'DE'+A'BCD'E'+A'BCDE'+AB'C'D'E'+AB'C'DE'+ABCD'E'+ABCDE'",
			"A'B'C'D'E'F'+A'B'C'D'E'F+A'B'C'D'EF'+A'B'C'D'EF+A'BC'D'E'F'+A'BC'D'EF+A'BCDEF+AB'CD'EF'+ABC'DEF",
			"A'B'C'D'E'F'G'H'I'J'+A'BC'D'E'F'G'H'I'J'+A'B'C'D'E'F'G'H'IJ'+A'B'CD'E'F'G'HI'J'+A'B'C'DE'F'G'H'I'J+ABCDE'F'G'H'I'J'",
			"A'B'C'D'E'F'G'H'I'J'K'L'M'N'O'+A'BC'D'E'F'G'H'I'J'K'L'M'N'O'+A'B'C'D'E'F'G'HI'J'K'L'M'N'O'+AB'C'D'E'F'G'H'I'J'K'L'M'N'O+A'BC'DE'FG'HI'JK'LM'NO'+AB'CD'EF'GH'IJ'KL'MN'O+ABC'DEF'GHI'JKL'MNO'+A'B'CD'E'FG'H'IJ'K'LM'N'O"
			"+ABCDEFG'H'I'J'K'L'M'N'O'+ABCDEFGHIJKLMNO",
			"AB'CD+A'BCD'+A'BC'D",
			"A'B'C'D+A'BCD'+ABCD'",
			"A'BCD'+AB'CD+ABCD"
		};

		std::cout << "Select a test function (1-10): ";
		int testOption; 
		std::cin >> testOption;

		if (testOption < 1 || testOption > 10) {
			std::cout << "Invalid option. Please try again.\n";
			goto start;
		}

		quineMcCluskey qm(utils::parse_string(&testFunctions[testOption - 1]));
		qm.start();
	}
	else if (option == 2) {
	tryagain:

		std::cout << "Enter the function in sum of products form: ";

		std::string expression;
		std::cin >> expression;

		if (!utils::check_characters_within_range(&expression))
		{
			std::cout << "Invalid input, try again!";
			goto tryagain;
		}

		quineMcCluskey qm(utils::parse_string(&expression));
		qm.start();

	}
	else {
		std::cout << "Invalid option. Please try again.\n";
		goto start;
	}

    return 0;
}