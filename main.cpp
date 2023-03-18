
#include "utils.h"
#include "quineMcCluskey.h"

int main()
{
    std::set<char> uniqueLiterals = { 'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H','I', 'J' };

    std::vector<std::string> s = {"ABCD", "A'BCD'", "AB'CD'" , "ABC'D"};
    quineMcCluskey qm(&s);

    qm.start();

    return 0;
}