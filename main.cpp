
#include "utils.h"
#include "quineMcCluskey.h"

int main()
{

    std::vector<std::string> s = {"ABCD", "A'BCD", "A'B'CD", "A'B'C'D", "A'B'C'D'", "AB'C'D'", "ABC'D'", "ABCD'"};
    quineMcCluskey qm(&s);

    qm.start();

    return 0;
}