
#include "utils.h"
#include "quineMcCluskey.h"

int main()
{

    std::vector<std::string> s = {"ABCDE", "A'BCD'E", "AB'CD'E'" , "ABC'DE", "A'B'C'D'E'", "A'B'CDE"};
    quineMcCluskey qm(&s);

    qm.start();

    return 0;
}