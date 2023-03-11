
#include "utils.h"
#include "quineMcCluskey.h"

int main()
{
	std::set<char>* Uls = new std::set<char>({'A', 'B','C', 'D'});
	normalizedString* f = new normalizedString({});

	quineMcCluskey T1(Uls, f);

	printf("Bits: %i", utils::count_bits(-5));

	std::string* s = new std::string;
	*s = "ABCD+A'BCD+A'B'CD+A'B'C'D";
	normalizedString* a = utils::parse_string(s);
	T1.set_function(a);
	T1.start();

	return 0;
}